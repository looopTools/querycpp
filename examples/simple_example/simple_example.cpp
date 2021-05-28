#include <querycpp/constraints.hpp>
#include <querycpp/column.hpp>
#include <querycpp/table.hpp>
#include <querycpp/query.hpp>

#include <querycpp/common.hpp>

#include <iostream>

int main(void)
{
    querycpp::column id("id", querycpp::database::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::database::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::string _query = query.SELECT(querycpp::common::symbols::WILDECARD).WHERE().str();

    std::cout << _query << "\n"; 
    return 0; 
}
