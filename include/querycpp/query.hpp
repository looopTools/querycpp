#ifndef QUERYCPP_QUERY_HPP
#define QUERYCPP_QUERY_HPP

#include "querycpp/column.hpp"
#include "querycpp/table.hpp"

#include "querycpp/common.hpp" 
#include "querycpp/commands.hpp"
#include "querycpp/constraints.hpp"

#include "querycpp/helpers.hpp"

#include "querycpp/operators.hpp"

#include <fmt/core.h>

#include <string>

#include <tuple>

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

    query& CREATE(const std::vector<std::tuple<column, table, column>> references, const bool if_not_exists = false);

    /// Single column select statement
    /// @param column is the name of the column or wildecard. Default is wilde card
    query& SELECT(const std::string& column = "*");

    template<typename T> query& SELECT(const std::vector<T>& columns)
    {
        std::string columns_str = "";

        for (const auto& column : columns)
        {
            columns_str = fmt::format("{}{}, ", columns_str, column_as_str(column));
        }

        columns_str = columns_str.substr(0, columns_str.length() - 2);
        
        if (_query.empty())
        {
            _query = fmt::format("{} {} {} {}", commands::SELECT, columns_str, commands::FROM, _table.name());
        }
        else
        {
            _query = fmt::format("{} {} {} {} {}", _query, commands::SELECT, columns_str, commands::FROM, _table.name());
        }
        return *this;        
    }

    template<typename... T>query& SELECT(T... columns)
    {
        auto columns_str = columns_to_str(columns...);

        if (columns_str.empty())
        {
            return *this;
        }

        if (_query.empty())
        {
            _query = fmt::format("{} {} {} {}", commands::SELECT, columns_str, commands::FROM, _table.name());
        }
        else
        {
            _query = fmt::format("{} {} {} {} {}", _query, commands::SELECT, columns_str, commands::FROM, _table.name());
        }
        return *this;
            

        
    }

    /// Select exists single column
    /// @param column is the name of the column or wilde card. Default is wilde card
    query& SELECT_EXISTS(const std::string& column = "*");

    template<typename T> query& SELECT_EXISTS(T& col)
    {
        std::string col_str; 
        if  constexpr (std::is_same<T, std::string>::value)
        {
            col_str = col; 
        }
        else if constexpr(std::is_same<T, column>::value)
        {
            col_str = col.name(); 
        }

        if (_query.empty())
        {
            _query = fmt::format("{} {}{}{}{} {} {}", commands::SELECT, commands::EXISTS, common::symbols::LEFT_PARENTHESE, col_str, common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
        }
        else
        {
            _query = fmt::format("{} {} {}{}{}{} {} {}", _query, commands::SELECT, commands::EXISTS, common::symbols::LEFT_PARENTHESE, col_str, common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
        }
        return *this; 
    }

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
        if constexpr (std::is_same<T, std::string>::value)
        {
            return fmt::format("{}({})", commands::COUNT, col);
        }

        if constexpr(std::is_same<T, column>::value)
        {
            return fmt::format("{}({})", commands::COUNT, col.name());
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

    template<typename T> query& IN(const T& col)
    {
        if constexpr (std::is_same<T, std::string>::value)
        {
            _query = fmt::format("{} {} {}", _query, col, commands::IN);
        }
        else if constexpr (std::is_same<T, column>::value)
        {
            _query = fmt::format("{} {} {}", _query, col.name(), commands::IN);            
        }
        else
        {
            throw std::runtime_error("Unsupported type for SELECT IN");
        }
            
        return *this;
    }

    /// @param params can be either of type query or std::string where a query will be used as a subquerry, and if string it is a comma seperated list (don't add () we do that for you)
    template<typename T, typename T2> query& IN(const T& col, T2& params)
    {
        IN(col);

        if constexpr (std::is_same<T2, std::string>::value)
        {
            _query = fmt::format("{} {}{}{}", _query, common::symbols::LEFT_PARENTHESE,
                                 params, common::symbols::RIGHT_PARENTHESE);            
        }
        else if constexpr (std::is_same<T2, query>::value)
        {
            _query = fmt::format("{} {}{}{}", _query, common::symbols::LEFT_PARENTHESE,
                                 params.str(), common::symbols::RIGHT_PARENTHESE);
        }
        else
        {
            throw std::runtime_error("Unsupported type for subquery");
        }
            
        return *this;
            
    }

    template<typename T> query& IN(const column col, const std::vector<T> params)
    {
        std::string params_list;

        for (const T& param : params)
        {
            params_list = fmt::format("{}{}, ", params_list, helpers::type_to_sql_str(param));
        }

        params_list = params_list.substr(0, params_list.length() - 2); 

        
        _query = fmt::format("{} {} {} {}{}{}", _query, col.name(), commands::IN,
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

    
    query& UPDATE(const std::vector<std::pair<column, std::string>>& column_update_value)
    {
        std::string update_string = "";
        for (const auto& pair : column_update_value)
        {
            update_string = fmt::format("{}{} = {}, ", update_string, pair.first.name(), pair.second);
        }

        update_string = update_string.substr(0, update_string.length() - 2); 

        if (_query.empty())
        {
            _query = fmt::format("{} {} {} {}", commands::UPDATE, _table.name(), commands::SET, update_string); 
        }
        else
        {
            _query = fmt::format("{} {} {} {} {}", _query, commands::UPDATE, _table.name(), commands::SET, update_string); 
        }

        return *this; 
    }

    /// Group by 
    template<typename T> query& GROUP_BY(T val)
    {
        std::string group_by_col;

        if constexpr (std::is_same<T, std::string>::value)
        {
            group_by_col = val;
        }
        else if constexpr (std::is_same<T, column>::value)
        {
            group_by_col = val.name();
        }
        else
        {
            throw std::runtime_error("Unsupported type for group by"); 
        }
        
        _query = fmt::format("{} {} {}", _query, commands::GROUP_BY, group_by_col); 
        
        return *this;
    }
    
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


    std::string columns_to_str()
    {
        return "";
    }
    
    template<typename T1, typename... T2> std::string columns_to_str(const T1& col, const T2&... columns)
    {

        
        std::string result = fmt::format("{}, {}", column_as_str(col), columns_to_str(columns...));
        // Replace return with the following when C++20 update happens

        return result.at(result.length() - 1) == ' ' ? result.substr(0, result.length() - 2) : result;
    }

    template<typename T> std::string column_as_str(const T& col)
    {
        if constexpr (std::is_same<T, std::string>::value)
        {
            return  col;
        }
        else if constexpr (std::is_same<T, column>::value)
        {
            return col.name();
        }
        else
        {
            throw std::runtime_error("Unsupported type for column / column name");
        }

    }

    
private:

    table _table;
    std::string _query; 
};
}

#endif /* QUERYCPP_QUERY_HPP */
