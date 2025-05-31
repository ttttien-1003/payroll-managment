#ifndef _TRANSPORTATION_WELFARE_H_
#define _TRANSPORTATION_WELFARE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee
#include <map>

/**
 * @brief Lớp triển khai phúc lợi Phụ cấp đi lại.
 *
 * Lớp này cụ thể hóa các phương thức của IWelfare để tính toán
 * và kiểm tra điều kiện cho Phụ cấp đi lại.
 */
class TransportationWelfare : public IWelfare
{
private:
    WelfareDetails details; ///< Thông tin chi tiết về phúc lợi Phụ cấp đi lại.
    double ratePerKm = 4000;       ///< Số tiền phụ cấp cho mỗi km di chuyển (được lấy theo thời giá, tại 18/05: 4000đ/km)
    std::map<std::string, double> distancesToThuDuc; // Khoảng cách từ các khu vực đến TP. Thủ Đức

public:
    /**
     * @brief Constructor cho TransportationWelfare.
     *
     * @param rate Số tiền phụ cấp đi lại trên mỗi km.
     */
    TransportationWelfare(double rate);

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi Phụ cấp đi lại.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override;

    /**
     * @brief Tính toán tác động của Phụ cấp đi lại đến lương của nhân viên.
     *
     * Tác động này thường là khoản cộng thêm vào lương, được tính bằng
     * số km di chuyển nhân với tỷ lệ phụ cấp trên mỗi km.
     * * Yêu cầu đối tượng IEmployee cung cấp thông tin về khoảng cách di chuyển từ nhà đến công ty.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return Giá trị tác động lên lương (thường là số dương).
     */
    double calculateImpact(const IEmployee& employee) const override;

    /**
     * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận Phụ cấp đi lại hay không.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    bool isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager, int month, int year) const override;
};

#endif // _TRANSPORTATION_WELFARE_H_