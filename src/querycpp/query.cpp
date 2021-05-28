#include "query.hpp"
#include "common.hpp" 
#include "commands.hpp"
#include "operators.hpp"

#include <fmt/core.h>

#include <sstream> 

#include <algorithm>
#include <stdexcept>

namespace querycpp
{
    query::query(table table) : _table(table), _query("") {}

    query& query::CREATE(bool if_not_exists)
    {

        std::stringstream ss;

        if (if_not_exists)
        {
            ss << fmt::format("{} {} {} {} (", commands::CREATE, commands::IF_NOT_EXISTS, commands::TABLE, _table.name());
        }
        else
        {
            ss << fmt::format("{} {} {} (", commands::CREATE, commands::TABLE, _table.name());
        }


        for (const auto& column : _table.columns())
        {
            ss << column.str() << ", "; 
        }

        _query = ss.str().substr(0, ss.str().size() - 2) + ")";
        
        return *this; 
    }

    query& query::SELECT(const std::string& column)
    {
        if (_query.size() == 0)
        {
             _query = fmt::format("{} {} {} {}", commands::SELECT, column, commands::FROM, _table.name());
        }
        else
        {
            _query = fmt::format("{} {} {} {} {}", _query, commands::SELECT, column, commands::FROM, _table.name());
        }
        return *this; 
    }

    query& query::SELECT(const std::vector<std::string>& columns)
    {
        std::vector<std::string> table_columns;
        for (const auto& column : _table.columns())
        {
            table_columns.emplace_back(column.name()); 
        }

        std::string columns_str = "";
        
        for (const auto& column : columns)
        {
            auto found = std::find(std::begin(table_columns), std::end(table_columns), column);
            if (found == std::end(table_columns))
            {
                throw std::runtime_error(fmt::format("column: {} not found for table {}", column, _table.name())); 
            }

            if (columns_str.size() == 0)
            {
                columns_str = fmt::format("{}, ", column); 
            }
            else
            {
                columns_str = fmt::format("{} {},", column); 
            }
        }
        columns_str = columns_str.substr(0, columns_str.size() - 1);

        if (_query.size() == 0)
        {
            _query = fmt::format("{} {} {} {}", commands::SELECT, commands::FROM, _table.name()); 
        }
        else
        {
            _query = fmt::format("{} {} {} {} {}", _query, commands::SELECT, commands::FROM, _table.name()); 
        }
        
        return *this; 
    }

    query& query::WHERE()
    {
        _query = fmt::format("{} {}", _query, commands::WHERE);
        return *this; 
    }

    query& query::AND()
    {
        _query = fmt::format("{} {}", _query, commands::AND);
        return *this; 
    }

    query& query::OR()
    {
        _query = fmt::format("{} {}", _query, commands::OR);
        return *this; 
    }    

    query& query::GT(const std::string& lhs, const std::string rhs)
    {
        _query = fmt::format("{} {} {} {}", _query, lhs, operators::GT, rhs);
        return *this; 
    }
    
    query& query::LT(const std::string& lhs, const std::string rhs)
    {
        _query = fmt::format("{} {} {} {}", _query, lhs, operators::LT, rhs);
        return *this; 
    }
    
    query& query::EQ(const std::string& lhs, const std::string rhs)
    {
        _query = fmt::format("{} {} {} {}", _query, lhs, operators::EQ, rhs);
        return *this;
    }

    query& query::IN()
    {
        _query = fmt::format("{} IN", _query);
        return *this; 
    }

    query& query::IN(query& sub_query)
    {
        _query = fmt::format("{} IN {} {} {}", _query, common::symbols::LEFT_PARENTHESE, sub_query.str(), common::symbols::RIGHT_PARENTHESE);
        return *this; 
    }

    query& query::IN(const std::string& params_list)
    {
        _query = fmt::format("{} IN {} {} {}", _query, common::symbols::LEFT_PARENTHESE, params_list, common::symbols::RIGHT_PARENTHESE);
        return *this; 
    }

    query& query::BEGIN_NESTED()
    {
        _query = fmt::format("{} {}", _query, common::symbols::LEFT_PARENTHESE);
        return *this;
    }
    
    query& query::END_NESTED()
    {
        _query = fmt::format("{} {}", _query, common::symbols::RIGHT_PARENTHESE);
        return *this;   
    }

    std::string query::str(bool clean)
    {
        auto res = _query;
        if (clean)
        {
           _query = "";
        }
        return res; 
    }

    void query::clean()
    {
        _query = ""; 
    }

    
}
