#ifndef RGEXCEPTIONHANDLER_H
#define RGEXCEPTIONHANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <exception>

namespace rg {

class exception : public std::exception {
public:
  exception(const std::string& message)
  : m_message(message)
  {}
  virtual ~exception() throw() {}

  const char* what() const throw() { return m_message.c_str(); }

private:
  std::string m_message;
};

} // namspace rg

#endif // RGEXCEPTIONHANDLER_H