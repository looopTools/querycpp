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
    query& create(bool if_not_exists = false);

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
