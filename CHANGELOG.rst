* [IMPORTANT] [latest] 3.0.5
  - Fixing mispelling of FOREIGN
  - Moving FOREIGN KEY from commands to constraints (makes more sense) and renames to just FOREIGN 
* 3.0.4
  - Fixing error for CREATE IF NOT EXISTS 
* 1.2.0
 - Moved back to using README.md instead of RST version
 - Added datat type for UUID
 - Added Unique and Default constraints
 - Added UPDATE
 - Using reference
 - (Internal) we swapped to using name() instead of str() inside for increased readability, we recommend you do the same
 - We renamed input params col to column 
  
* 1.1.0
  - Added support for FOREING KEY REFERENCE
  - Added a SQL safe string type
  - Added IN function using column instead of std::string, the later is still an option
  - Added COUNT as an argument option on SELECT
  - Added a type to string function for all data types supported by QueryC++
  - Added SELECT based on columns and not just std::string
  - Added Group by
  - Added SELECT COUNT and SELECT EXISTS
  - Enabled test build and running using CMAKE 
  
* 1.0.0

  - Removed support for `char*` 
