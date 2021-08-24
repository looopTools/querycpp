#ifndef QUERYCPP_QUERY_HPP
#define QUERYCPP_QUERY_HPP

#include "querycpp/column.hpp"
#include "querycpp/table.hpp"

#include "querycpp/common.hpp" 
#include "querycpp/commands.hpp"

#include "querycpp/helpers.hpp"

#include "querycpp/operators.hpp"

#include <fmt/core.h>

#include <string>

#include <type_traits>

namespace querycpp
{
class query
{

public:

    /// Setup the bases for a query, which is constructed from the provided table
    /// @param table for which the query will be executed 
    query(const table table);

    /// Constructs the CREATE statement for a table 
    /// @param if_not_exists add the IF NOT EXITS check to the create statement
    query& CREATE(bool if_not_exists = false);

    /// Single column select statement
    /// @param column is the name of the column or wildecard. Default is wilde card
    query& SELECT(const std::string& column = "*");

    /// Multi column select
    /// @param a collection of column names 
    /// @throws exception if a column in columns does not exist
    query& SELECT(const std::vector<std::string>& columns);

    /// Select exists single column
    /// @param column is the name of the column or wilde card. Default is wilde card
    query& SELECT_EXISTS(const std::string& column = "*");

    /// Count number of eleements in database
    /// @param param is either a column or the name of a column as string 
    template<typename T> query& COUNT(T param)
    {
        // If param is a column or a string we assume it is a column name        
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

    template<typename T> std::string COUNT_COLUMN(T col)
    {
        std::string pattern = commands::COUNT + "({})";
        
        if constexpr (std::is_same<T, std::string>::value)
        {
            return fmt::format(pattern, col);
        }

        if constexpr(std::is_same<T, column>::value)
        {
            return fmt::format(pattern, col.name()); 
        }

        throw std::runtime_error("Unsupported datatype for count column"); 
    }


    /// Starts EXISTS query
    query& EXISTS();

    /// Build exists query based on another query, this query is treaded as a sub query.
    /// @param other is a sub query
    query& EXISTS(query& other);
        

    /// Starts WHERE clause
    query& WHERE();

    /// Starts AND 
    query& AND();

    /// Starts OR
    query& OR();


    /// Create a < experessen
    /// @param lhs can be a column or a std::string
    /// @param rhs can be a column or a std::string    
    template<typename T1, typename T2> query& GT(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::GT); 
    }

    /// Create a > experessen
    /// @param lhs can be a column or a std::string
    /// @param rhs can be a column or a std::string        
    template<typename T1, typename T2> query& LT(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::LT); 
    }

    /// Create a = experessen
    /// @param lhs can be a column or a std::string
    /// @param rhs can be a column or a std::string        
    template<typename T1, typename T2> query& EQ(const T1 lhs, const T2 rhs)
    {
        return comparison_experssion(lhs, rhs, operators::EQ); 
    }

    query& IN(const std::string& column);
    query& IN(const std::string& column, query& sub_query);
    query& IN(const std::string& column, const std::string& params_list);

    template<typename T>
    query& IN(const column column, const std::vector<T> params)
    {
        std::string params_list;

        for (const T& param : params)
        {
            params_list = fmt::format("{}{}, ", params_list, helpers::type_to_sql_str(param));
        }

        params_list = params_list.substr(0, params_list.length() - 2); 

        
        _query = fmt::format("{} {} {} {}{}{}", _query, column.name(), commands::IN,
                             common::symbols::LEFT_PARENTHESE, params_list, common::symbols::RIGHT_PARENTHESE);
        return *this;
        
    }

    
    query& BEGIN_NESTED();
    query& END_NESTED();

    query& INSERT(const std::vector<column>& columns);

    /// Inserts into all  
    query& INSERT();    

    query& INSERT(const std::vector<column>& columns, std::vector<std::vector<std::string>> values);
    query& INSERT(std::vector<std::vector<std::string>> values);

    query& DELETE(); 
    
    /// @param clean cleans the query string already build 
    std::string str(bool clear_query = false);
    

    // Cleans current build query
    void clear();

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

    std::string strip_command_from_column_name(const std::string& col_with_cmd, const std::string& start = common::symbols::LEFT_PARENTHESE,
                                               const std::string& end = common::symbols::RIGHT_PARENTHESE);
    
private:

    table _table;
    std::string _query; 
};
}

#endif /* QUERYCPP_QUERY_HPP */
