#ifndef SVECTORGTEST_H
#define SVECTORGTEST_H

using namespace SVector;

class SVectorfTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  void compare(const SVectorf &a, float x, float y = 0, float z = 0,
               float w = 0) {
    EXPECT_EQ(x, a.x);
    EXPECT_EQ(y, a.y);
    EXPECT_EQ(z, a.z);
    EXPECT_EQ(w, a.w);
  }
  void compare(const SVectorf &A, const SVectorf &B) {
    EXPECT_EQ(A.x, B.x);
    EXPECT_EQ(A.y, B.y);
    EXPECT_EQ(A.z, B.z);
    EXPECT_EQ(A.w, B.w);
  }
};

TEST_F(SVectorfTest, Constructors0) {
  // SVector() : data{0}
  SVectorf a;
  compare(a, 0, 0, 0, 0);
}

TEST_F(SVectorfTest, Constructors1) {
  // SVector(T x, T y, T z, T w = T(0))
  SVectorf b(2, 3, 4, 5);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Constructors1a) {
  // SVector(T x, T y, T z, T w = T(0))
  SVectorf b(2, 3, 4);
  compare(b, 2, 3, 4, 0);
}

TEST_F(SVectorfTest, Constructors2) {
  // SVector(const SVector &t)
  SVectorf b(2, 3, 4, 5);
  SVectorf c(b);
  compare(b, c);
}

TEST_F(SVectorfTest, Constructors3) {
  // SVector(T v)
  SVectorf b(2);
  compare(b, 2, 2, 2, 2);
}

TEST_F(SVectorfTest, Constructors4) {
  // SVector(T *v)
  float v[4] = {2, 3, 4, 5};
  SVectorf b(v);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Assignments0) {
  // void operator()(const SVector &t)
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  b(a);
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, Assignments1) {
  // void operator()(T x, T y, T z, T w = T(0))
  SVectorf a(1, 2, 3, 4);
  a(2, 3, 4);
  compare(a, 2, 3, 4, 0);
  a(4);
  compare(a, 4, 4, 4, 4);
}

TEST_F(SVectorfTest, Assignments2) {
  // void clear()
  SVectorf a(1, 2, 3, 4);
  a.clear();
  compare(a, 0);
}

TEST_F(SVectorfTest, Assignments3) {
  // T &operator[](size_t i)
  SVectorf a(1, 2, 3, 4);
  EXPECT_EQ(3, a[2]);
  a[1] = 5;
  compare(a, 1, 5, 3, 4);
}

TEST_F(SVectorfTest, UnaryOperators0) {
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  // SVector operator+()
  b = +a;
  compare(b, a);
  // SVector operator-()
  b = -a;
  compare(b, -1, -2, -3, -4);
}

TEST_F(SVectorfTest, UnaryOperators1) {
  SVectorf a(1, 2, 3, 4);
  // SVector operator++()
  ++a;
  compare(a, 2, 3, 4, 5);
  // SVector operator--()
  --a;
  compare(a, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, UnaryOperators2) {
  SVectorf a(1, 2, 3, 4);
  SVectorf b;
  // SVector operator++(int)
  b = a++;
  compare(a, 2, 3, 4, 5);
  compare(b, 1, 2, 3, 4);
  // SVector operator--(int)
  b = a--;
  compare(a, 1, 2, 3, 4);
  compare(b, 2, 3, 4, 5);
}

TEST_F(SVectorfTest, Mutators) {
  float v[4] = {1, 2, 3, 4};
  SVectorf b;
  b = v;
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, ScalarMutators) {
  SVectorf b;
  // void operator=(T v)
  b = 3;
  compare(b, 3, 3, 3, 3);
  b(1, 2, 3, 4);
  // SVector &operator+=(float v) 
  b += 5;
  compare(b, 6, 7, 8, 9);
  b -= 5;
  compare(b, 1, 2, 3, 4);
  b *= 2;
  compare(b, 2, 4, 6, 8);
  b /= 2;
  compare(b, 1, 2, 3, 4);
}

TEST_F(SVectorfTest, VectorMutators) {
  SVectorf b;
  SVectorf a(2, 3, 4, 5);
  SVectorf c(2, 2, 2, 2);
  // void operator=(T v)
  b = a;
  compare(b, 2, 3, 4, 5);
  b += c;
  compare(b, 4, 5, 6, 7);
  b -= c;
  compare(b, 2, 3, 4, 5);
  b *= c;
  compare(b, 4, 6, 8, 10);
  b /= c;
  compare(b, 2, 3, 4, 5);
}


TEST_F(SVectorfTest, BinaryOperatorsPlus) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a + 2.0f;  
  compare(b, 4, 5, 6, 7);
  b = 2.0f + a;  
  compare(b, 4, 5, 6, 7);  
}

TEST_F(SVectorfTest, BinaryOperatorsMinus) {
  SVectorf a(2, 3, 4, 5);
  SVectorf b;
  b = a - 2.0f;  
  compare(b, 0, 1, 2, 3);
  b = 2.0f - a;  
  compare(b, 0, -1, -2,  -3);  
}







#endif  // SVECTORGTEST_H