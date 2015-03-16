#include <io/rgWavefrontObj.h>
#include <io/rgDirectoryUtils.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace rg {

std::vector<std::string> splitString(const std::string& S,
                                     const std::string& Delimiters) {
  std::vector<std::string> Tokens;
  std::stringstream SS(S);
  std::string Item;
  size_t Prev = 0;
  size_t Pos = 0;
  while ((Pos = S.find_first_of(Delimiters, Prev)) != std::string::npos) {
    if (Pos > Prev) Tokens.push_back(S.substr(Prev, Pos - Prev));
    Prev = Pos + 1;
  }
  if (Prev < S.length()) Tokens.push_back(S.substr(Prev, std::string::npos));
  return Tokens;
}

template <typename T>
T toNumber(const std::string& stringNumber) {
  T value;
  std::stringstream stream(stringNumber);
  stream >> value;
  if (stream.fail()) {
    std::cout << "StringToNumber Error, " << stringNumber << std::endl;
  }
  return value;
}

bool WavefrontObjFile::loadMtlFile(const std::string& Filename) {
  MtlFilename = Filename;
  std::ifstream Ifs(Filename.c_str(), std::ios::in);
  if (!Ifs.is_open()) {
    std::cout << "WavefrontObjFile::loadMtlFile() -> Error Opening the file "
              << Filename << std::endl;
    return false;
  }
  std::string Line;
  while (!Ifs.eof()) {
    getline(Ifs, Line);
    std::vector<std::string> Tokens = splitString(Line, " /");
    if (Tokens.size() > 0) {
      std::string Tk = Tokens[0];
      if (Tk == "#") continue;
      if (Tk == "newmtl") {
        // add Material
        GLMaterial M(Tokens[1]);
        std::pair<MaterialIterator, bool> ret =
            Materials.insert(MaterialPair(Tokens[1], M));
        CurrentMaterial = &(ret.first->second);
        continue;
      }
      if (Tk == "Ka") {
        CurrentMaterial->Ka =
            glm::vec3(toNumber<float>(Tokens[1]), toNumber<float>(Tokens[2]),
                      toNumber<float>(Tokens[3]));
        continue;
      }
      if (Tk == "Kd") {
        CurrentMaterial->Kd =
            glm::vec3(toNumber<float>(Tokens[1]), toNumber<float>(Tokens[2]),
                      toNumber<float>(Tokens[3]));
        continue;
      }
      if (Tk == "Ks") {
        CurrentMaterial->Ks =
            glm::vec3(toNumber<float>(Tokens[1]), toNumber<float>(Tokens[2]),
                      toNumber<float>(Tokens[3]));
        continue;
      }
      if (Tk == "map_Kd") {
        CurrentMaterial->map_Kd = Tokens[1];
        if (Tokens.size() > 2)
          for (int k = 2; k < Tokens.size(); ++k)
            CurrentMaterial->map_Kd += "/" + Tokens[k];

        continue;
      }
    }
  }
  return true;
}

