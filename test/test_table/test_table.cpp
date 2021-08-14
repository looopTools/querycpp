#include <gtest/gtest.h>

#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>
#include <querycpp/table.hpp>

TEST(test_querycpp_table, test_constructor)
{

    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});

    querycpp::table tbl("test", {id, text});

    EXPECT_EQ("test", tbl.name());

    auto columns = tbl.columns();
    
    EXPECT_TRUE(columns.at(0) == id);
    EXPECT_TRUE(columns.at(1) == text); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
