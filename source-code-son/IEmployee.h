#ifndef _IEMPLOYEE_H_
#define _IEMPLOYEE_H_

#include <string>
#include <iostream>
#include <sstream>

/**
 * @brief Lớp trừu tượng cơ sở đại diện cho một Nhân viên.
 *
 * Lớp này định nghĩa các thuộc tính và hành vi chung
 * mà mọi loại nhân viên trong hệ thống đều có.
 *
 * @see Intern
 * @see OfficialEmployee
 * @see Manager
 * @see Director
 */
class IEmployee 
{
protected:
    std::string employeeId; ///< ID duy nhất của nhân viên.
    std::string name; ///< Tên của nhân viên.
    std::string address; ///< Địa chỉ của nhân viên.
    std::string phone; ///< SĐT của nhân viên.
	std::string email; ///< Email của nhân viên (nếu có).
    ///< Ngày, tháng, năm hết hạn hợp đồng của nhân viên.
    int _d = 0;
    int _m = 0;
    int _y = 0;
    std::string additionalInfo; ///< Các thông tin thêm liên quan đến nhân viên này.

public:
/**
     * @brief Constructor cho lớp IEmployee.
     *
     * Khởi tạo một đối tượng Nhân viên với các thông tin cơ bản.
     * Nó cũng phân tích chuỗi ngày hết hạn hợp đồng từ định dạng YYYY-MM-DD.
     *
     * @param id ID duy nhất của nhân viên.
     * @param n Tên đầy đủ của nhân viên.
     * @param addr Địa chỉ của nhân viên.
     * @param p Số điện thoại liên lạc.
     * @param info Thông tin bổ sung về nhân viên.
     * @param expiryDateString Chuỗi ngày hết hạn hợp đồng theo định dạng "YYYY-MM-DD".
     */
    IEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string info, std::string email, std::string expiryDate);

    /**
     * @brief Destructor ảo mặc định.
     * Đảm bảo giải phóng bộ nhớ đúng khi làm việc với các đối tượng dẫn xuất thông qua con trỏ lớp cơ sở.
     */
    virtual ~IEmployee();
    
    /**
     * @brief Lấy loại nhân viên cụ thể.
     *
     * Đây là phương thức thuần ảo, phải được cài đặt bởi các lớp kế thừa
     * để trả về chuỗi mô tả loại nhân viên đó (ví dụ: "Intern", "Official Employee",...).
     *
     * @return Chuỗi đại diện cho loại nhân viên.
     */
    virtual std::string getEmployeeType() const = 0;

    /**
     * @brief Lấy ID nhân viên.
     * @return Chuỗi ID nhân viên.
     */
    const std::string& getEmployeeId();

    /**
     * @brief Lấy tên nhân viên.
     * @return Chuỗi tên nhân viên.
     */
    const std::string& getName() const;

    /**
     * @brief Lấy địa chỉ nhân viên.
     * @return Chuỗi địa chỉ nhân viên.
     */
    const std::string& getAddress() const;

    /**
     * @brief Lấy SĐT nhân viên.
     * @return Chuỗi SĐT nhân viên.
     */
    const std::string& getPhone() const;

	/**
	 * @brief Lấy email nhân viên.
	 * @return Chuỗi email nhân viên.
	 */
    const std::string& getEmail() const;

    /**
     * @brief Lấy thông tin bổ sung của nhân viên.
     * @return Chuỗi thông tin bổ sung của nhân viên.
     */
    const std::string& getAdditionalInfo() const;

    /**
     * @brief Lấy ngày hết hạn hợp đồng nhân viên.
     * @return Số nguyên ngày hết hạn hợp đồng nhân viên.
     */
    const int& getExpiredDay();

    /**
     * @brief Lấy tháng hết hạn hợp đồng nhân viên.
     * @return Số nguyên tháng hết hạn hợp đồng nhân viên.
     */
    const int& getExpiredMonth();

    /**
     * @brief Lấy năm hết hạn hợp đồng nhân viên.
     * @return Số nguyên năm hết hạn hợp đồng nhân viên.
     */
    const int& getExpiredYear();

    /**
	* @brief Thiết lập ID nhân viên.
	* @param newId ID mới.
    */
	virtual void setId(const std::string& newId) = 0;

    /**
     * @brief Thiết lập tên nhân viên.
    * @param newName Tên mới.
    */
    virtual void setName(const std::string& newName) = 0;

    /**
     * @brief Thiết lập địa chỉ nhân viên.
     * @param newAddress Địa chỉ mới.
     */
    virtual void setAddress(const std::string& newAddress) = 0;

    /**
     * @brief Thiết lập số điện thoại nhân viên.
     * @param newPhone SĐT mới.
     */
    virtual void setPhone(const std::string& newPhone) = 0;

	/**
	 * @brief Thiết lập email nhân viên.
	 * @param newEmail Email mới.
	 */
	virtual void setEmail(const std::string& newEmail) = 0;

    /**
     * @brief Thiết lập thông tin bổ sung.
     * @param info Thông tin bổ sung mới.
     */
    virtual void setAdditionalInfo(const std::string& info) = 0;

	/**
	 * @brief Thiết lập ngày hết hạn hợp đồng.
	 * @param d Ngày hết hạn.
	 * @param m Tháng hết hạn.
	 * @param y Năm hết hạn.
	 */
	virtual void setContractExpiry(int d, int m, int y) = 0;
};

#endif