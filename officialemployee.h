#ifndef _OFFICIALEMPLOYEE_H_
#define _OFFICIALEMPLOYEE_H_

#include "IEmployee.h"


class OfficialEmployee : public IEmployee
{
public:
    OfficialEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    std::string getEmployeeType() const override;

};

#endif