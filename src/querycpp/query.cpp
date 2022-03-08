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
            ss << fmt::format("{} {} {} {} (", commands::CREATE, commands::TABLE, commands::IF_NOT_EXISTS , _table.name());
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

    query& query::CREATE(const std::vector<std::tuple<column, table, column>> references, const bool if_not_exists)
    {

        CREATE(if_not_exists);
        
        std::stringstream reference_stream;

        for (const auto& reference : references)
        {
            column loc_col;
            table ref_tbl;
            column ref_col;

            std::tie(loc_col, ref_tbl, ref_col) = reference; 
                
            reference_stream << fmt::format("{} {}{}{} {} {}{}{}{}, ",
                                            commands::FOREING_KEY, common::symbols::LEFT_PARENTHESE,
                                            loc_col.name(),
                                            common::symbols::RIGHT_PARENTHESE,
                                            commands::REFERENCES,
                                            ref_tbl.name(),
                                            common::symbols::LEFT_PARENTHESE,
                                            ref_col.name(),
                                            common::symbols::RIGHT_PARENTHESE);
        }

        auto reference_str = reference_stream.str();
        reference_str = reference_str.substr(0, reference_str.length() - 2);

        _query = fmt::format("{}, {}{}", _query.substr(0, _query.length() - 1),
                             reference_str, common::symbols::RIGHT_PARENTHESE);
        
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
            ss << column.name() << ", ";
        }
        auto columns_str  = ss.str();
        columns_str = columns_str.substr(0, columns_str.length() - 2);

        std::string tmp_query = fmt::format("{} {} {} {}{}{} {}", commands::INSERT, commands::INTO, _table.name(),
                                            common::symbols::LEFT_PARENTHESE, columns_str, common::symbols::RIGHT_PARENTHESE, commands::VALUES);  
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

    query& query::INSERT(const std::vector<column>& columns, std::vector<std::vector<std::string>> values)
    {
        INSERT(columns);

        std::stringstream ss; 

        for (const auto& value_row : values)
        {
            ss << common::symbols::LEFT_PARENTHESE; 

            std::stringstream value_stream;
            
            for (const auto& value : value_row)
            {
                value_stream << value << ", ";
            }

            auto value_str = value_stream.str();
            value_str = value_str.substr(0, value_str.length() - 2);
            ss << value_str << common::symbols::RIGHT_PARENTHESE << ", "; 
        }

        auto values_str = ss.str();
        values_str = values_str.substr(0, values_str.length() - 2);
        _query = fmt::format("{} {}", _query, values_str);
        return *this; 
    }

    query& query::INSERT(std::vector<std::vector<std::string>> values)
    {
        return INSERT(_table.columns(), values);
    }

    query& query::DELETE()
    {

        if (_query.empty())
        {
            _query = fmt::format("{} {} {}", commands::DELETE, commands::FROM, _table.name()); 
        }
        else
        {
            _query = fmt::format("{} {} {} {}", _query, commands::DELETE, commands::FROM, _table.name()); 
        }
        
        return *this; 
    }
    

    std::string query::str(bool clear_query)
    {
        auto res = _query;
        if (clear_query)
        {
            clear();
        }
        return res; 
    }

    void query::clear()
    {
        _query.clear(); 
    }

    std::string query::strip_command_from_column_name(const std::string& col_with_cmd, const std::string& start, const std::string& end)
    {
        // +1 due to need for offset when using substr
        auto _start = col_with_cmd.find(start) + 1;

        // We need the length of the col name not the pos of end
        auto _end = col_with_cmd.find(end) - _start;
        return col_with_cmd.substr(_start, _end); 
    }    
}
