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

TEST(test_querycpp_query, test_create_unqiue)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2", querycpp::constraints::UNIQUE});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2) UNIQUE)";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}

TEST(test_querycpp_query, test_create_default)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2", querycpp::constraints::UNIQUE});

    std::string uuid_func = "uuid_generate_v4()"; 
    querycpp::column token("token", querycpp::type::common::string::UUID, {querycpp::helpers::create_default(uuid_func, true)});

    std::string _name = "Jane Doe";
    querycpp::column name("name", querycpp::type::common::string::VARCHAR, {"255", querycpp::helpers::create_default(_name)});

    bool a = false;

    querycpp::column is_set("is_set", querycpp::type::common::BOOLEAN, {querycpp::helpers::create_default(a)});
    
    querycpp::table tbl("test", {id, text, token, name, is_set});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2) UNIQUE, token UUID DEFAULT uuid_generate_v4(), name VARCHAR(255) DEFAULT 'Jane Doe', is_set BOOLEAN DEFAULT false)";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}

TEST(test_querycpp_query, test_create_default_UUID_postgres)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2", querycpp::constraints::UNIQUE});

    std::string uuid_func = "uuid_generate_v4()"; 
    querycpp::column token("token", querycpp::type::common::string::UUID, {querycpp::constraints::DEFAULT, querycpp::constraints::postgre::uuid::GENERATE_V4});

    std::string _name = "Jane Doe";
    querycpp::column name("name", querycpp::type::common::string::VARCHAR, {"255", querycpp::helpers::create_default(_name)});

    bool a = false;

    querycpp::column is_set("is_set", querycpp::type::common::BOOLEAN, {querycpp::helpers::create_default(a)});
    
    querycpp::table tbl("test", {id, text, token, name, is_set});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2) UNIQUE, token UUID DEFAULT uuid_generate_v4(), name VARCHAR(255) DEFAULT 'Jane Doe', is_set BOOLEAN DEFAULT false)";
    EXPECT_EQ(EXPECTED, query.CREATE().str()); 
}



TEST(test_querycpp_query, test_create_exists)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "CREATE IF NOT EXISTS TABLE test (id SERIAL PRIMARY KEY, text VARCHAR(2))";
    EXPECT_EQ(EXPECTED, query.CREATE(true).str()); 
}

TEST(test_querycpp_query, test_create_references)
{

    querycpp::column id_ref("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::table tbl_ref("ref_tbl", {id_ref});
    
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column idx("idx", querycpp::type::postgres::numerical::SERIAL);    
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, idx, text});
    querycpp::query query(tbl); 

    std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>> references;

    auto test_tuple = std::make_tuple(idx, tbl_ref, id_ref);
    references.emplace_back(test_tuple);
    
    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, idx SERIAL, text VARCHAR(2), FOREING KEY (idx) REFERENCES ref_tbl(id))";
    EXPECT_EQ(EXPECTED, query.CREATE(references).str()); 
}

TEST(test_querycpp_query, test_create_multiple_references)
{

    querycpp::column id_ref("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::table tbl_ref("ref_tbl", {id_ref});
    
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column idx("idx", querycpp::type::postgres::numerical::SERIAL);    
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, idx, text});
    querycpp::query query(tbl); 

    std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>> references;

    auto test_tuple = std::make_tuple(idx, tbl_ref, id_ref);
    references.emplace_back(test_tuple);
    references.emplace_back(test_tuple);    
    
    std::string EXPECTED = "CREATE TABLE test (id SERIAL PRIMARY KEY, idx SERIAL, text VARCHAR(2), FOREING KEY (idx) REFERENCES ref_tbl(id), FOREING KEY (idx) REFERENCES ref_tbl(id))";
    EXPECT_EQ(EXPECTED, query.CREATE(references).str()); 
}

TEST(test_querycpp_query, test_create_references_if_not_exists)
{

    querycpp::column id_ref("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::table tbl_ref("ref_tbl", {id_ref});
    
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column idx("idx", querycpp::type::postgres::numerical::SERIAL);    
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, idx, text});
    querycpp::query query(tbl); 

    std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>> references;

    auto test_tuple = std::make_tuple(idx, tbl_ref, id_ref);
    references.emplace_back(test_tuple);
    
    std::string EXPECTED = "CREATE IF NOT EXISTS TABLE test (id SERIAL PRIMARY KEY, idx SERIAL, text VARCHAR(2), FOREING KEY (idx) REFERENCES ref_tbl(id))";
    EXPECT_EQ(EXPECTED, query.CREATE(references, true).str()); 
}

