#include <gtest/gtest.h>

#include <vec2.h>

#include <cmath>

TEST(vec2_test, vec2_ops) {
  vec2_t a, b;
  a.x = 10.0f;
  a.y = 1;
  b.x = 20.0f;
  b.y = 2;
  vec2_t res;
  float fres;

  ASSERT_TRUE(vec2_iseq({1, 1}, {1, 1})) << "vec2_iseq failed\n";
  ASSERT_FALSE(vec2_iseq({1, 2}, {2, 1})) << "vec2_iseq failed\n";

  res = vec2_add(a, b);
  EXPECT_TRUE(vec2_iseq(res, (vec2_t){30, 3})) << "vec2_add failed\n";

  fres = vec2_norm(a);
  EXPECT_TRUE(fabs(fres - sqrt(101) <= 0.01)) << "vec2_norm failed\n";

  res = vec2_multip(a, 1.0f/fres);
  EXPECT_TRUE(vec2_iseq(res, vec2_normalised(a))) << "vec2_multip failed\n";

  res= vec2_cross(a, 10.0f);
  EXPECT_TRUE(vec2_iseq(res, {10.0f, -100.0f})) << "vec2_cross failed\n";
}
