#include "table.hpp"

#include <cstdint>

namespace querrycpp
{
    table::table(const std::string table, const std::vector<std::string> columns) : _table(table), _columns(columns) {}

    table::table(std::string table, std::map<std::string, std::vector<std::string>> columns_and_settings) : _table(table)
    {
        std::vector<std::string> columns(columns_and_settings.size());
        size_t column_index = 0; 
        for (const auto& [column, constraints] : columns_and_settings)
        {
            columns.at(column_index) = column;
            _column_constraints[column] = constraints;
        }
        _columns = columns; 
    }
}
