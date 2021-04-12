#include <gtest/gtest.h>

#include <querycpp/column.hpp>
#include <querycpp/table.hpp>

TEST(test_querycpp_table, test_constructor)
{

    querry::column id("id", querycpp::database::data_type::SERIAL, {querycpp::constraints::PRIMARY});
    querry::column text("text", querycpp::database::data_type::VARCHAR, {"2"});
    (void) id;
    (void) text;
    
    EXPECT_TRUE(true); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
