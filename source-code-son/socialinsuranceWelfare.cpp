/**
 * @file socialinsuranceWelfare.cpp
 * @brief Triển khai lớp SocialInsuranceWelfare.
 */

#include "socialinsuranceWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

 /**
  * @brief Constructor cho SocialInsuranceWelfare.
  *
  * Khởi tạo thông tin chi tiết và tỷ lệ đóng góp cho phúc lợi Bảo hiểm xã hội.
  *
  * @param employeeRate Tỷ lệ đóng góp của nhân viên.
  * @param employerRate Tỷ lệ đóng góp của công ty.
  */
SocialInsuranceWelfare::SocialInsuranceWelfare(double employeeRate)
    : employeeContributionRate(employeeRate)
{
    details.type = WelfareType::SocialInsurance;
    details.name = "Bao hiem xa hoi";
    details.description = "Khoan dong gop BHXH cua nhan vien.";
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Bảo hiểm xã hội.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& SocialInsuranceWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của Bảo hiểm xã hội đến lương của nhân viên.
 *
 * Tác động này thường là khoản trừ vào lương của nhân viên, được tính dựa trên
 * tỷ lệ đóng góp của nhân viên và lương đóng bảo hiểm của họ.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (thường là số âm).
 */
double SocialInsuranceWelfare::calculateImpact(const IEmployee& employee) const
{
    // TODO: Cần có cách lấy lương đóng bảo hiểm từ đối tượng IEmployee
    // Hiện tại, dùng một giá trị giả định cho mục đích minh họa.
    double assumedSalaryForSI = 10000000.0; // Giả định lương đóng BHXH là 10 triệu

    // Tác động đến lương nhân viên là khoản trừ đi
    double impact = -(assumedSalaryForSI * employeeContributionRate);

    return impact; // Trả về tác động đến lương nhân viên
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện tham gia Bảo hiểm xã hội hay không.
 *
 * Điều kiện dựa trên loại hợp đồng lao động có chính thức hay không.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool SocialInsuranceWelfare::isEligible(const IEmployee& employee) const
{
    return (employee.getEmployeeType() == "Official Employee") || (employee.getEmployeeType() == "Manager")
        || (employee.getEmployeeType() == "Director"); 
}
