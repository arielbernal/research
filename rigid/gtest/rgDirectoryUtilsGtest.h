#ifndef RGDIRECTORYUTILSGTEST_H
#define RGDIRECTORYUTILSGTEST_H

#include <fstream>
#include <iostream>
#include <vector>

#include <io/rgDirectoryUtils.h>

using namespace rg;

TEST(Test_DirectoryUtils, ExtractPathAndFilename) {
  std::string p = extract_path("./dirtest/testing/file01.txt");
  EXPECT_EQ("./dirtest/testing/", p);
  p = extract_filename("./dirtest/testing/file01.txt");
  EXPECT_EQ("file01.txt", p);
  p = extract_filename("./dirtest/testing/file01");
  EXPECT_EQ("file01", p);
}

TEST(Test_DirectoryUtils, FileExists) {
  EXPECT_TRUE(file_exists("./dirtest/file01.txt"));
  EXPECT_FALSE(file_exists("./dirtest/testing/file01.txt"));
}

TEST(Test_DirectoryUtils, TemporaryFiles) {
  TempFiles tp;
  tp.init("./dirtest/temp/tempXXXXXX");
  std::string firstFile = tp.create();
  ;
  for (size_t i = 0; i < 10; ++i) {
    std::string newFile = tp.create();
    std::ofstream outputFile(newFile.c_str());
    outputFile << "writing to file";
    EXPECT_TRUE(file_exists(newFile.c_str()));
  }
  EXPECT_FALSE(file_exists(firstFile.c_str()));
}

TEST(Test_DirectoryUtils, SearchDirectory) {
  std::vector<std::string> files;
  search_directory("./dirtest", "txt", files);
  EXPECT_EQ(2, files.size());
}
#endif  // RGDIRECTORYUTILSGTEST_H