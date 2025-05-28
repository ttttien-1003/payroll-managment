/**
 * @file TransportationWelfare.cpp
 * @brief Triển khai lớp TransportationWelfare.
 */

#include "transportationWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

 /**
  * @brief Constructor cho TransportationWelfare.
  *
  * Khởi tạo thông tin chi tiết và số tiền phụ cấp đi lại.
  *
  * @param amount Số tiền phụ cấp đi lại.
  */
TransportationWelfare::TransportationWelfare(double rate)
    : ratePerKm(rate)
{
    details.type = WelfareType::Transportation;
    details.name = "Phu cap di lai";
    details.description = "Phu cap ho tro chi phi di lai hang thang.";
}

/**
 * @brief Lấy thông tin chi tiết về phúc lợi Phụ cấp đi lại.
 *
 * @return Tham chiếu hằng đến đối tượng WelfareDetails.
 */
const WelfareDetails& TransportationWelfare::getDetails() const
{
    return details;
}

/**
 * @brief Tính toán tác động của Phụ cấp đi lại đến lương của nhân viên.
 *
 * Tác động này là tính số tiền dựa theo số km di chuyển từ nhà đến công ty của nhân viên
 * nhân với thời giá của xăng hiện tại.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return Giá trị tác động lên lương (số tiền phụ cấp).
 */
double TransportationWelfare::calculateImpact(const IEmployee& employee) const
{
    // Tác động đến lương nhân viên là khoản cộng thêm
    return ratePerKm * 4000;
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận Phụ cấp đi lại hay không.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool TransportationWelfare::isEligible(const IEmployee& employee) const
{
    return true;
}
