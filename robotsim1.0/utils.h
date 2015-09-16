#ifndef UTILS_H
#define UTILS_H

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void Sleep(int sleepMs) {
#ifdef WIN32
  Sleep(sleepMs);
#else
  // usleep takes sleep time in us (1 millionth of a second)
  usleep(sleepMs * 1000);
#endif
}

#endif