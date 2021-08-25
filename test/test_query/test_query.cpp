#include <gtest/gtest.h>

#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>
#include <querycpp/table.hpp>
#include <querycpp/query.hpp>

#include <querycpp/common.hpp>

TEST(test_querycpp_query, test_create)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2))";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}

TEST(test_querycpp_query, test_select)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test"; 
    
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).str());
    query.clear(); 
    
    EXPECTED = "SELECT id, text FROM test";

    std::vector<std::string> _columns = {"id", "text"};
    

    EXPECT_EQ(EXPECTED, query.SELECT(_columns).str());
}

TEST(test_querycpp_query, test_select_where)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().str());
}

TEST(test_querycpp_query, test_select_where_gt)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id > 3"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().GT(id, std::to_string(3)).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id > 3";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().GT(id, std::to_string(3)).str());
}

TEST(test_querycpp_query, test_select_where_lt)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id < 3"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().LT(id, std::to_string(3)).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id < 3";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().LT(id, std::to_string(3)).str());
}


TEST(test_querycpp_query, test_select_where_in)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN("id").str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN("id").str());
}


TEST(test_querycpp_query, test_select_where_in_str_param_list)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN ($1, $2, $3)"; 
    
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN("id", "$1, $2, $3").str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN (13, 1337, 42)";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN("id", "13, 1337, 42").str());
}

TEST(test_querycpp_query, test_select_where_in_vector_param_list)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED;

    {
        EXPECTED = "SELECT * FROM test WHERE id IN ('$1', '$2', '$3')"; 
        std::vector<std::string> params = {"$1", "$2", "$3"}; 
        EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(id, params).str());
        query.clear();
    }

    {
        EXPECTED = "SELECT * FROM test WHERE id IN ('test', 'john')";         
        std::vector<querycpp::sql_string> params  = {querycpp::sql_string("test"), querycpp::sql_string("john")};
        EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(id, params).str());
        query.clear();        
    }
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN (13, 1337, 42)";

    std::vector<std::string> _columns = {"id", "text"};
    std::vector<int> params = {13, 1337, 42};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN(id, params).str());
}

TEST(test_querycpp_query, test_nested)
{

    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    querycpp::column id2("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column num("num", querycpp::type::postgres::numerical::INTEGER, {querycpp::constraints::PRIMARY});
    querycpp::table tbl2("tbl2", {id2, num});
    querycpp::query query2(tbl2);

    query2.SELECT("num");
    query.SELECT("id").WHERE().IN("id", query2);
                         

    std::string EXPECTED = "SELECT id FROM test WHERE id IN (SELECT num FROM tbl2)"; 
    
    EXPECT_EQ(EXPECTED, query.str());    
}

TEST(test_querycpp_query, test_exists_sub)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
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
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT id FROM test WHERE EXISTS"; 

    query.SELECT(id.name()).WHERE().EXISTS();
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_count_column_string)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT COUNT(id) FROM test"; 

    query.COUNT(id.name());
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_count_column)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT COUNT(id) FROM test"; 

    query.COUNT(id);
    EXPECT_EQ(EXPECTED, query.str()); 
}

TEST(test_querycpp_query, test_count_column_column)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "COUNT(id)";
    EXPECT_EQ(EXPECTED, query.COUNT_COLUMN(id));
    query.clear();
    
    EXPECTED = "SELECT id, COUNT(id) FROM test"; 

    query.SELECT({id.name(), query.COUNT_COLUMN(id)});
    EXPECT_EQ(EXPECTED, query.str());
    query.clear();
    
    query.SELECT({id.name(), query.COUNT_COLUMN(id.name())});
    EXPECT_EQ(EXPECTED, query.str());    


}

TEST(test_querycpp_query, test_exists_str)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT EXISTS(*) FROM test"; 

    query.SELECT_EXISTS();

    EXPECT_EQ(EXPECTED, query.str());
    
    query.clear();

    query.SELECT_EXISTS(std::string("id")); 

    EXPECTED = "SELECT EXISTS(id) FROM test";
    EXPECT_EQ(EXPECTED, query.str());    
}

TEST(test_querycpp_query, test_insert)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "INSERT INTO test (id, text) VALUES"; 

    query.INSERT({id, text});

    EXPECT_EQ(EXPECTED, query.str());
    
    query.clear();

    query.INSERT();
    EXPECT_EQ(EXPECTED, query.str());    
}

TEST(test_querycpp_query, test_insert_values)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::vector<std::vector<std::string>> values = {{"a", "b"}, {"c", "d"}}; 
    
    std::string EXPECTED = "INSERT INTO test (id, text) VALUES (a, b), (c, d)"; 

    query.INSERT({id, text}, values);

    EXPECT_EQ(EXPECTED, query.str());
    
    query.clear();

    query.INSERT(values);
    EXPECT_EQ(EXPECTED, query.str());    
}


TEST(test_querycpp_query, DELETE)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);


    
    std::string EXPECTED = "DELETE FROM test"; 

    query.DELETE(); 

    EXPECT_EQ(EXPECTED, query.str());
}


TEST(test_querycpp_query, group_by_column)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);
    
    std::string EXPECTED = "SELECT * FROM test GROUP BY id"; 

    query.SELECT().GROUP_BY(id); 

    EXPECT_EQ(EXPECTED, query.str());
}

TEST(test_querycpp_query, group_by_str)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);
    
    std::string EXPECTED = "SELECT * FROM test GROUP BY id"; 

    query.SELECT().GROUP_BY(std::string("id")); 

    EXPECT_EQ(EXPECTED, query.str());
}

TEST(test_querycpp_query, group_by_char_ptr)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);
    
    std::string EXPECTED = "SELECT * FROM test GROUP BY id"; 

    char* id_char_ptr = "id";
    
    query.SELECT().GROUP_BY(std::string(id_char_ptr)); 

    EXPECT_EQ(EXPECTED, query.str());
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
