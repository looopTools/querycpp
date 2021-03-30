#include <gtest/gtest.h>
#include <querycpp/database_data_type.hpp>

TEST(test_database_data_types, type_to_string)
{
    EXPECT_EQ("NUMBER", querycpp::database::type_to_string(querycpp::database::data_type::NUMBER));

    EXPECT_EQ("BIGINT", querycpp::database::type_to_string(querycpp::database::data_type::BIG_INT));

    EXPECT_EQ("VARCHAR", querycpp::database::type_to_string(querycpp::database::data_type::VARCHAR));

    EXPECT_EQ("SERIAL", querycpp::database::type_to_string(querycpp::database::data_type::SERIAL));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
