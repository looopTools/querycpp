#include <gtest/gtest.h>

#include <querycpp/sql_string.hpp>

TEST(test_sql_string, test_sql_string)
{
    querycpp::sql_string sql_str;
    sql_str = querycpp::sql_string("Test");

    std::string EXPECTED = "'Test'"; 
    EXPECT_EQ(sql_str.str(), EXPECTED);

    EXPECTED = "Test";
    EXPECT_EQ(sql_str.raw_str(), EXPECTED);

    size_t EXPECTED_SIZE = 6;
    EXPECT_EQ(sql_str.size(), EXPECTED_SIZE); 
    
    
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
