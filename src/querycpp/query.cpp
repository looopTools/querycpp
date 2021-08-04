#include "querycpp/query.hpp"

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
                columns_str = fmt::format("{},", column); 
            }
            else
            {
                columns_str = fmt::format("{} {},", columns_str, column); 
            }
        }
        columns_str = columns_str.substr(0, columns_str.size() - 1);

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

    query& query::SELECT_EXISTS(const std::string& column)
    {
        if (_query.empty())
        {
            _query = fmt::format("{} {}{}{}{} {} {}", commands::SELECT, commands::EXISTS, common::symbols::LEFT_PARENTHESE, column, common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
        }
        else
        {
            _query = fmt::format("{} {} {}{}{}{} {} {}", _query, commands::SELECT, commands::EXISTS, common::symbols::LEFT_PARENTHESE, column, common::symbols::RIGHT_PARENTHESE, commands::FROM, _table.name());
        }
        return *this; 
    }

    query& query::EXISTS()
    {
        _query = fmt::format("{} {}", _query, commands::EXISTS);
        return *this;
    }
        
    query& query::EXISTS(query& other)
    {
        _query = fmt::format("{} {}{}{}{}", _query, commands::EXISTS, common::symbols::LEFT_PARENTHESE, other.str(), common::symbols::RIGHT_PARENTHESE);
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

    query& query::IN(const std::string& column)
    {
        _query = fmt::format("{} {} {}", _query, column, commands::IN);
        return *this; 
    }

    query& query::IN(const std::string& column, query& sub_query)
    {
        _query = fmt::format("{} {} {} {}{}{}", _query, column, commands::IN, common::symbols::LEFT_PARENTHESE, sub_query.str(), common::symbols::RIGHT_PARENTHESE);
        return *this; 
    }

    query& query::IN(const std::string& column, const std::string& params_list)
    {
        _query = fmt::format("{} {} {} {}{}{}", _query, column, commands::IN, common::symbols::LEFT_PARENTHESE, params_list, common::symbols::RIGHT_PARENTHESE);
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

    query& query::INSERT(const std::vector<column>& columns)
    {
        
        std::stringstream ss;

        for (const auto& column : columns)
        {
            ss << column.name() << ",";
        }
        auto columns_str  = ss.str();
        columns_str = columns_str.substr(0, columns_str.length() - 1);

        std::string tmp_query = fmt::format("{} {} {} {} {} {} {}", commands::INSERT, commands::INTO, commands::VALUES,
                                            common::symbols::LEFT_PARENTHESE, columns_str, common::symbols::RIGHT_PARENTHESE);  
        if (_query.empty())
        {
            _query = tmp_query; 
        }
        else
        {
            _query = fmt::format("{} {}", _query, tmp_query);
        }
        return *this; 
    }

    query& query::INSERT()
    {
        return INSERT(_table.columns()); 
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
