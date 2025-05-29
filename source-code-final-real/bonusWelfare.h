#ifndef _BONUS_WELFARE_H_
#define _BONUS_WELFARE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee

/**
 * @brief Lớp triển khai phúc lợi Thưởng.
 *
 * Lớp này cụ thể hóa các phương thức của IWelfare để tính toán
 * và kiểm tra điều kiện cho các khoản thưởng doanh thu.
 */
class BonusWelfare : public IWelfare
{
private:
    WelfareDetails details; ///< Thông tin chi tiết về phúc lợi Thưởng.
    double revenueBonusAmount;          ///< Số tiền thưởng doanh thu.

public:
    /**
     * @brief Constructor cho BonusWelfare.
     *
     * @param thirteenthAmount Số tiền lương tháng 13.
     * @param revenueAmount Số tiền thưởng doanh thu.
     */
    BonusWelfare(double revenueAmount = 0.0);

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi Thưởng.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override;

    /**
     * @brief Tính toán tác động của các khoản thưởng đến lương của nhân viên.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return Giá trị tác động lên lương (thường là số dương).
     */
    double calculateImpact(const IEmployee& employee) const override;

    /**
     * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận thưởng hay không.
     *
     * Điều kiện dựa trên thời gian làm việc, hiệu suất, đạt mục tiêu, v.v.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    bool isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager) const override;
};

#endif // _BONUS_WELFARE_H_