#include <querycpp/querycpp.hpp>

#include <string>
#include <vector>

#include <iostream>

class user
{
public:
    user(const int id, const std::string& name, const std::string& email) : _id(id), _name(name), _email(email) {}
    user (const std::string& name, const std::string& email) : _id(0), _name(name), _email(email) {}

    int id() const
    {
        return _id; 
    }
    
    std::string name() const
    {
        return _name; 
    }

    void name(const std::string& new_name)
    {
        _name = new_name; 
    }

    void email(const std::string& new_email)
    {
        _email = new_email; 
    }

    std::string email() const
    {
        return _email; 
    }
    
    static std::string create(const user& usr)
    {
        std::vector<std::vector<std::string>> vals = {{usr.name(), usr.email()}};
        querycpp::query query(_tbl);
        query.INSERT({_db_name, _db_email}, vals);
        return query.str();         
    }

    static std::string save(const user& usr)
    {
        if (usr.id() == 0)
        {
            return user::create(usr); 
        }

        querycpp::query query(_tbl);
        //query.UPDATE().WHERE().

    }
    
private:
    int _id; 
    std::string _name;
    std::string _email;

private:    
    static querycpp::column _db_id("id", querycpp::type::postgres::numerical::SERIAL, {querycpp::constraints::PRIMARY});
    static querycpp::column _db_name("name", querycpp::type::common::string::VARCHAR, {"255"});
    static querycpp::column _db_email("email", querycpp::type::common::string::VARCHAR, {"255"});
    static querycpp::table _tbl("tbl", {_db_id, _db_name, _db_email});
};


int main(void)
{
    user usr(1, "Jane Doe", "jane@doe.com");
    user usr2("John Doe", "john@doe.com");

    auto usr_create = user::create(usr);
    std::cout << usr_create << "\n";

    auto usr_create2 = user::create(usr2);
    std::cout << usr_create2 << "\n";

    auto usr_save2 = user::save(usr2);

    if (usr_create2 == usr_save2)
    {
        std::cout << "YES User 2 has no id so not created\n"; 
    }
    else
    {
        std::cout << "Something is wrong\n"; 
    }
        
    
}
