#ifndef QUERYCPP_DATABASE_DATA_TYPES_HPP
#define QUERYCPP_DATABASE_DATA_TYPES_HPP

#include <string>
#include <vector>
namespace querycpp::database
{
    enum data_type
    {
        
        // Standard Number Types
        NUMBER,
        BIG_INT,
        
    
        // Standard String types
        VARCHAR,
        
        // Postgres Number Types
        SERIAL
    
    };

    const std::vector<std::string> data_types_as_strings {"NUMBER", "BIGINT", "VARCHAR", "SERIAL"};


    std::string type_to_string(data_type Type); 

}

#endif /*QUERYCPP_DATABASE_DATA_TYPES_HPP*/
