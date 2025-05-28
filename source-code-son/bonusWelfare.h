/**
 * @file BonusWelfare.h
 * @brief Khai báo lớp BonusWelfare kế thừa từ IWelfare.
 *
 * Lớp này đại diện cho phúc lợi Thưởng, bao gồm lương tháng 13 và thưởng doanh thu.
 */

#ifndef _BONUS_WELFARE_H_
#define _BONUS_WELFARE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee

 /**
  * @brief Lớp triển khai phúc lợi Thưởng.
  *
  * Lớp này cụ thể hóa các phương thức của IWelfare để tính toán
  * và kiểm tra điều kiện cho các khoản thưởng (lương tháng 13 và thưởng doanh thu).
  */
class BonusWelfare : public IWelfare
{
private:
    WelfareDetails details; ///< Thông tin chi tiết về phúc lợi Thưởng.
    double thirteenthMonthSalaryAmount; ///< Số tiền lương tháng 13.
    double revenueBonusAmount;          ///< Số tiền thưởng doanh thu.

public:
    /**
     * @brief Constructor cho BonusWelfare.
     *
     * @param thirteenthAmount Số tiền lương tháng 13.
     * @param revenueAmount Số tiền thưởng doanh thu.
     */
    BonusWelfare(double thirteenthAmount = 0.0, double revenueAmount = 0.0); // Mặc định là 0 nếu không có thưởng

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi Thưởng.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override;

    /**
     * @brief Tính toán tác động của các khoản thưởng (lương tháng 13 và thưởng doanh thu) đến lương của nhân viên.
     *
     * Tổng tác động là tổng của lương tháng 13 và thưởng doanh thu đủ điều kiện.
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
    bool isEligible(const IEmployee& employee) const override;

    /**
     * @brief Destructor cho BonusWelfare.
     */
    ~BonusWelfare() override = default;
};

#endif // _BONUS_WELFARE_H_
