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
        SMALL_INT,
        
    
        // Standard String types
        VARCHAR,
        
        // Postgres Number Types
        SERIAL,
        BIG_SERIAL,
        NUMERIC
    
    };

    const std::vector<std::string> data_types_as_strings {"NUMBER", "BIGINT", "SMALL_INT", "VARCHAR", "SERIAL", "BIG_SERIAL", "NUMERIC"};


    std::string type_to_string(data_type Type); 

}

#endif /*QUERYCPP_DATABASE_DATA_TYPES_HPP*/
