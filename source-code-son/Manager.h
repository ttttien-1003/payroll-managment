/**
 * @file Manager.h
 * @brief Khai báo lớp Manager kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Quản lý.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của quản lý.
 */

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "IEmployee.h"

 /**
  * @brief Lớp đại diện cho nhân viên quản lý (Manager), kế thừa từ IEmployee.
  */
class Manager : public IEmployee {
public:
    /**
     * @brief Constructor cho Manager.
     * @param id Mã nhân viên.
     * @param name Tên nhân viên.
     * @param address Địa chỉ.
     * @param phone SĐT.
     * @param info Thông tin bổ sung.
     * @param email Email.
     * @param expiryDate Ngày hết hạn hợp đồng (dạng YYYY-MM-DD).
     */
    Manager(std::string id, std::string name, std::string address, std::string phone,
        std::string info, std::string email, std::string expiryDate);

    /// Trả về loại nhân viên: "Manager"
    std::string getEmployeeType() const override;

    /// Cài đặt lại các setter
	void setId(const std::string& newId) override;
    void setName(const std::string& newName) override;
    void setAddress(const std::string& newAddress) override;
    void setPhone(const std::string& newPhone) override;
    void setEmail(const std::string& newEmail) override;
    void setAdditionalInfo(const std::string& info) override;
    void setContractExpiry(int d, int m, int y) override;
};

#endif
