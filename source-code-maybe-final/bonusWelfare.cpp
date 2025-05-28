#include "bonusWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

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
    // bool eligibleForRevenueBonus = employee.metSalesTarget(); // Giả định có phương thức metSalesTarget()

    // Hiện tại, giả định tất cả nhân viên đều đủ điều kiện nhận thưởng nếu có giá trị
    return (revenueBonusAmount > 0);
}