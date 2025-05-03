#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "IEmployee.h"


class Manager : public IEmployee
{
public:
    Manager(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    std::string getEmployeeType() const override;

};

#endif