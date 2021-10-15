#ifndef QUERYCPP_CONSTRAINTS_HPP
#define QUERYCPP_CONSTRAINTS_HPP

#include <string>


namespace querycpp::constraints
{
    // Keys
    const std::string PRIMARY = "PRIMARY KEY";
    const std::string UNIQUE = "UNIQUE";
    const std::string DEFAULT = "DEFAULT"; 

namespace postgre
{
    const std::string REFERENCE = "REFERENCE"; 
}

namespace mariadb
{
    const std::string AUTO_INCREMENT = "AUTO_INCREMENT"; 
}
}


#endif /* QUERYCPP_CONSTRAINTS_HPP */
