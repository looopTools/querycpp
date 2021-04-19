#include <gtest/gtest.h>

#include <querycpp/common.hpp>
#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>

#include <string>
#include <vector>

TEST(test_querycpp_column, test_constructor)
{
    const std::string EXPECTED = "id SERIAL PRIMARY KEY";

    std::string name = "id";
    std::vector<std::string> constraints = {querycpp::constraints::PRIMARY};

    querycpp::column c(name, querycpp::database::data_type::SERIAL); 
    
    querycpp::column column(name, querycpp::database::data_type::SERIAL, constraints);

    EXPECT_EQ(EXPECTED, column.str());     
}

TEST(test_querycpp_column, test_varchar)
{
    const std::string EXPECTED = "text VARCHAR(3)";

    querycpp::column column("text", querycpp::database::data_type::VARCHAR, {"3"});
    
    EXPECT_EQ(EXPECTED, column.str()); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
