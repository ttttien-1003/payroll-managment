#include "OfficialEmployee.h"

/**
* @brief Constructor cho lớp OfficialEmployee.
* @param id Mã nhân viên.
* @param n Tên nhân viên.
* @param addr Địa chỉ nhân viên.
* @param p Số điện thoại.
* @param info Thông tin bổ sung.
* @param expiryDate Ngày hết hạn hợp đồng (định dạng "YYYY-MM-DD").
*/
OfficialEmployee::OfficialEmployee(std::string id, std::string n, std::string addr, std::string p,
    std::string info, std::string email, std::string expiryDate)
    : IEmployee(id, n, addr, p, info, email, expiryDate) {}

/**
*  @brief Destructor ảo cho lớp OfficialEmployee.
* * Giải phóng tài nguyên nếu cần thiết.
* * Trong trường hợp này, không có tài nguyên đặc biệt nào cần giải phóng,
* * nhưng vẫn giữ phương thức này để tuân thủ quy tắc của lớp cơ sở.
*/
OfficialEmployee::~OfficialEmployee() {}

/**
* @brief Lấy loại nhân viên.
* @return Chuỗi "Official Employee".
*/
std::string OfficialEmployee::getEmployeeType() const {
    return "Official Employee";
}

/**
* @brief Thiết lập ID nhân viên.
* @param newId ID mới.
*/
void OfficialEmployee::setId(const std::string& newId) {
	employeeId = newId;
}

/**
* @brief Thiết lập tên nhân viên.
* @param newName Tên mới.
*/
void OfficialEmployee::setName(const std::string& newName) {
    name = newName;
}

/**
* @brief Thiết lập địa chỉ nhân viên.
* @param newAddress Địa chỉ mới.
*/
void OfficialEmployee::setAddress(const std::string& newAddress) {
    address = newAddress;
}

/**
* @brief Thiết lập số điện thoại nhân viên.
* @param newPhone Số điện thoại mới.
*/
void OfficialEmployee::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

/**
* @brief Thiết lập email cho nhân viên.
* @param newEmail Email mới.
*/
void OfficialEmployee::setEmail(const std::string& newEmail) {
	email = newEmail;
}

/**
* @brief Thiết lập thông tin bổ sung cho nhân viên.
* @param info Thông tin mới.
*/
void OfficialEmployee::setAdditionalInfo(const std::string& info) {
    additionalInfo = info;
}

/**
* @brief Thiết lập ngày hết hạn hợp đồng cho nhân viên.
* @param d Ngày hết hạn.
* @param m Tháng hết hạn.   
* @param y Năm hết hạn.
*/
void OfficialEmployee::setContractExpiry(int d, int m, int y) {
    _d = d; _m = m; _y = y;
}
