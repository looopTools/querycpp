#include "query.hpp"
#include "common.hpp"

#include <sstream> 

#include <fmt/core.h>
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
        _query = fmt::format("{} {} > {}", _query, lhs, rhs);
        return *this; 
    }
    
    query& query::LT(const std::string& lhs, const std::string rhs)
    {
        _query = fmt::format("{} {} < {}", _query, lhs, rhs);
        return *this; 
    }
    
    query& query::EQ(const std::string& lhs, const std::string rhs)
    {
        _query = fmt::format("{} {} < {}", _query, lhs, rhs);
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
