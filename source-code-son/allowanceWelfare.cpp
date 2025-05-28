/**
 * @file allowanceWelfare.cpp
 * @brief Triển khai lớp AllowanceWelfare.
 */

#include "AllowanceWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

 /**
  * @brief Constructor cho AllowanceWelfare.
  *
  * Khởi tạo thông tin chi tiết và số tiền phụ cấp.
  *
  * @param amount Số tiền phụ cấp.
  * @param name Tên cụ thể của loại phụ cấp.
  * @param description Mô tả chi tiết.
  */
AllowanceWelfare::AllowanceWelfare(double amount, const std::string& name, const std::string& description)
    : allowanceAmount(amount)
{
    details.type = WelfareType::Allowance;
    details.name = name;
    details.description = description;
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Phụ cấp khác.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& AllowanceWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của khoản phụ cấp khác đến lương của nhân viên.
 *
 * Logic tính toán có thể phức tạp, phụ thuộc vào loại phụ cấp và thông tin nhân viên.
 * Cần thêm logic để tính toán dựa trên trạng thái (thai sản, ốm đau) của nhân viên.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (số tiền phụ cấp).
 */
double AllowanceWelfare::calculateImpact(const IEmployee& employee) const
{
    // TODO: Cần thêm logic tính toán phụ cấp phức tạp hơn nếu cần
    // Ví dụ: Nếu đây là phụ cấp thai sản, kiểm tra trạng thái thai sản của employee
    // if (employee.isMaternityLeave()) return allowanceAmount;

    // Hiện tại, chỉ trả về số tiền phụ cấp cố định
    return allowanceAmount;
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận phụ cấp này hay không.
 *
 * Điều kiện phụ thuộc vào loại phụ cấp cụ thể và trạng thái của nhân viên.
 * Cần thêm logic kiểm tra trạng thái cụ thể của nhân viên (ốm, thai sản,...)
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool AllowanceWelfare::isEligible(const IEmployee& employee) const
{
    // TODO: Cần thêm logic kiểm tra điều kiện
    // Ví dụ: Kiểm tra trạng thái ốm đau hoặc thai sản của employee
    // if (details.name == "Phu cap thai san" && employee.isMaternityLeave()) return true;
    // if (details.name == "Phu cap om dau" && employee.isSickLeave()) return true;

    // Ví dụ đơn giản: Giả định là nhân viên chính thức
    return (employee.getEmployeeType() == "Official Employee") || (employee.getEmployeeType() == "Manager")
        || (employee.getEmployeeType() == "Director");
}
