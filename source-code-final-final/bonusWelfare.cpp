#include "bonusWelfare.h"
#include "attendanceManager.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên
#include <set>
#include <string>
#include <sstream>
#include "globalDefinitions.h" // Để sử dụng WelfareType và WelfareDetails
#include "utils.h" // Giả sử bạn có hàm parseWorkDate trong utils.h

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
bool BonusWelfare::isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager, 
                              int targetMonth, int targetYear) const {
    std::set<std::string> foundDayTypes;
    const auto& allRecords = attendanceManager.getRecords();

    for (const auto& record : allRecords) {
        if (record.employeeId == employee.getEmployeeId()) {
            int recYear = 0, recMonth = 0;
            if (record.workDate.length() == 10 && record.workDate[4] == '-' && record.workDate[7] == '-') {
                 try {
                    recYear = std::stoi(record.workDate.substr(0, 4));
                    recMonth = std::stoi(record.workDate.substr(5, 2));
                } catch (const std::exception& e) {
                    // std::cerr << "LOI phan tich ngay (YYYY-MM-DD) trong BonusWelfare '" << record.workDate << "': " << e.what() << std::endl;
                    continue; 
                }
            } else {
                // std::cerr << "CANH BAO: Dinh dang ngay trong record khong dung YYYY-MM-DD (BonusWelfare): " << record.workDate << ". Bo qua." << std::endl;
                continue;
            }

            if (recYear == targetYear && recMonth == targetMonth) {
                foundDayTypes.insert(record.dayType);
            }
        }
    }
    bool hasNormal = foundDayTypes.count("normal") > 0;
    bool hasOvertime = foundDayTypes.count("overtime") > 0;
    bool hasHoliday = foundDayTypes.count("holiday") > 0;
    return (hasNormal && hasOvertime && hasHoliday);
}