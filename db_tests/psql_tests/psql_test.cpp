#include <querycpp/querycpp.hpp>

#include <fmt/core.h>
#include <pqxx/pqxx>

#include <string>

#include <vector>
#include <utility>

#include <cstdlib>

#include <cassert>

void setup_tables(pqxx::connection& con, std::vector<std::pair<querycpp::table, std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>>>>& tbls)
{

    for (auto& tbl : tbls)
    {
        querycpp::query query(tbl.first);
        if (tbl.second.empty())
        {
            query.CREATE(); 
        }
        else
        {
            query.CREATE(tbl.second); 
        }
        pqxx::work tx(con);
        tx.exec(query.str());
        tx.commit(); 
    }
}

void drop_tables(pqxx::connection& con, std::vector<std::pair<querycpp::table, std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>>>>& tbls)
{
    for (const auto& tbl : tbls)
    {
        querycpp::query query(tbl.first); 
        query.drop(true);
        pqxx::work tx(con);
        tx.exec(query.str());
        tx.commit();         
    }    
}

void insert_into_tbl_test(pqxx::connection& con, querycpp::table& tbl, querycpp::column& text)
{
    querycpp::query query(tbl);

    std::vector<std::vector<std::string>> values; 
    for (size_t i = 0; i < 10; ++i)
    {
        std::string text = fmt::format("'Test text {}'", i);
        values.push_back({text});
    }

    query.INSERT({text}, values);
    pqxx::work tx(con);
    tx.exec(query.str());
    tx.commit();
}

void insert_with_foreing_key(pqxx::connection& con, querycpp::table& tbl, querycpp::column& text, querycpp::column& idx_ref)
{
    (void) con; (void) tbl;

    querycpp::query query(tbl);

    std::vector<std::vector<std::string>> row_values;
    
    for (size_t i = 10; i > 0; --i)
    {
        std::string text = fmt::format("'Referencing {}'", i);
        std::vector<std::string> values = {text, std::to_string(i)};
        row_values.push_back(values);
        
    }

    query.INSERT({text, idx_ref}, row_values);
    pqxx::work tx(con);
    tx.exec(query.str());
    tx.commit(); 
}

void select_all_from_tbl(pqxx::connection& con, querycpp::table& tbl)
{
    querycpp::query query(tbl);
    query.SELECT();
    pqxx::work tx(con);
    pqxx::result res = tx.exec(query.str());
    assert(res.size() == 10);

    for (auto row : res)
    {
        fmt::print("Id: {} Text: {}\n", row[0].as<size_t>(), row[1].as<std::string>());
    }
    tx.commit();
}

void select_all_from_tbl2(pqxx::connection& con, querycpp::table& tbl)
{
    querycpp::query query(tbl);
    query.SELECT();
    pqxx::work tx(con);
    pqxx::result res = tx.exec(query.str());
    for (auto row : res)
    {
        fmt::print("Id: {} Text: {} Ref Id: {}\n", row[0].as<size_t>(), row[1].as<std::string>(), row[2].as<size_t>()); 
    }
    tx.commit(); 
}



int main(void)
{

    fmt::print("DB: {}\n", std::getenv("QUERYCPP_PQXX_DB"));
    fmt::print("User: {}\n", std::getenv("QUERYCPP_PQXX_USER")); 
    fmt::print("Password: {}\n", std::getenv("QUERYCPP_PQXX_PASS"));
    fmt::print("Host: {}\n", std::getenv("QUERYCPP_PQXX_HOST"));
    fmt::print("Port: {}\n", std::getenv("QUERYCPP_PQXX_PORT"));
    
    std::string con_str = fmt::format("dbname = {} user = {} password = {} hostaddr = {} port = {}",
                                      std::getenv("QUERYCPP_PQXX_DB"),
                                      std::getenv("QUERYCPP_PQXX_USER"),
                                      std::getenv("QUERYCPP_PQXX_PASS"),                                      
                                      std::getenv("QUERYCPP_PQXX_HOST"),
                                      std::getenv("QUERYCPP_PQXX_PORT"));

    fmt::print("Starting with connectio{}\n", con_str);
    pqxx::connection con(con_str);

    std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>> references;
    std::vector<std::pair<querycpp::table, std::vector<std::tuple<querycpp::column, querycpp::table, querycpp::column>>>> tables;
    
    
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"255"});
    querycpp::table tbl("test", {id, text});

    auto t1_pair = std::make_pair(tbl, references); 
    tables.push_back(t1_pair);
    
    querycpp::column idx_ref{"idx_ref", querycpp::type::postgres::numerical::SERIAL};
    querycpp::table tbl2("test_ref", {id, text, idx_ref});

    auto reference_tuple = std::make_tuple(idx_ref, tbl, id);
    references.push_back(reference_tuple);

    auto t2_pair = std::make_pair(tbl2, references);
    tables.push_back(t2_pair); 
    
    setup_tables(con, tables);
    insert_into_tbl_test(con, tbl, text);
    insert_with_foreing_key(con, tbl2, text, idx_ref);
    
    select_all_from_tbl(con, tbl);
    select_all_from_tbl2(con, tbl2);
    
    drop_tables(con, tables); 
}
