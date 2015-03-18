#ifndef RGDIRECTORYUTILS_H
#define RGDIRECTORYUTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <io/rgExceptionHandler.h>
#include <math/rgRng.h>

namespace rg {

#if _WIN32
#include <Windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif


#if _WIN32
#define FILEMODE 0
#define PATHTOKEN ";"
#define PATHSEP '\\'
#else
#define FILEMODE 1
#define PATHTOKEN ":"
#define PATHSEP '/'
#endif

/// Tests if an ifstream or an ofstream was successfully opened.
template <typename T>
inline bool is_file_open(const T& file, const std::string& filename) {
  std::ostringstream message;
  if (!file.is_open()) {
    message << "File '" << filename << "' not found!";

    if (filename.find("..") == 0) {
      message << std::endl << "--> Please check the relative path from the "
                              "current directory to the specified file.";
    }
    throw rg::exception(message.str());
  }
  return true;
}

inline void search_directory(const std::string& path,
                             const std::string& extension,
                             std::vector<std::string>& files,
                             bool recursive_search = false) {
  std::string file_extension;
  std::string file_name;

#if WIN32
  HANDLE h_file;
  WIN32_FIND_DATA file_information;
  std::string pattern = path + PATHSEP +"\\*.*";

  h_file = FindFirstFile(LPCWSTR(pattern.c_str()), &file_information);
  if (h_file != INVALID_HANDLE_VALUE) {
    do {
      if (file_information.cFileName[0] != '.') {
        file_name = path + "\\" + std::string((char*)file_information.cFileName);
        if (file_information.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
          if (recursive_search) {
            search_directory(file_name, extension, files, recursive_search);
          }
        } else {
          file_extension = std::string((char*)file_information.cFileName);
          file_extension = file_extension.substr(file_extension.rfind(".") + 1);
          if (file_extension == extension) {
            files.push_back(file_name);
          }
        }
      }
    } while (FindNextFile(h_file, &file_information) == true);
    FindClose(h_file);
  }
#else
  DIR* dp;
  struct dirent* dirp;
  if ((dp = opendir(path.c_str())) == NULL) {
    std::cout << "Error opening " << path << std::endl;
    return;
  }
  while ((dirp = readdir(dp)) != NULL) {
    std::string fname = std::string(dirp->d_name);
    file_name = path + "/" + fname;

    if (dirp->d_type == DT_DIR && fname != ".." && fname != ".") {
      if (recursive_search) {
        search_directory(file_name, extension, files, recursive_search);
      }
    } else {
      file_extension = fname.substr(fname.rfind(".") + 1);
      if (file_extension == extension) {
        files.push_back(file_name);
      }
    }
  }
  closedir(dp);
#endif
}

inline std::string extract_path(const std::string& path) {
  return path.substr(0, path.find_last_of(PATHSEP) + 1);
}

inline std::string extract_filename(const std::string& path,
                                    bool no_extension = false) {
  std::string str;
  size_t i0 = path.find_last_of(PATHSEP) + 1;
  size_t i1 = path.find_last_of('.');
  if (no_extension) {
    str = path.substr(i0, i1 - i0);
  } else {
    str = path.substr(i0);
  }
  return str;
}

inline bool file_exists(const std::string& filename, int mode = 0) {
  if (mode < 0 || mode > 7) {
    throw rg::exception("File exists mode should be [0,7]");
    return false;
  }
// mode = 0 (F_OK) (default): checks file for existence only
// mode = 1 (X_OK): execution permission
// mode = 2 (W_OK): write permission
// mode = 4 (R_OK): read permission
// mode = 6       : read and write permission
// mode = 7       : read, write and execution permission
#if WIN32
  if (_access(filename.c_str(), mode) == 0)
#else
  if (access(filename.c_str(), mode) == 0)
#endif
  {
    return true;
  }
  return false;
}



inline bool get_executable_path(const std::string& filename,
                                std::string& filepath) {
  std::string filetmp = filepath + PATHSEP + filename;

  if (file_exists(filetmp, FILEMODE)) {
    return true;
  }
  char* path = getenv("PATH");
  if (path == NULL) {
    filepath = "Path is not set";
    return false;
  } else {
    std::list<std::string> ls;
    char* pch = strtok(path, PATHTOKEN);
    while (pch != NULL) {
      ls.push_back(pch);
      pch = strtok(NULL, PATHTOKEN);
    }
    for (std::list<std::string>::const_iterator i = ls.begin(); i != ls.end();
         ++i) {
      filetmp = (*i) + PATHSEP + filename;
      if (file_exists(filetmp, FILEMODE)) {
        filepath = *i;
        return true;
      }
    }
  }
  filepath = "Executable file not found";
  return false;
}

class TempFiles {
 public:
  static const size_t retry_max = 100;

  TempFiles() : m_template("") {};

  ~TempFiles() { remove_files(); }

  void init(const std::string& templ) { m_template = templ; }

  std::string create() {

    std::string str_name = generate_random_string();

    size_t iretry = 0;
    while (file_exists(str_name) && iretry < retry_max) {
      str_name = generate_random_string();
      iretry++;
    }
    if (iretry == retry_max) {
      throw rg::exception("Cannot generate random file");
      return "";
    }
    m_files.push_back(str_name);
    return str_name;
  }

  void remove_files() {
    for (size_t i = 0; i < m_files.size(); ++i) {
      std::remove(m_files[i].c_str());
    }
    m_files.clear();
  }

 protected:
  std::string generate_random_string() {
    std::string rnd = m_template;
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 0; i < rnd.size(); ++i) {
      if (rnd[i] == 'X') {
        size_t j = size_t(rg::uniform<float>(0, sizeof(alphabet) - 1));
        rnd[i] = alphabet[j];
      }
    }
    return rnd;
  }

 private:
  std::string m_template;
  std::vector<std::string> m_files;
};

}  // namespace rg

#endif  // RGDIRECTORYUTILS_H