bool WavefrontObjFile::loadObjFile(const std::string& Filename) {
  ObjFilename = Filename;
  std::ifstream ifs(Filename.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cout << "WavefrontObjFile::loadObjFile() -> Error Opening file "
              << Filename << std::endl;
    return false;
  }

  std::string path = extract_path(Filename);
  std::string line;
  CurrentMaterial = NULL;
  while (!ifs.eof()) {
    getline(ifs, line);
    std::vector<std::string> tokens = splitString(line, " /");
    // parsing line
    if (tokens.size() > 0) {
      std::string tk = tokens[0];
      if (tk == "#") continue;
      if (tk == "mtllib") {
        MtlFilename = tokens[1];
        if (tokens.size() > 2)
          for (int k = 2; k < tokens.size(); ++k)
            MtlFilename += "/" + tokens[k];
        if (!loadMtlFile(path + MtlFilename)) return false;
        continue;
      }
      if (tk == "o") {
        // add Object
        WavefrontObj* O = new WavefrontObj(tokens[1]);
        Objects.push_back(O);
        CurrentObject = Objects.back();
        continue;
      }
      if (tk == "v") {
        if (!CurrentObject) {
          WavefrontObj* O = new WavefrontObj("unknonw");
          Objects.push_back(O);
          CurrentObject = Objects.back();
        }
        // add Vertex
        float x = toNumber<float>(tokens[1]);
        float y = toNumber<float>(tokens[2]);
        float z = tokens.size() < 4 ? 0 : toNumber<float>(tokens[3]);
        CurrentObject->addVertex(x, y, z);
        continue;
      }
      if (tk == "vn") {
        if (!CurrentObject) {
          WavefrontObj* O = new WavefrontObj("unknonw");
          Objects.push_back(O);
          CurrentObject = Objects.back();
        }
        // add Vertex
        float x = toNumber<float>(tokens[1]);
        float y = toNumber<float>(tokens[2]);
        float z = tokens.size() < 4 ? 0 : toNumber<float>(tokens[3]);
        CurrentObject->addNormal(x, y, z);
        continue;
      }
      if (tk == "vt") {
        if (!CurrentObject) {
          WavefrontObj* O = new WavefrontObj("unknonw");
          Objects.push_back(O);
          CurrentObject = Objects.back();
        }
        // add Vertex
        float x = toNumber<float>(tokens[1]);
        float y = toNumber<float>(tokens[2]);
        CurrentObject->addUv(x, y);
        continue;
      }

      if (tk == "f") {
        // add Face
        WavefrontFace* F = new WavefrontFace(CurrentMaterial);
        int i = 1;
        while (i < (int)tokens.size()) {
          F->Vertices.push_back(toNumber<int>(tokens[i++]) - 1);
          if (CurrentObject->hasUVs())
            F->UVs.push_back(toNumber<int>(tokens[i++]) - 1);
          if (CurrentObject->hasNormals())
            F->Normals.push_back(toNumber<int>(tokens[i++]) - 1);
        }
        CurrentObject->addFace(F);
        continue;
      }
      if (tk == "usemtl") {
        // add material
        CurrentMaterial = &Materials[tokens[1]];
        continue;
      }
      if (tk == "s") {
        // smoothing group ???
        continue;
      }
    }
  }
  return true;
}

std::string toString(const glm::vec3& v) {
  std::ostringstream output;
  output << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return output.str();
}

std::string toString(const glm::vec2& v) {
  std::ostringstream output;
  output << "[" << v.x << ", " << v.y << "]";
  return output.str();
}

void WavefrontObj::dump() {
  std::cout << "Object : " << Name << std::endl;
  std::cout << "  Vertices: " << std::endl;
  for (auto e : Vertices) {
    std::cout << "    " << toString(e) << std::endl;
  }
  std::cout << "  Normals: " << std::endl;
  for (auto e : Normals) {
    std::cout << "    " << toString(e) << std::endl;
  }
  std::cout << "  UVs: " << std::endl;
  for (auto e : UVs) {
    std::cout << "    " << toString(e) << std::endl;
  }
  std::cout << "  Faces: " << std::endl;
  for (auto e : Faces) {
    if (e->Material)
      std::cout << "    M: " << e->Material->Name ;
    std::cout << " v(";
    for (auto s : e->Vertices)
      std::cout << s << " ";
    std::cout << ") ";
    std::cout << " n(";
    for (auto s : e->Normals)
      std::cout << s << " ";
    std::cout << ") ";
    std::cout << " t(";
    for (auto s : e->UVs)
      std::cout << s << " ";
    std::cout << ") ";
    std::cout << "\n";
  }
}

void WavefrontObjFile::dump() {
  std::cout << "WavefrontObjFile = " << ObjFilename << std::endl;
  std::cout << "MtlFilename = " << MtlFilename << std::endl;
  std::cout << "Materials = " << Materials.size() << std::endl;
  for (auto e : Objects) {
    e->dump();
  }

  for (auto e : Materials) {
    const GLMaterial& M = e.second;
    std::cout << "Material : " << M.Name << std::endl;
    std::cout << "  Ambient  : " << toString(M.Ka) << std::endl;
    std::cout << "  Diffuse  : " << toString(M.Kd) << std::endl;
    std::cout << "  Specular : " << toString(M.Ks) << std::endl;
    std::cout << "  Specular Exp : " << M.Ns << std::endl;
    if (M.map_Ka.size() > 0)
      std::cout << "  Texture Ambient  : " << M.map_Ka << std::endl;
    if (M.map_Kd.size() > 0)
      std::cout << "  Texture Diffuse  : " << M.map_Kd << std::endl;
    if (M.map_Ks.size() > 0)
      std::cout << "  Texture Specular : " << M.map_Ks << std::endl;
  }
}

}  // namespace rg
