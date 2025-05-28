#ifndef _OFFICIAL_EMPLOYEE_H_
#define _OFFICIAL_EMPLOYEE_H_

#include "IEmployee.h"

/**
 * @brief Lớp đại diện cho nhân viên chính thức (Official Employee).
 *
 * Kế thừa từ IEmployee và triển khai các phương thức getter/setter cụ thể cho loại nhân viên này.
 */
class OfficialEmployee : public IEmployee
{
public:
    /**
     * @brief Khởi tạo một nhân viên chính thức với thông tin chi tiết.
     * @param id Mã nhân viên.
     * @param n Tên nhân viên.
     * @param addr Địa chỉ nhân viên.
     * @param p Số điện thoại.
     * @param info Thông tin bổ sung.
     * @param expiryDate Ngày hết hạn hợp đồng (định dạng "YYYY-MM-DD").
     */
    OfficialEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string info, std::string email, std::string expiryDate);

    /**
     * @brief Destructor ảo.
     */
    ~OfficialEmployee() override;

    /**
     * @brief Lấy loại nhân viên.
     * @return Chuỗi "Official Employee".
     */
    std::string getEmployeeType() const override;

	/**
	 * @brief Thiết lập ID nhân viên.
	 * @param newId ID mới.
     */
	void setId(const std::string& newId) override;

    /**
     * @brief Thiết lập tên nhân viên.
     * @param newName Tên mới.
     */
    void setName(const std::string& newName) override;

    /**
     * @brief Thiết lập địa chỉ nhân viên.
     * @param newAddress Địa chỉ mới.
     */
    void setAddress(const std::string& newAddress) override;

    /**
     * @brief Thiết lập số điện thoại nhân viên.
     * @param newPhone Số điện thoại mới.
     */
    void setPhone(const std::string& newPhone) override;

	/**
	 * @brief Thiết lập email cho nhân viên.
	 * @param newEmail Email mới.
	 */
	void setEmail(const std::string& newEmail) override;

    /**
     * @brief Thiết lập thông tin bổ sung cho nhân viên.
     * @param info Thông tin mới.
     */
    void setAdditionalInfo(const std::string& info) override;

	/**
	 * @brief Thiết lập ngày hết hạn hợp đồng cho nhân viên.
	 * @param d Ngày hết hạn.
	 * @param m Tháng hết hạn.
	 * @param y Năm hết hạn.
	 */
	void setContractExpiry(int d, int m, int y) override;
};

#endif
