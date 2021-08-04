#ifndef QUERYCPP_QUERY_HPP
#define QUERYCPP_QUERY_HPP

#include "column.hpp"
#include "table.hpp"

#include "querycpp/common.hpp" 
#include "querycpp/commands.hpp"


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

    query& SELECT_EXISTS(const std::string& column = "*");

    /// If param is a column or a string we assume it is a column name
    template<typename T> query& COUNT(T param)
    {

        ///_query = fmt::format("{} {} {} {}", _query, _lhs, op, _rhs);
        
        if constexpr (std::is_same<T, std::string>::value)
        {
            _query = fmt::format("{} {}{}{}{} {} {}", commands::SELECT, commands::COUNT, common::symbols::LEFT_PARENTHESE,
                                 param, common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
            return *this; 
            
        }
        else if constexpr (std::is_same<T, column>::value)
        {
            _query = fmt::format("{} {}{}{}{} {} {}", commands::SELECT, commands::COUNT, common::symbols::LEFT_PARENTHESE,
                                 param.name(), common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
            return *this; 
        }
        else if constexpr (std::is_same<T, query>::value)
        {
            _query = fmt::format("{} {}{}{}{} {} {}", commands::SELECT, commands::COUNT, common::symbols::LEFT_PARENTHESE,
                                 param.str(), common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
            return *this; 
        }
    }

    
    query& EXISTS();        
    query& EXISTS(query& other);
        
    
    query& WHERE();
    query& AND();
    query& OR();

    
    template<typename T1, typename T2> query& GT(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::GT); 
    }

    template<typename T1, typename T2> query& LT(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::LT); 
    }

    template<typename T1, typename T2> query& EQ(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::EQ); 
    }

    query& IN(const std::string& column);
    query& IN(const std::string& column, query& sub_query);
    query& IN(const std::string& column, const std::string& params_list);     

    
    query& BEGIN_NESTED();
    query& END_NESTED();

    query& INSERT(const std::vector<column>& columns);

    /// Inserts into all  
    query& INSERT();    
        

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
            _rhs = std::to_string(rhs);
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
