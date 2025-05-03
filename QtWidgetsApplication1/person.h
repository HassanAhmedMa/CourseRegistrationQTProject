#ifndef PERSON_H
#define PERSON_H
using namespace std;
#include <string>;

class Person {
private:
    string name;
    int id;
    string username;
    string password;



public:

    Person(int id, string name, string username, string password) {
        this->name = name;
        this->id = id;
        this->username = username;
        this->password = password;

    }
    void setName(string& n);
    void setId(int i);
    void setUsername(string& u);
    void setPassword(string& p);

    string getName();
    int getId();
    string getUsername();
    string getPassword();


    void changeUsername(string& newUsername);
    void changePassword(string& newPassword);

};

#endif

