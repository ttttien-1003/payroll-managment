#ifndef _IEMPLOYEE_H_
#define _IEMPLOYEE_H_

#include <string>
#include <iostream>
#include <sstream>

class IEmployee 
{
protected:
    std::string employeeId; // MaNV
    std::string name; // TenNV
    std::string address; // DiaChi
    std::string phone; // SDT
    // NgayHetHanHopDong
    int _d = 0;
    int _m = 0;
    int _y = 0;
    std::string additionalInfo; // ThongTinThem

public:
    IEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string info, std::string expiryDate);

    ~IEmployee();

    virtual std::string getEmployeeType() const = 0;

    const std::string& getEmployeeId();
    const std::string& getName();
    const std::string& getAddress();
    const std::string& getPhone();
    const std::string& getAdditionalInfo();
};

#endif