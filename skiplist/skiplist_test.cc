#include <gtest/gtest.h>
#include "skiplist.h"

TEST(skiplist, all) {
     SkipList set;
     int v;

     ASSERT_EQ(set.get(2, &v), false);
     set.put(2, 3);
     ASSERT_EQ(set.get(2, &v), true);
     ASSERT_EQ(v, 3);
     set.del(2);
     set.put(2, 3);
     ASSERT_EQ(set.get(2, &v), true);
     set.put(2, 3);
     ASSERT_EQ(set.get(2, &v), true);
     ASSERT_EQ(set.len(), 1);
     set.put(3, 3);
     ASSERT_EQ(set.len(), 2);
     ASSERT_EQ(set.get(2, &v), true);
     ASSERT_EQ(v, 3);
     set.del(2);
     ASSERT_EQ(set.get(2, &v), false);
     set.del(3);
     ASSERT_EQ(set.get(3, &v), false);
     set.put(2, 3);
     set.del(2);
     ASSERT_EQ(set.get(2, &v), false);
     set.put(2, 3);
     set.del(2);
     set.del(2);
     ASSERT_EQ(set.get(2, &v), false);
     set.put(2, 3);
}
