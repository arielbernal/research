#ifndef RGEXCEPTIONHANDLERGTEST_H
#define RGEXCEPTIONHANDLERGTEST_H

#include <io/rgExceptionHandler.h>

using namespace rg;

void exceptionStdFunc(const std::string& msg) {
  throw std::invalid_argument("invalid argument");
}

void exceptionFunc(const std::string& msg) { throw rg::exception(msg); }

TEST(Test_ExceptionHandler, ExceptionStdFunc) {
  try {
    exceptionStdFunc("invalid argument");
  }
  catch (const std::exception& e) {
    std::string str = e.what();
    EXPECT_EQ("invalid argument", str);
  }
}

TEST(Test_ExceptionHandler, ExceptionFunc) {
  try {
    exceptionFunc("invalid argument");
  }
  catch (const std::exception& e) {
    std::string str = e.what();
    EXPECT_EQ("invalid argument", str);
  }
}

#endif  // RGEXCEPTIONHANDLERGTEST_H