#ifndef QUERYCPP_CONSTRAINTS_HPP
#define QUERYCPP_CONSTRAINTS_HPP

#include <string>


namespace querycpp::constraints
{
    // Keys
    const std::string PRIMARY = "PRIMARY KEY";
    const std::string UNIQUE = "UNIQUE";
    const std::string DEFAULT = "DEFAULT";
    const std::string NOT_NULL = "NOT NULL"; 


namespace postgre
{
    const std::string REFERENCE = "REFERENCE";
}

namespace postgre::uuid
{
    const std::string GENRATE_RANDOM = "gen_random_uuid ()";
    const std::string GENERATE_V1 = "uuid_generate_v1()";
    const std::string GENERATE_V1MC = "uuid_generate_v1mc()";
    const std::string GENERATE_V3 = "uuid_generate_v3()";    
    const std::string GENERATE_V4 = "uuid_generate_v4()";
    const std::string GENERATE_V5 = "uuid_generate_v5()";
    
    
}

namespace mariadb
{
    const std::string AUTO_INCREMENT = "AUTO_INCREMENT"; 
}

}


#endif /* QUERYCPP_CONSTRAINTS_HPP */
