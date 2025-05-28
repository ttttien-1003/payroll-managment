#include "socialinsuranceWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

/**
 * @brief Constructor cho SocialInsuranceWelfare.
 *
 * Khởi tạo thông tin chi tiết và tỷ lệ đóng góp cho phúc lợi Bảo hiểm xã hội.
 *
 * @param employeeRate Tỷ lệ đóng góp của nhân viên.
 */
SocialInsuranceWelfare::SocialInsuranceWelfare(double employeeRate)
    : employeeContributionRate(employeeRate)
{
    details.type = WelfareType::SocialInsurance;
    details.name = "Bảo hiểm xã hội.";
    details.description = "Khoản đóng góp BHXH của nhân viên.";
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
    // Sử dụng getBaseSalary() để lấy lương cơ bản của nhân viên để tính BHXH
    double salaryForSI = employee.getBaseSalary();

    // Tiền lương dùng để tính đóng bảo hiểm phải lớn hơn mức lương tối thiểu ở vùng I (01/07/2024)
    // Giả định mức lương tối thiểu vùng I là 4,960,000 VND (4960 đơn vị nghìn đồng)
    if (salaryForSI < 4960000) // Đã sửa từ 4960 thành 4960000 để phù hợp với đơn vị tiền tệ
    {
        return 0; // Không đóng BHXH nếu lương thấp hơn mức tối thiểu
    }

    // Tác động đến lương nhân viên là khoản trừ đi
    double impact = -(salaryForSI * employeeContributionRate);

    return impact; // Trả về tác động đến lương nhân viên
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện tham gia Bảo hiểm xã hội hay không.
 *
 * Điều kiện thường dựa trên loại hợp đồng lao động.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool SocialInsuranceWelfare::isEligible(const IEmployee& employee) const
{
    int _m = employee.getMonthsWorked();
    return (_m >= 6);
}