#ifndef RGLOG_H
#define RGLOG_H


namespace rg {

#ifndef LOG_ACTIONS
#define LOG(x)
#else
#define LOG(x) do {std::cout << x; } while(0)
#endif

}  // namespace rg

#endif  // RGLOG_H
