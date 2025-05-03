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

class Manager : public IEmployee
{
public:
    /**
        * @brief Constructor cho lớp Manager.
        *
        * Khởi tạo một đối tượng Quản lý với các thông tin cơ bản
        * và ngày hết hạn hợp đồng.
        * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
        * các thuộc tính chung.
        *
        * @param id ID duy nhất của quản lý.
        * @param n Tên đầy đủ của quản lý.
        * @param addr Địa chỉ liên lạc.
        * @param p Số điện thoại liên lạc.
        * @param info Thông tin bổ sung.
        */
    Manager(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Manager".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại Quản lý.
     *
     * @return Chuỗi "Manager".
     * @override
     */
    std::string getEmployeeType() const override;

};

#endif