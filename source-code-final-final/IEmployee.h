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

    std::string _logicalEmployeeType; // Loại nhân viên logic (ví dụ: "Full-time", "Intern", "Contractual")
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
        std::string email, std::string info, std::string expiryDate, std::string logicalType);

    // Destructor ảo
    virtual ~IEmployee() = default;

    // --- Phương thức thuần ảo ---
    virtual std::string getEmployeeType() const;
    virtual SalaryDetails calculateSalary(const AttendanceManager& attendance, int month, int year, double bonuses, double allowances, double deductions) const = 0; // Thêm month, year

    // --- Getters ---
    const std::string& getEmployeeId() const;
    const std::string& getName() const;
    const std::string& getAddress() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    const std::string& getAdditionInfo() const;
    int getExpDay() const;
    int getExpMonth() const;
    int getExpYear() const;
    std::string getFormattedExpiryDate() const;
    virtual double getBaseSalary() const = 0; // Phương thức thuần ảo để lấy lương cơ bản
    virtual int getMonthsWorked() const { return 0; }
    // --- Phương thức ảo (có thể override) ---
    virtual std::string toCsvString() const = 0;

    // --- Setters ---
    virtual void setName(const std::string& name) { _name = name; }
    virtual void setAddress(const std::string& address) { _address = address; }
    virtual void setPhone(const std::string& phone) { _phone = phone; }
    virtual void setEmail(const std::string& email) { _email = email; }
    virtual void setAdditionalInfo(const std::string& info) { _additionalInfo = info; }

    /**
     * @brief Đặt ngày hết hạn hợp đồng từ chuỗi "YYYY-MM-DD".
     */
    virtual void setExpiryDate(const std::string& expiryDateStr);

    /**
     * @brief Đặt số tháng làm việc. Phải được override bởi các lớp con.
     */
    virtual void setMonthsWorked(int months) { /* Lớp cơ sở không làm gì, hoặc throw lỗi */ }

    // Setter mới cho các thuộc tính cần thay đổi khi loại nhân viên thay đổi
    virtual void setEmployeeId(const std::string& id) { _employeeId = id; }
    virtual void setLogicalEmployeeType(const std::string& type) { _logicalEmployeeType = type; }
    virtual void setBaseSalary(double salary) = 0; // Pure virtual, lớp con phải cài đặt
};

#endif // _IEMPLOYEE_H_