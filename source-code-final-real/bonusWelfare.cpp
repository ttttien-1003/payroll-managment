#include "bonusWelfare.h"
#include "attendanceManager.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên
#include <set>

/**
 * @brief Constructor cho BonusWelfare.
 *
 * Khởi tạo thông tin chi tiết và số tiền thưởng doanh thu.
 *
 * @param revenueAmount Số tiền thưởng doanh thu.
 */
BonusWelfare::BonusWelfare(double revenueAmount)
    : revenueBonusAmount(revenueAmount)
{
    details.type = WelfareType::Bonus;
    details.name = "Các khoản thưởng";
    details.description = "Thưởng doanh thu.";
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Thưởng.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& BonusWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của các khoản thưởng đến lương của nhân viên.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (tổng số tiền thưởng đủ điều kiện).
 */
double BonusWelfare::calculateImpact(const IEmployee& employee) const
{
    // TODO: Có thể là nếu đi làm đủ 5 ngày/tuần thì được thưởng....

    double totalBonus = revenueBonusAmount;

    return totalBonus; // Trả về tổng tác động
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận thưởng hay không.
 *
 * Điều kiện mới: Nhân viên phải có ít nhất một ngày làm việc thuộc mỗi loại:
 * normal, overtime, và holiday trong kỳ.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @param attendanceManager Tham chiếu hằng đến đối tượng AttendanceManager.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool BonusWelfare::isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager) const
{
    // Tạo một set để lưu các loại ngày làm việc đã tìm thấy của nhân viên
    std::set<std::string> foundDayTypes;

    // Lấy tất cả bản ghi chấm công
    const auto& allRecords = attendanceManager.getRecords();

    // Duyệt qua tất cả các bản ghi
    for (const auto& record : allRecords) {
        // Chỉ xét các bản ghi của nhân viên đang được kiểm tra
        if (record.employeeId == employee.getEmployeeId()) {
            foundDayTypes.insert(record.dayType);
        }
    }

    // Kiểm tra xem set có chứa cả 3 loại yêu cầu hay không
    bool hasNormal = foundDayTypes.count("normal") > 0;
    bool hasOvertime = foundDayTypes.count("overtime") > 0;
    bool hasHoliday = foundDayTypes.count("holiday") > 0;

    // Nếu có đủ cả 3 loại thì đủ điều kiện
    return (hasNormal && hasOvertime && hasHoliday);
}