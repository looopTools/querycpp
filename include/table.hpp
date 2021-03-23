#ifndef QUERRYCPP_TABLE_HPP
#define QUERRYCPP_TABLE_HPP

#include <string>
#include <vector>
#include <map>

namespace querrycpp
{
class table
{

public:

    /// TODO change to use columns class; 
    table(const std::string table, const std::vector<std::string> columns);
    table(std::string table, std::vector<std::string> columns, std::map<std::string, std::vector<std::string>> column_settings);
    table(std::string table, std::map<std::string, std::vector<std::string>> columns_and_settings); 
private:

    const std::string _table;
    std::vector<std::string> _columns;
    std::map<std::string, std::vector<std::string>> _column_constraints; 
};
}
#endif /*QUERRYCPP_TABLE_HPP*/
