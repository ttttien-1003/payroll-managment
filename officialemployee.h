/**
 * @file OfficialEmployee.h
 * @brief Khai báo lớp OfficialEmployee kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Nhân viên Chính thức.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của nhân viên chính thức.
 */

#ifndef _OFFICIALEMPLOYEE_H_
#define _OFFICIALEMPLOYEE_H_

#include "IEmployee.h"

class OfficialEmployee : public IEmployee
{
public:
    /**
        * @brief Constructor cho lớp OfficialEmployee.
        *
        * Khởi tạo một đối tượng Nhân viên Chính thức với các thông tin cơ bản
        * và ngày hết hạn hợp đồng.
        * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
        * các thuộc tính chung.
        *
        * @param id ID duy nhất của nhân viên chính thức.
        * @param n Tên đầy đủ của nhân viên chính thức.
        * @param addr Địa chỉ liên lạc.
        * @param p Số điện thoại liên lạc.
        * @param info Thông tin bổ sung.
        */
    OfficialEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Official Employee".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại nhân viên Chính thức.
     *
     * @return Chuỗi "Official Employee".
     * @override
     */
    std::string getEmployeeType() const override;

};

#endif