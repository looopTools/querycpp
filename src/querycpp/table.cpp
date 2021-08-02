#include "querycpp/table.hpp"

#include <cstdint>

namespace querycpp
{
    table::table(const std::string& name, const std::vector<column>& columns) : _name(name), _columns(columns)
    {}

    std::string table::name() const
    {
        return _name; 
    }
    
    void table::name(const std::string& name)
    {
        _name = name; 
    }

    std::vector<column> table::columns() const
    {
        return _columns; 
    }
    
    void table::columns(const std::vector<column>& columns)
    {
        _columns = columns; 
    }
}
