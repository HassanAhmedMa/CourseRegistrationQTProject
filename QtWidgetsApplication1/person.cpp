#include "person.h"

#include <iostream>





void Person::setName(string& n) {
    name == n;
}

void Person::setId(int id) {
    id = id;
}

void Person::setUsername(string& u) {
    username = u;
}

void Person::setPassword(string& p) {
    password = p;
}



string Person::getName() {
    return name;
}

int Person::getId() {
    return id;
}

string Person::getUsername() {
    return username;
}

string Person::getPassword() {
    return password;
}



void Person::changeUsername(string& newUsername) {
    username = newUsername;
}


void Person::changePassword(string& newPassword) {
    password = newPassword;
}