#ifndef GLOBAL_DEFINITIONS_H
#define GLOBAL_DEFINITIONS_H

#include <string>
#include <vector>

/**
 * @brief Định nghĩa các loại phúc lợi.
 * Giúp phân loại và quản lý các phúc lợi một cách rõ ràng.
 */
enum class WelfareType
{
    SocialInsurance,    // Bảo hiểm xã hội
    Transportation,     // Phụ cấp đi lại
    Bonus              // Thưởng
};

/**
 * @brief Cấu trúc lưu trữ một bản ghi chấm công.
 * Chứa thông tin về một lần chấm công của nhân viên.
 */
struct AttendanceRecord {
    std::string employeeId;      // Mã nhân viên
    std::string workDate;        // Ngày làm việc (định dạng YYYY-MM-DD)
    std::string checkInTime;     // Giờ check-in (định dạng HH:MM:SS)
    std::string checkOutTime;    // Giờ check-out (định dạng HH:MM:SS)
    std::string dayType;        // // Loại ngày ("normal", "overtime", "leave", "holiday", "leave_unpaid")
};

/**
 * @brief Cấu trúc chứa thông tin chi tiết về lương.
 * Được sử dụng để trả về kết quả tính lương từ SalaryCalculator.
 */
struct SalaryDetails {
    double basicSalary = 0.0;     // Lương cơ bản theo giờ làm việc
    double overtimeSalary = 0.0;  // Lương làm thêm giờ
    double holidaySalary = 0.0;   // Lương làm trong ngày lễ
    double bonuses = 0.0;         // Tổng các khoản thưởng
    double allowances = 0.0;      // Tổng các khoản trợ cấp
    double deductions = 0.0;      // Tổng các khoản khấu trừ
    double totalSalary = 0.0;     // Lương cuối cùng (lương ròng)
};

#endif // GLOBAL_DEFINITIONS_H