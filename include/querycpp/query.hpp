#ifndef QUERYCPP_QUERY_HPP
#define QUERYCPP_QUERY_HPP

#include "table.hpp"

#include <string>

namespace querycpp
{
class query
{

public:

    query(const table table);

    /// @param if_not_exists add the IF NOT EXITS check to the create statement
    query& CREATE(bool if_not_exists = false);

    query& SELECT(std::vector<std::string> columns);
    query& SELECT(std::map<std::string, std::string>);
    
    
    query& WHERE();
    query& AND();
    query& OR();

    query& GT(const std::string& lhs, const std::string rhs);
    query& LT(const std::string& lhs, const std::string rhs);
    query& EQ(const std::string& lhs, const std::string rhs); 
    
    
    

    /// @param clean cleans the query string already build 
    std::string str(bool clean = false);
    

    // Cleans current build query
    void clean(); 
    
private:

    table _table;
    std::string _query; 
};
}

#endif /* QUERYCPP_QUERY_HPP */
