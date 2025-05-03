#ifndef _INTERN_H_
#define _INTERN_H_

#include "IEmployee.h"


class Intern : public IEmployee 
{
public:
    Intern(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    std::string getEmployeeType() const override; 

};

#endif