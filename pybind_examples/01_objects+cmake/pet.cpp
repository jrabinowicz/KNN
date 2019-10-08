#include <iostream>
#include "pet.h"

using namespace std;

Pet::Pet(const string& name): name(name){
    cout << "A pet called " << name << " has been created" << endl;
}

void Pet::setName(const string &name_)
{
    name = name_;
}

const string& Pet::getName() const
{
    return name;
}
