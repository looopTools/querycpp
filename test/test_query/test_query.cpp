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

TEST(test_querycpp_query, test_nested)
{

    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    querycpp::column id2("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column num("num", querycpp::database::type::postgres::numerical::INTEGER, {querycpp::constraints::PRIMARY});
    querycpp::table tbl2("tbl2", {id2, num});
    querycpp::query query2(tbl2);

    query2.SELECT("num");
    query.SELECT("id").WHERE().IN("id", query2);
                         

    std::string EXPECTED = "SELECT id FROM test WHERE id IN (SELECT num FROM tbl2)"; 
    
    EXPECT_EQ(EXPECTED, query.str());    
}

TEST(test_querycpp_query, test_exists_sub)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);
    querycpp::query sub_query(tbl);

    std::string EXPECTED = "SELECT id FROM test WHERE EXISTS(SELECT * FROM test WHERE id > 3)"; 

    std::vector<std::string> _columns = {"id", "text"};

    sub_query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().GT(id, std::string("3"));
    query.SELECT(id.name()).WHERE().EXISTS(sub_query);
    EXPECT_EQ(EXPECTED, query.str()); 
}


TEST(test_querycpp_query, test_exists)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT id FROM test WHERE EXISTS"; 

    query.SELECT(id.name()).WHERE().EXISTS();
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_count_column_string)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT COUNT(id) FROM test"; 

    query.COUNT(id.name());
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_count_column)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT COUNT(id) FROM test"; 

    query.COUNT(id);
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_exists_str)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT EXISTS(*) FROM test"; 

    query.SELECT_EXISTS();

    EXPECT_EQ(EXPECTED, query.str());
    
    query.clean();

    query.SELECT_EXISTS(std::string("id")); 

    EXPECTED = "SELECT EXISTS(id) FROM test";
    EXPECT_EQ(EXPECTED, query.str());    
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
