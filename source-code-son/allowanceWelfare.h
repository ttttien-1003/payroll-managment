/**
 * @file allowanceWelfare.h
 * @brief Khai báo lớp AllowanceWelfare kế thừa từ IWelfare.
 *
 * Lớp này đại diện cho phúc lợi Phụ cấp khác (thai sản, bệnh tật,...).
 */

#ifndef _ALLOWANCE_WELFARE_H_
#define _ALLOWANCE_WELFARE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee

 /**
  * @brief Lớp triển khai phúc lợi Phụ cấp khác.
  *
  * Lớp này cụ thể hóa các phương thức của IWelfare để tính toán
  * và kiểm tra điều kiện cho các khoản phụ cấp khác.
  */
class AllowanceWelfare : public IWelfare
{
private:
    WelfareDetails details; ///< Thông tin chi tiết về phúc lợi Phụ cấp khác.
    double allowanceAmount; ///< Số tiền phụ cấp.
public:
    /**
     * @brief Constructor cho AllowanceWelfare.
     *
     * @param amount Số tiền phụ cấp.
     * @param name Tên cụ thể của loại phụ cấp (ví dụ: "Phụ cấp thai sản").
     * @param description Mô tả chi tiết về loại phụ cấp.
     */
    AllowanceWelfare(double amount, const std::string& name, const std::string& description);

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi Phụ cấp khác.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override;

    /**
     * @brief Tính toán tác động của khoản phụ cấp khác đến lương của nhân viên.
     *
     * Logic tính toán có thể phụ thuộc vào loại phụ cấp cụ thể (thai sản, ốm đau,...)
     * và thông tin của nhân viên.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return Giá trị tác động lên lương (thường là số dương).
     */
    double calculateImpact(const IEmployee& employee) const override;

    /**
     * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận phụ cấp này hay không.
     *
     * Điều kiện phụ thuộc vào loại phụ cấp cụ thể và trạng thái của nhân viên.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    bool isEligible(const IEmployee& employee) const override;

    /**
     * @brief Destructor cho AllowanceWelfare.
     */
    ~AllowanceWelfare() override = default;
};

#endif // _ALLOWANCE_WELFARE_H_
