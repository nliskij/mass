#include "gtest/gtest.h"

#include "tests/proto.pb.h"

TEST(ProtoBuildTest, Serialize) {
    ::controve::PTest test_proto1, test_proto2;
    test_proto1.set_s("Hey there");
    test_proto1.set_i(3141);

    ::std::string serialized;
    ASSERT_TRUE(test_proto1.SerializeToString(&serialized));
    ASSERT_TRUE(test_proto2.ParseFromString(serialized));

    EXPECT_EQ("Hey there", test_proto2.s());
    EXPECT_EQ(3141, test_proto2.i());
}
