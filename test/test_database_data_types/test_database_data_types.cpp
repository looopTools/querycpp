#include <gtest/gtest.h>
#include <querycpp/types.hpp>

TEST(test_database_data_types, type_to_string)
{
    EXPECT_EQ("NUMBER", querycpp::type_to_string(querycpp::data_type::common::numerical::NUMBER));

    EXPECT_EQ("BIGINT", querycpp::type_to_string(querycpp::data_type::common::numerical::BIG_INT));

    EXPECT_EQ("VARCHAR", querycpp::type_to_string(querycpp::data_type::common::string::VARCHAR));

    EXPECT_EQ("SERIAL", querycpp::type_to_string(querycpp::data_type::postgres::numerical::SERIAL));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
