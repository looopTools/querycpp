#ifndef QUERRY_COLUMN_HPP
#define QUERRY_COLUMN_HPP

#include <string>
#include <vector>

namespace querycpp
{
class column
{
public:
    //TODO: Change type to enum
    column(std::string name, std::string type, std::vector<std::string> constraints = std::vector<std::string>());

    std::string name() const;
    void name(std::string name);

    std::string type() const;
    void type(std::string type);

    std::vector<std::string> constraints() const;
    void constraints(std::vector<std::string> constraints); 


private:

    std::string _name;
    std::string _type; 
    std::vector<std::string> _constraints;

}; 
}

#endif /*QUERRY_COLUMN_HPP*/
