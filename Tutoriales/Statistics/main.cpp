#include <iostream>
#include <vector>

float mean(const float* a, int n) {
  float s = 0;
  for (int i = 0; i < n; ++i)
    s += a[i];
  return s / n;
}

float mean1(const std::vector<float>& a) {
  float s = 0;
  for (size_t i = 0; i < a.size(); ++i)
    s += a[i];
  return s / a.size();
}

float mean2(const std::vector<float>& a) {
  float s = 0;
  for (std::vector<float>::const_iterator I = a.begin(), E = a.end(); I != E; ++I)
    s += *I;
  return s / a.size();
}

float meanC11(const std::vector<float>& a) {
  float s = 0;
  for (auto e : a)
    s += e;
  return s / a.size();
}


int main() {
  float a[] = {7, 4, 1, 8};
  float m = mean(a, 4);
  std::cout << "c array mean = " << m << std::endl;

  std::vector<float> v({ 7, 4, 1, 8 });
  float m1 = mean1(v);
  std::cout << "vector mean1 = " << m1 << std::endl;

  float m2 = mean2(v);
  std::cout << "vector mean2 = " << m2 << std::endl;

  float mc11 = meanC11(v);
  std::cout << "vector C11 mean = " << mc11 << std::endl;

  return 0;
}