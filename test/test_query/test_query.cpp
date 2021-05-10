#include <gtest/gtest.h>

#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>
#include <querycpp/table.hpp>
#include <querycpp/query.hpp>

TEST(test_querycpp_query, test_create)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2))";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
