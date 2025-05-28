/**
 * @file bonusWelfare.cpp
 * @brief Triển khai lớp BonusWelfare.
 *
 * File này chứa cài đặt chi tiết cho các phương thức của lớp BonusWelfare,
 * đại diện cho các khoản thưởng như lương tháng 13 và thưởng doanh thu.
 */

#include "bonusWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

 /**
  * @brief Constructor cho BonusWelfare.
  *
  * Khởi tạo thông tin chi tiết và số tiền cho lương tháng 13 và thưởng doanh thu.
  *
  * @param thirteenthAmount Số tiền lương tháng 13.
  * @param revenueAmount Số tiền thưởng doanh thu.
  */
BonusWelfare::BonusWelfare(double thirteenthAmount, double revenueAmount)
    : thirteenthMonthSalaryAmount(thirteenthAmount), revenueBonusAmount(revenueAmount)
{
    details.type = WelfareType::Bonus;
    details.name = "Cac khoan thuong";
    details.description = "Bao gom luong thang 13 va thuong doanh thu (neu co).";
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
 * @brief Tính toán tác động của các khoản thưởng (lương tháng 13 và thưởng doanh thu) đến lương của nhân viên.
 *
 * Tác động này là tổng của số tiền lương tháng 13 và số tiền thưởng doanh thu.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (tổng số tiền thưởng đủ điều kiện).
 */
double BonusWelfare::calculateImpact(const IEmployee& employee) const
{
    // TODO: Cần thêm logic tính toán thưởng doanh thu phức tạp hơn nếu cần.

    // Tổng tác động là tổng của lương tháng 13 và thưởng doanh thu
    double totalBonus = thirteenthMonthSalaryAmount + revenueBonusAmount;

    return totalBonus; // Trả về tổng tác động
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận thưởng hay không.
 *
 * Điều kiện có thể khác nhau cho lương tháng 13 và thưởng doanh thu,
 * dựa trên thời gian làm việc, hiệu suất, đạt mục tiêu, v.v.
 * Phương thức này hiện tại chỉ là placeholder chung.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện cho ít nhất một loại thưởng, false ngược lại.
 */
bool BonusWelfare::isEligible(const IEmployee& employee) const
{
    // TODO: Cần thêm logic kiểm tra điều kiện phức tạp hơn cho từng loại thưởng.
    // Ví dụ:
    // bool eligibleForThirteenth = employee.getMonthsWorked() >= 12; // Giả định
    // bool eligibleForRevenue = employee.hasMetSalesTarget(); // Giả định

    // Ví dụ đơn giản: Giả định luôn đủ điều kiện cho mục đích minh họa
    return true;
}
