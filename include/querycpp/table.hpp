#ifndef QUERYCPP_TABLE_HPP
#define QUERYCPP_TABLE_HPP

#include "column.hpp"

#include <string>
#include <vector>
#include <map>

namespace querycpp
{
class table
{

public:

    table(const std::string& name, const std::vector<column>& columns);

    std::string name() const;
    void name(const std::string& name);

    std::vector<column> columns() const;
    void columns(std::vector<column>& columns); 
    
private:

    std::string _name;
    std::vector<column> _columns;

};
}
#endif /*QUERYCPP_TABLE_HPP*/
