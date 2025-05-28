/**
 * @file healthinsuranceWelfare.cpp
 * @brief Triển khai lớp HealthInsuranceWelfare.
 */

#include "healthinsuranceWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

 /**
  * @brief Constructor cho HealthInsuranceWelfare.
  *
  * Khởi tạo thông tin chi tiết và tỷ lệ đóng góp cho phúc lợi Bảo hiểm y tế.
  *
  * @param employeeRate Tỷ lệ đóng góp của nhân viên (thập phân).
  */
HealthInsuranceWelfare::HealthInsuranceWelfare(double employeeRate)
    : employeeContributionRate(employeeRate)
{
    details.type = WelfareType::HealthInsurance;
    details.name = "Bao hiem y te";
    details.description = "Khoan dong gop BHYT cua nhan vien.";
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Bảo hiểm y tế.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& HealthInsuranceWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của Bảo hiểm y tế đến lương của nhân viên.
 *
 * Tác động này thường là khoản trừ vào lương của nhân viên, được tính dựa trên
 * tỷ lệ đóng góp của nhân viên và lương đóng bảo hiểm y tế của họ.
 * 
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (thường là số âm).
 */
double HealthInsuranceWelfare::calculateImpact(const IEmployee& employee) const
{
    // TODO: Cần có cách lấy lương đóng bảo hiểm y tế từ đối tượng IEmployee
    // Hiện tại, dùng một giá trị giả định cho mục đích minh họa.
    double assumedSalaryForHI = 10000000.0; // Giả định lương đóng BHYT là 10 triệu

    // Tác động đến lương nhân viên là khoản trừ đi
    double impact = -(assumedSalaryForHI * employeeContributionRate);

    return impact; // Trả về tác động đến lương nhân viên
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện tham gia Bảo hiểm y tế hay không.
 *
 * Điều kiện dựa trên loại hợp đồng lao động có chính thức hay không.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool HealthInsuranceWelfare::isEligible(const IEmployee& employee) const
{
    return (employee.getEmployeeType() == "Official Employee") || (employee.getEmployeeType() == "Manager")
        || (employee.getEmployeeType() == "Director");
}
