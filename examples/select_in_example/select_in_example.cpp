#include <querycpp/querycpp.hpp>

#include <vector>

#include <cassert>

#include <iostream>

int main()
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    std::vector<int> ids = {1, 2, 3, 4};

    auto str = query.SELECT(id).WHERE().IN(id, ids).str();

    if (assert(str == "SELECT id FROM test WHERE id IN (1 ,2, 3)"))
    {
        std::cout << "Success we have created query: " << str << "\n"; 
    }
    else
    {
        std::cout << "You have encounter an error, please contact the developers of Query C++\n"; 
    }

    return 0; 
}
