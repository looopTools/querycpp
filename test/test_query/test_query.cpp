#include <gtest/gtest.h>

#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>
#include <querycpp/table.hpp>
#include <querycpp/query.hpp>

#include <querycpp/common.hpp>

TEST(test_querycpp_query, test_create)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2))";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}

TEST(test_querycpp_query, test_select)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test"; 
    
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).str());
    query.clean(); 
    
    EXPECTED = "SELECT id, text FROM test";

    std::vector<std::string> _columns = {"id", "text"};
    

    EXPECT_EQ(EXPECTED, query.SELECT(_columns).str());
}

TEST(test_querycpp_query, test_select_where)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().str());
    query.clean();
    
    EXPECTED = "SELECT id, text FROM test WHERE";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().str());
}

TEST(test_querycpp_query, test_select_where_gt)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id > 3"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().GT(id, std::to_string(3)).str());
    query.clean();
    
    EXPECTED = "SELECT id, text FROM test WHERE id > 3";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().GT(id, std::to_string(3)).str());
}

TEST(test_querycpp_query, test_select_where_lt)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id < 3"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().LT(id, std::to_string(3)).str());
    query.clean();
    
    EXPECTED = "SELECT id, text FROM test WHERE id < 3";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().LT(id, std::to_string(3)).str());
}


TEST(test_querycpp_query, test_select_where_in)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN("id").str());
    query.clean();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN("id").str());
}


TEST(test_querycpp_query, test_select_where_in_str_param_list)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN ($1, $2, $3)"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN("id", "$1, $2, $3").str());
    query.clean();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN (13, 1337, 42)";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN("id", "13, 1337, 42").str());
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
