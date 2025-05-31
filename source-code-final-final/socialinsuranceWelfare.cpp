#include "socialinsuranceWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

/**
 * @brief Constructor cho SocialInsuranceWelfare.
 *
 * Khởi tạo thông tin chi tiết và tỷ lệ đóng góp cho phúc lợi Bảo hiểm xã hội.
 *
 * @param employeeRate Tỷ lệ đóng góp của nhân viên.
 */
SocialInsuranceWelfare::SocialInsuranceWelfare(double employeeRate)
    : employeeContributionRate(employeeRate)
{
    details.type = WelfareType::SocialInsurance;
    details.name = "Bảo hiểm xã hội.";
    details.description = "Khoản đóng góp BHXH của nhân viên.";
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Bảo hiểm xã hội.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& SocialInsuranceWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của Bảo hiểm xã hội đến lương của nhân viên.
 *
 * Tác động này thường là khoản trừ vào lương của nhân viên, được tính dựa trên
 * tỷ lệ đóng góp của nhân viên và lương đóng bảo hiểm của họ.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (thường là số âm).
 */
double SocialInsuranceWelfare::calculateImpact(const IEmployee& employee) const
{
    // Sử dụng getBaseSalary() để lấy lương cơ bản của nhân viên để tính BHXH
    double salaryForSI = employee.getBaseSalary();

    // Tác động đến lương nhân viên là khoản trừ đi
    double impact = -(salaryForSI * employeeContributionRate);

    return impact; // Trả về tác động đến lương nhân viên
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện tham gia Bảo hiểm xã hội hay không.
 *
 * Điều kiện thường dựa trên loại hợp đồng lao động.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
// Cập nhật chữ ký và thân hàm isEligible
bool SocialInsuranceWelfare::isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager, int month, int year) const {
    // (void)attendanceManager; // Dùng để tránh cảnh báo "unused parameter" nếu không dùng
    // (void)month;
    // (void)year;

    // Sử dụng logic cũ của bạn: nhân viên đủ điều kiện nếu đã làm việc >= 6 tháng
    int monthsWorked = employee.getMonthsWorked(); //
    return (monthsWorked >= 6); //
    // Hoặc nếu bạn muốn một ngưỡng khác, ví dụ 3 tháng:
    // return (monthsWorked >= 3);
}