#include "query.hpp"
#include "common.hpp"

#include <sstream> 

#include <fmt/core.h>
namespace querycpp
{
    query::query(table table) : _table(table), _query("") {}

    query& query::create(bool if_not_exists)
    {

        std::stringstream ss;

        if (if_not_exists)
        {
            ss << fmt::format("{} {} {} {} (", CREATE, IF_NOT_EXISTS, TABLE, _table.name());
        }
        else
        {
            ss << fmt::format("{} {} {} (", CREATE, TABLE, _table.name());
        }


        for (const auto& column : _table.columns())
        {
            ss << column.str() << ", "; 
        }

        _query = ss.str().substr(0, ss.str().size() - 2) + ")";
        
        return *this; 
    }

    ///TODO if not exists

    
    

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
