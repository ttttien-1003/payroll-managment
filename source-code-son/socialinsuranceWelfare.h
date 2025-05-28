/**
 * @file socialinsuranceWelfare.h
 * @brief Khai báo lớp socialinsuranceWelfare kế thừa từ IWelfare.
 *
 * Lớp này đại diện cho phúc lợi Bảo hiểm xã hội.
 */

#ifndef _SOCIAL_INSURANCE_WELFARE_H_
#define _SOCIAL_INSURANCE_WELFARE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee

 /**
  * @brief Lớp triển khai phúc lợi Bảo hiểm xã hội.
  *
  * Lớp này cụ thể hóa các phương thức của IWelfare để tính toán
  * và kiểm tra điều kiện cho Bảo hiểm xã hội.
  */
class SocialInsuranceWelfare : public IWelfare
{
private:
    WelfareDetails details; ///< Thông tin chi tiết về phúc lợi Bảo hiểm xã hội.
    double employeeContributionRate; ///< Tỷ lệ đóng góp của nhân viên.
public:
    /**
     * @brief Constructor cho SocialInsuranceWelfare.
     *
     * @param employeeRate Tỷ lệ đóng góp của nhân viên (thập phân, ví dụ 0.08).
     * @param employerRate Tỷ lệ đóng góp của công ty (thập phân, ví dụ 0.175).
     */
    SocialInsuranceWelfare(double employeeRate);

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi Bảo hiểm xã hội.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override;

    /**
     * @brief Tính toán tác động của Bảo hiểm xã hội đến lương của nhân viên.
     *
     * Tác động này thường là khoản trừ vào lương của nhân viên.
     * Logic tính toán có thể dựa trên lương cơ bản hoặc lương đóng bảo hiểm của nhân viên.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return Giá trị tác động lên lương (thường là số âm).
     */
    double calculateImpact(const IEmployee& employee) const override;

    /**
     * @brief Kiểm tra xem nhân viên có đủ điều kiện tham gia Bảo hiểm xã hội hay không.
     *
     * Điều kiện thường dựa trên loại hợp đồng lao động.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    bool isEligible(const IEmployee& employee) const override;

    /**
     * @brief Destructor cho SocialInsuranceWelfare.
     */
    ~SocialInsuranceWelfare() override = default;
};

#endif // _SOCIAL_INSURANCE_WELFARE_H_
