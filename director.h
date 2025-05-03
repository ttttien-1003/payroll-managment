#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include "IEmployee.h"


class Director : public IEmployee
{
public:
    Director(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    std::string getEmployeeType() const override;

};

#endif