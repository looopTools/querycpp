#ifndef QUERYCPP_HPP
#define QUERYCPP_HPP

#include <string>
#include <vector>
#include <map>

namespace querrycpp
{
class querry
{

public:

    querry* create();
    querry* SELECT(std::string column);
    querry* SELECT(std::vector<std::string> columns); 
        

private:

    const std::string _table;
    const std::vector<std::string> _columns;
    const std::map<std::string, std::vector<std::string>> _constraints; 
    
};
}
#endif /*QUERYCPP_HPP*/