TEST(test_querycpp_query, test_create_multiple_references_if_not_exists)
{

    querycpp::column id_ref("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::table tbl_ref("ref_tbl", {id_ref});
    
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column idx("idx", querycpp::type::postgres::numerical::SERIAL);    
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, idx, text});
    querycpp::query query(tbl); 

    std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>> references;

    auto test_tuple = std::make_tuple(idx, tbl_ref, id_ref);
    references.emplace_back(test_tuple);
    references.emplace_back(test_tuple);    
    
    std::string EXPECTED = "CREATE IF NOT EXISTS TABLE test (id SERIAL PRIMARY KEY, idx SERIAL, text VARCHAR(2), FOREING KEY (idx) REFERENCES ref_tbl(id), FOREING KEY (idx) REFERENCES ref_tbl(id))";
    EXPECT_EQ(EXPECTED, query.CREATE(references, true).str()); 
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

TEST(test_querycpp_query, test_select_template)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT id, text FROM test"; 

    std::string id_str = id.name();
    std::string text_str = text.name();

        
    EXPECT_EQ(EXPECTED, query.SELECT(id_str, text_str).str());
    query.clear(); 
    

    EXPECT_EQ(EXPECTED, query.SELECT(id.name(), text.name()).str());
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

    std::string col_name = "id";
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(col_name).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN(col_name).str());
}

TEST(test_querycpp_query, test_select_where_in_column)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN"; 

    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(id).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN";

    std::vector<std::string> _columns = {"id", "text"};
    
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN(id).str());
}


TEST(test_querycpp_query, test_select_where_in_str_param_list)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN ($1, $2, $3)"; 

    std::string col_name = "id";
    std::string param_list = "$1, $2, $3";
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(col_name, param_list).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN (13, 1337, 42)";

    std::vector<std::string> _columns = {"id", "text"};

    param_list = "13, 1337, 42";
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN(col_name, param_list).str());
}

TEST(test_querycpp_query, test_select_where_in_column_str_param_list)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::string EXPECTED = "SELECT * FROM test WHERE id IN ($1, $2, $3)"; 

    std::string param_list = "$1, $2, $3";
    EXPECT_EQ(EXPECTED, query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().IN(id, param_list).str());
    query.clear();
    
    EXPECTED = "SELECT id, text FROM test WHERE id IN (13, 1337, 42)";

    std::vector<std::string> _columns = {"id", "text"};

    param_list = "13, 1337, 42";
    EXPECT_EQ(EXPECTED, query.SELECT(_columns).WHERE().IN(id, param_list).str());
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

    std::string col_name = "id";
    query2.SELECT(num.name());
    query.SELECT(id.name()).WHERE().IN(col_name, query2);
                         

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

    std::vector<std::string> vec = {id.name(), query.COUNT_COLUMN(id)};
    query.SELECT(vec);
    EXPECT_EQ(EXPECTED, query.str());
    query.clear();

    vec = {id.name(), query.COUNT_COLUMN(id.name())}; 
    query.SELECT(vec);
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

TEST(test_querycpp_query, test_exists_col)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string EXPECTED = "SELECT EXISTS(id) FROM test"; 

    query.SELECT_EXISTS(id);

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

TEST(test_querycpp_query, test_insert_default_returning)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::vector<std::vector<std::string>> values = {{querycpp::constraints::DEFAULT, querycpp::constraints::DEFAULT}}; 
    
    std::string EXPECTED = "INSERT INTO test (id, text) VALUES (DEFAULT, DEFAULT) RETURNING id"; 

    query.INSERT({id, text}, values).RETURNING(id);

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

TEST(test_querycpp_query, test_UPDATE)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2", querycpp::constraints::UNIQUE});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl); 

    std::vector<std::pair<querycpp::column, std::string>> updates;
    auto update = std::make_pair(id, std::to_string(10)); 
    updates.emplace_back(update);

    update = {text, std::string("'Yoda'")};
    updates.emplace_back(update);    
    
    std::string EXPECTED = "UPDATE test SET id = 10, text = 'Yoda'";
    EXPECT_EQ(EXPECTED, query.UPDATE(updates).str()); 
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



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
