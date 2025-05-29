#include "transportationWelfare.h"
#include "IEmployee.h" // Cần thiết để truy cập thông tin nhân viên

/**
 * @brief Constructor cho TransportationWelfare.
 *
 * Khởi tạo thông tin chi tiết và số tiền phụ cấp đi lại.
 *
 * @param rate Số tiền phụ cấp đi lại trên mỗi km.
 */
TransportationWelfare::TransportationWelfare(double rate)
    : ratePerKm(rate)
{
    details.type = WelfareType::Transportation;
    details.name = "Phụ cấp đi lại";
    details.description = "Phụ cấp hỗ trợ chi phí đi lại hàng tháng.";

    // Khởi tạo dữ liệu khoảng cách
    // Key là tên khu vực/quận, Value là khoảng cách đến TP. Thủ Đức (km)
    distancesToThuDuc["Quan 1, TP.HCM"] = 15.0;
    distancesToThuDuc["Quan 2, TP.HCM"] = 8.0; // Đã là một phần của TP. Thủ Đức
    distancesToThuDuc["Quan 3, TP.HCM"] = 17.0;
    distancesToThuDuc["Quan 4, TP.HCM"] = 19.8;
    distancesToThuDuc["Quan 7, TP.HCM"] = 20.6;
    distancesToThuDuc["Nhon Trach, Dong Nai"] = 42.6;
    distancesToThuDuc["Thuan An, Binh Duong"] = 13.0;
    distancesToThuDuc["Di An, Binh Duong"] = 5.8;
    // Thêm các khu vực khác nếu cần
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
    // Giả sử công ty ở Thành phố Thủ Đức (Tp.HCM)
    double employeeDistance = 0.0;
    std::string employeeAddress = employee.getAddress(); // Lấy địa chỉ của nhân viên

    // Tìm kiếm khoảng cách dựa trên địa chỉ của nhân viên
    // Hàm này sẽ kiểm tra xem địa chỉ của nhân viên có chứa tên của bất kỳ vùng lân cận nào không.
    bool found = false;
    for (const auto& pair : distancesToThuDuc)
    {
        // Kiểm tra xem địa chỉ nhân viên có chứa tên vùng lân cận không
        // Sử dụng find để tìm kiếm chuỗi con, không phân biệt hoa thường nếu cần
        if (employeeAddress.find(pair.first) != std::string::npos)
        {
            employeeDistance = pair.second;
            found = true;
            break; // Tìm thấy khớp, thoát vòng lặp
        }
    }

    if (!found)
    {
        return 0.0; // Trả về 0 nếu không tìm thấy khoảng cách
    }

    // Tác động đến lương nhân viên là khoản cộng thêm
    // Công thức tính phúc lợi: tỷ lệ trên mỗi km * khoảng cách
    double impact = ratePerKm * employeeDistance;

    return impact; // Trả về giá trị phúc lợi
}

/**
 * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận Phụ cấp đi lại hay không.
 *
 * @param employee Tham chiếu hằng đến đối tượng IEmployee.
 * @return true nếu nhân viên đủ điều kiện, false ngược lại.
 */
bool TransportationWelfare::isEligible(const IEmployee& employee, const AttendanceManager& attendanceManager) const
{
    return true;
}