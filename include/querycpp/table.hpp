#ifndef QUERYCPP_TABLE_HPP
#define QUERYCPP_TABLE_HPP

#include "column.hpp"

#include <fmt/core.h>

#include <string>
#include <vector>
#include <map>

#include <type_traits>

#include <stdexcept>

namespace querycpp
{
class table
{

public:

    table() = default;

    table(const std::string& name, const std::vector<column>& columns);

    std::string name() const;
    void name(const std::string& name);

    std::vector<column> columns() const;
    void columns(const std::vector<column>& columns);

    /// has_column identifies if a table contains a column
    /// If a std::string is provided as input param it will check based on name
    /// If a querycpp::column is provided the == operator will be used
    /// @param col is a Template type which should be either std::string or querycpp::column
    /// @return true if the table contains the column otherwise false 
    template<typename T> bool has_column(const T col)
    {

        bool constexpr is_supported = (std::is_same<T, std::string>::value || std::is_same<T, column>::value);
        
        if (!is_supported)
        {
            
            throw std::invalid_argument("col must be of type std::string or type querycpp::column");
        }

        bool constexpr is_string = std::is_same<T, std::string>::value;

        if (is_string)
        {
            for (const auto& _col : _columns)
            {
                if (_col.name() == col)
                {
                    return true; 
                }
            }
        }
        else
        {
            for (const auto& _col : _columns)
            {
                if (_col == col)
                {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:

    std::string _name;
    std::vector<column> _columns;

};
}
#endif /*QUERYCPP_TABLE_HPP*/
