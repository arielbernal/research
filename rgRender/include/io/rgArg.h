#ifndef RGARG_H
#define RGARG_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace rg {

/// Helper class to parse command-line arguments, print help and manage defaults
class ArgParser
{
public:
  ArgParser(int argc, char* argv[])
    : m_usage_help(true)
  {
    m_arguments.clear();
    m_usage.clear();
    for (int i = 1; i < argc; ++i) {
      m_arguments.push_back(argv[i]);
    }
  }
  
  
  ArgParser(int argc, char* argv[], const std::string& usage)
    : m_usage_help(true)
  {
    m_arguments.clear();
    m_usage.clear();
    for (int i = 1; i < argc; ++i) {
      m_arguments.push_back(argv[i]);
    }
    add_usage(usage);
  }

  /// Parse a command-line parameter that takes a numeric argument and return true if argument is found
  template<typename T>
  bool parse_argument(
    const std::string& name,
    const std::string& short_name,
    T& var,
    const std::string& usage = "")
  {
    bool found = false; 
    std::list<std::string>::iterator it = m_arguments.begin();
    while(it != m_arguments.end()) {    
      if ((*it) == "--"+name || (*it) == "-"+short_name) {
        it = m_arguments.erase(it);
        if (it == m_arguments.end()) {
          break;
        }
        else {
          var = static_cast<T>(atof((*it).c_str()));
          m_arguments.erase(it);
          found = true;
          break;
        }
      }
      ++it;
    }
    add_usage(name, short_name, "", var, usage);
    return found;
  }

  /// Parse a command-line parameter that takes a string argument and return true if argument is found
  bool parse_argument(
    const std::string& name,
    const std::string& short_name,
    std::string& var,
    const std::string& usage = "")
  {
    bool found = false;
    std::list<std::string>::iterator it = m_arguments.begin();
    while(it != m_arguments.end()) {    
      if ((*it) == "--"+name || (*it) == "-"+short_name) {
        it = m_arguments.erase(it);
        if (it == m_arguments.end()) {          
          break;
        }
        else {
          var = (*it);
          m_arguments.erase(it);
          found = true;
          break;
        }
      }
      ++it;
    }
    add_usage(name, short_name, var, 0, usage);
    return found;
  }

  /// Parse a command-line parameter that takes a boolean argument and return true if argument is found
  bool parse_argument(
    const std::string& name,
    const std::string& short_name,
    bool& var,
    const std::string& usage = "")
  {
    bool found = false;
    std::list<std::string>::iterator it = m_arguments.begin();
    while(it != m_arguments.end()) {    
      if ((*it) == "--"+name || (*it) == "-"+short_name) {
        it = m_arguments.erase(it);
        if (it == m_arguments.end()) {
          break;
        }
        else {
          const std::string arg = (*it);        
          if (arg == "false" || arg == "FALSE" || arg == "f" || arg == "F" ||
             arg == "n" || arg == "N" || arg == "no" || arg == "NO" || arg == "0") {
             var = 0;          
          } 
          else {
            var = 1;
          }
          m_arguments.erase(it);
          found = true;
          break;
        }
      }
      ++it;
    }
    add_usage(name, short_name, "", var, usage);
    return found;
  }

  /// Appends @p usage to the help message
  void add_usage(const std::string& usage)
  {
    m_usage.push_back(usage);
  }

  /// Constructs and appends a help message for the command-line argument @p info
  /// when @p usage is non-empty
  void add_usage(
    const std::string& name,
    const std::string& short_name,
    const std::string& parameter,
    const double value,

    const std::string& usage)
  {
    if (usage.empty() == false) {
      std::ostringstream stream_actual;
      if (parameter.empty()) {
        stream_actual << value;
      }
      else {
        stream_actual << parameter;
      }

      const std::string align = (name.size() > 7) ? "\t" : "\t\t";
      std::string line = " -" + short_name + ",  "
        + "--" + name + align
        + usage + " (" + stream_actual.str()+ ")";
      m_usage.push_back(line);
    }
  }

  /// Print the help for each command-line parameter
  void print_usage()
  {
    if (m_usage_help) {
      std::list<std::string>::iterator it;
      for (it = m_usage.begin(); it != m_usage.end(); ++it) {
        std::cout << *it << std::endl;
      }
      std::cout << std::endl;
    }
  }

protected:
  std::list<std::string> m_arguments;   
  std::list<std::string> m_usage;
  bool m_usage_help;
};

} // namespace rg

#endif // RGARG_H
