#include "database_data_types.hpp"

namespace querrycpp::database
{
    std::string type_to_string(data_type Type)
    {
        return data_types_as_strings.at(Type); 
    }
}
