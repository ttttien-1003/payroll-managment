#ifndef GLOBAL_DEFINITIONS_H
#define GLOBAL_DEFINITIONS_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric> // For std::accumulate

// Forward declarations
class IEmployee;
class IWelfare;
class Attendance; // Added for SalaryDetails dependency

/**
 * @brief Liệt kê các loại phúc lợi cơ bản.
 *
 * Enum này giúp phân loại các loại phúc lợi một cách rõ ràng. Có thể mở rộng
 * thêm các loại phúc lợi mới khi cần thiết.
 */
enum class WelfareType
{
    SocialInsurance,    ///< Bảo hiểm xã hội.
    HealthInsurance,    ///< Bảo hiểm y tế.
    Allowance,          ///< Phụ cấp khác (thai sản, bệnh tật,...).
    Bonus,              ///< Thưởng doanh thu và lương tháng 13.
    Transportation      ///< Phụ cấp đi lại (ví dụ từ ConcreteWelfareExample)
};

/**
 * @brief Cấu trúc lưu trữ thông tin chấm công của nhân viên.
 * Được sử dụng bởi lớp Attendance.
 */
struct AttendanceRecord {
    std::string employeeId;  // Mã nhân viên
    std::string date;        // Ngày chấm công (yyyy-mm-dd)
    int checkInHour;         // Giờ vào làm
    int checkOutHour;        // Giờ tan làm
    std::string dayType;     // Loại ngày ("normal", "overtime", "leave", "holiday", "leave_unpaid")
};

/**
 * @brief Cấu trúc chứa thông tin chi tiết về lương.
 * Được sử dụng bởi lớp SalaryCalculator.
 */
struct SalaryDetails {
    double basicSalary;     // Lương cơ bản
    double overtimeSalary;  // Lương làm thêm giờ
    double holidaySalary;   // Lương làm trong ngày lễ
    double bonuses;         // Các khoản thưởng
    double allowances;      // Các khoản trợ cấp
    double deductions;      // Các khoản khấu trừ
    double totalSalary;     // Tổng lương sau khi tính toán
};

#endif // GLOBAL_DEFINITIONS_H