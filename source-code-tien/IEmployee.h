#ifndef _IEMPLOYEE_H_
#define _IEMPLOYEE_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory> // Cho std::shared_ptr

// Khai báo chuyển tiếp để tránh include vòng lặp
class Attendance; // Cần thiết cho calculateSalary
struct SalaryDetails; // Cần thiết cho calculateSalary

/**
 * @brief Lớp trừu tượng cơ sở đại diện cho một Nhân viên.
 *
 * Lớp này định nghĩa các thuộc tính và hành vi chung
 * mà mọi loại nhân viên trong hệ thống đều có.
 *
 * @see Intern
 * @see FulltimeEmployee
 * @see ContractualEmployee
 * @see Director
 */
class IEmployee
{
protected:
    std::string employeeId; ///< ID duy nhất của nhân viên.
    std::string name; ///< Tên của nhân viên.
    std::string address; ///< Địa chỉ của nhân viên.
    std::string phone; ///< SĐT của nhân viên.
    std::string expiryDate; ///< Ngày hết hạn hợp đồng hoặc thực tập (YYYY-MM-DD).

public:
    /**
     * @brief Constructor cho lớp IEmployee.
     *
     * Khởi tạo một đối tượng Nhân viên với các thông tin cơ bản.
     *
     * @param id ID duy nhất của nhân viên.
     * @param n Tên đầy đủ của nhân viên.
     * @param addr Địa chỉ của nhân viên.
     * @param p Số điện thoại liên lạc.
     * @param expiryDateString Chuỗi ngày hết hạn hợp đồng theo định dạng "YYYY-MM-DD".
     */
    IEmployee(std::string id, std::string n, std::string addr, std::string p,
        std::string expiryDateString = "");

    /**
     * @brief Destructor ảo mặc định.
     * Đảm bảo giải phóng bộ nhớ đúng khi làm việc với các đối tượng dẫn xuất thông qua con trỏ lớp cơ sở.
     */
    virtual ~IEmployee() = default;

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
     * @brief Tính toán chi tiết lương của nhân viên.
     *
     * Đây là phương thức thuần ảo, phải được cài đặt bởi các lớp kế thừa.
     * Nó sẽ sử dụng thông tin chấm công và các khoản phúc lợi/trừ lương
     * để tính toán chi tiết lương và tổng lương ròng.
     *
     * @param attendance Đối tượng Attendance chứa thông tin chấm công.
     * @param bonuses Tổng các khoản thưởng.
     * @param allowances Tổng các khoản phụ cấp.
     * @param deductions Tổng các khoản khấu trừ (ví dụ: bảo hiểm).
     * @return SalaryDetails Đối tượng chứa thông tin chi tiết về lương.
     */
    virtual SalaryDetails calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const = 0;

    /**
     * @brief Lấy lương cơ bản (trước khi tính phúc lợi/trừ lương) của nhân viên.
     * Đây là phương thức thuần ảo, phải được cài đặt bởi các lớp kế thừa.
     * @return double Giá trị lương cơ bản của nhân viên.
     */
    virtual double getBaseSalary() const = 0;

    /**
     * @brief Lấy ID nhân viên.
     * @return Chuỗi ID nhân viên.
     */
    const std::string& getEmployeeId() const;

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
     * @brief Lấy số điện thoại nhân viên.
     * @return Chuỗi số điện thoại nhân viên.
     */
    const std::string& getPhone() const;

    /**
     * @brief Kiểm tra xem nhân viên có đang trong thời gian nghỉ thai sản không.
     * Phương thức ảo, các lớp con có thể ghi đè để cung cấp logic cụ thể.
     * @return true nếu đang nghỉ thai sản, false nếu không.
     */
    virtual bool isMaternityLeave() const { return false; }

    /**
     * @brief Kiểm tra xem nhân viên có đang trong thời gian nghỉ ốm không.
     * Phương thức ảo, các lớp con có thể ghi đè để cung cấp logic cụ thể.
     * @return true nếu đang nghỉ ốm, false nếu không.
     */
    virtual bool isSickLeave() const { return false; }

    /**
     * @brief Lấy số tháng nhân viên đã làm việc.
     * Được sử dụng để tính toán các loại thưởng yêu cầu thâm niên.
     * @return int Số tháng đã làm việc.
     */
    virtual int getMonthsWorked() const { return 0; } // Mặc định là 0, các lớp con có thể ghi đè
};

#endif // _IEMPLOYEE_H_