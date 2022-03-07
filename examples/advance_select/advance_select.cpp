#include <querycpp/querycpp.hpp>

#include <string>

#include <vector>


#include <iostream>

int main(void)
{
    querycpp::column id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    querycpp::column text("text", querycpp::type::common::string::VARCHAR, {"2"});
    querycpp::table tbl("test", {id, text});
    querycpp::query query(tbl);

    query.SELECT(id);
    std::cout << query.str() << "\n";
    
    query.WHERE();
    std::cout << query.str() << "\n";

    std::vector<std::string> strings = {"John", "Centaur", "Brian", "Dobby"}; 

    query.IN(text, strings);
    std::cout << query.str() << "\n";

    query.AND().GT(id, 1);
    std::cout << query.str() << "\n";

    query.AND().LT(id, 1000);
    std::cout << query.str() << "\n";

    auto first_query = query.str(true);
    auto second_query = query.SELECT(id).WHERE().IN(text, strings).AND().GT(id, 1).AND().LT(id, 1000).str();

    if (first_query == second_query)
    {
        std::cout << "Success :)" << std::endl; 
    }
    else
    {
        std::cout << "You have found a bug please report it :( " << std::endl; 
    }
    
    
    
}
