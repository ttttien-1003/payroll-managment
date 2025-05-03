/**
 * @file Director.h
 * @brief Khai báo lớp Director kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Giám đốc.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của giám đốc.
 */

#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include "IEmployee.h"

class Director : public IEmployee
{
public:
    /**
        * @brief Constructor cho lớp Director.
        *
        * Khởi tạo một đối tượng Giám đốc với các thông tin cơ bản
        * và ngày hết hạn hợp đồng.
        * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
        * các thuộc tính chung.
        *
        * @param id ID duy nhất của giám đốc.
        * @param n Tên đầy đủ của giám đốc.
        * @param addr Địa chỉ liên lạc.
        * @param p Số điện thoại liên lạc.
        * @param info Thông tin bổ sung.
        */
    Director(std::string id, std::string n, std::string addr, std::string p,
        std::string info, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Director".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại Giám đốc.
     *
     * @return Chuỗi "Director".
     * @override
     */
    std::string getEmployeeType() const override;

};

#endif