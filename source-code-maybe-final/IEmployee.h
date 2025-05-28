#ifndef _IEMPLOYEE_H_
#define _IEMPLOYEE_H_

#include "GlobalDefinitions.h"
#include <string>
#include <memory>
#include <iostream>

class AttendanceManager; // Khai báo chuyển tiếp

/**
 * @brief Lớp trừu tượng cơ sở đại diện cho một Nhân viên.
 *
 * Lớp này định nghĩa các thuộc tính và hành vi chung
 * mà mọi loại nhân viên trong hệ thống đều có.
 */
class IEmployee {
protected:
    std::string _employeeId;      // ID duy nhất của nhân viên.
    std::string _name;            // Tên của nhân viên.
    std::string _address;         // Địa chỉ của nhân viên.
    std::string _phone;           // SĐT của nhân viên.
    std::string _email;           // Email của nhân viên.
    std::string _additionalInfo;  // Thông tin bổ sung.
    int _expDay = 0, _expMonth = 0, _expYear = 0; // Ngày, tháng, năm hết hạn hợp đồng.

public:
    /**
     * @brief Constructor cho lớp IEmployee.
     * @param id ID duy nhất của nhân viên.
     * @param name Tên đầy đủ.
     * @param addr Địa chỉ.
     * @param phone SĐT.
     * @param email Email.
     * @param info Thông tin bổ sung.
     * @param expiryDate Chuỗi ngày hết hạn hợp đồng "YYYY-MM-DD".
     */
    IEmployee(std::string id, std::string name, std::string addr, std::string phone,
        std::string email, std::string info, std::string expiryDate);

    // Destructor ảo
    virtual ~IEmployee() = default;

    // --- Phương thức thuần ảo ---
    virtual std::string getEmployeeType() const = 0;
    virtual SalaryDetails calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const = 0;
    virtual double getBaseSalary() const = 0;

    // --- Getters ---
    const std::string& getEmployeeId() const;
    const std::string& getName() const;
    const std::string& getAddress() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    int getExpDay() const;
    int getExpMonth() const;
    int getExpYear() const;

    // --- Phương thức ảo (có thể override) ---
    virtual int getMonthsWorked() const { return 0; }
    virtual bool isMaternityLeave() const { return false; }
    virtual bool isSickLeave() const { return false; }
};

#endif // _IEMPLOYEE_H_