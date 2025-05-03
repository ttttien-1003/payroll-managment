/**
 * @file Intern.h
 * @brief Khai báo lớp Intern kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Nhân viên Thực tập.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của nhân viên thực tập.
 */

#ifndef _INTERN_H_
#define _INTERN_H_

#include "IEmployee.h"

class Intern : public IEmployee
{
public:
    /**
    * @brief Constructor cho lớp Intern.
    *
    * Khởi tạo một đối tượng Nhân viên Thực tập với các thông tin cơ bản
    * và ngày hết hạn hợp đồng.
    * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
    * các thuộc tính chung.
    *
    * @param id ID duy nhất của nhân viên thực tập.
    * @param n Tên đầy đủ của nhân viên thực tập.
    * @param addr Địa chỉ liên lạc.
    * @param p Số điện thoại liên lạc.
    * @param info Thông tin bổ sung.
    * @param expiryDateString Chuỗi ngày hết hạn hợp đồng thực tập theo định dạng "YYYY-MM-DD".
    */
    Intern(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Intern".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại nhân viên Thực tập.
     *
     * @return Chuỗi "Intern".
     * @override
     */
    std::string getEmployeeType() const override;

};

#endif