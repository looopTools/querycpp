#ifndef QUERYCPP_QUERY_HPP
#define QUERYCPP_QUERY_HPP

#include "column.hpp"
#include "table.hpp"

#include "operators.hpp"

#include <fmt/core.h>


#include <string>

#include <type_traits>

namespace querycpp
{
class query
{

public:

    query(const table table);

    /// @param if_not_exists add the IF NOT EXITS check to the create statement
    query& CREATE(bool if_not_exists = false);

    query& SELECT(const std::string& column = "*");

    /// @throws exception if a column in columns does not exist
    query& SELECT(const std::vector<std::string>& columns);
    // TODO: find a good way to implement:
    //       query& SELECT(std::map<std::string, std::string> columns_and_names);
    
    
    query& WHERE();
    query& AND();
    query& OR();

    
    template<typename T1, typename T2> query& GT(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::GT); 
    }

    
    query& LT(const std::string& lhs, const std::string rhs);
    query& EQ(const std::string& lhs, const std::string rhs);

    query& IN(const std::string& column);
    query& IN(const std::string& column, query& sub_query);
    query& IN(const std::string& column, const std::string& params_list);     

    query& BEGIN_NESTED();
    query& END_NESTED();      

    /// @param clean cleans the query string already build 
    std::string str(bool clean = false);
    

    // Cleans current build query
    void clean();

private:

    template<typename T1, typename T2> query& comparison_experssion(const T1 lhs, const T2 rhs, const std::string& op)
    {
        std::string _lhs;
        std::string _rhs; 

        if constexpr (std::is_same<T1, std::string>::value)
        {
            _lhs = lhs; 
        }
        else if constexpr (std::is_same<T1, querycpp::column>::value)
        {
            _lhs = lhs.name();
        }
        else
        {
            _lhs = std::to_string(lhs);
        }

        if constexpr (std::is_same<T2, std::string>::value)
        {
            _rhs = rhs; 
        }
        else if constexpr (std::is_same<T2, querycpp::column>::value)
        {
            _rhs = rhs.name();
        }
        else
        {
            _lhs = std::to_string(lhs);
        }
        _query = fmt::format("{} {} {} {}", _query, _lhs, op, _rhs);
        return *this; 
    }
    
private:

    table _table;
    std::string _query; 
};
}

#endif /* QUERYCPP_QUERY_HPP */
