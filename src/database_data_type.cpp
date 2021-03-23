#include "database_data_type.hpp"

namespace querycpp::database
{
    std::string type_to_string(data_type Type)
    {
        return data_types_as_strings.at(Type); 
    }
}
