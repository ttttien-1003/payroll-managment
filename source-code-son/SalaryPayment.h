#ifndef SALARY_PAYMENT_H
#define SALARY_PAYMENT_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

/**
 * @class SalaryPayment
 * @brief Lớp quản lý thông tin thanh toán lương của nhân viên.
 *
 * Lớp này lưu trữ thông tin thanh toán lương của nhân viên, bao gồm mã nhân viên,
 * ngày thanh toán, số tiền thanh toán, số tiền ứng trước, và ghi chú. Nó cũng cung cấp
 * các phương thức để chuyển đổi dữ liệu sang định dạng CSV và tạo đối tượng từ chuỗi CSV.
 */
class SalaryPayment {
private:
    std::string employeeId;  ///< Mã nhân viên
    std::string paymentDate; ///< Ngày thanh toán (định dạng YYYY-MM-DD)
    double amount;           ///< Số tiền thanh toán
    double advance;          ///< Số tiền ứng trước
    std::string notes;       ///< Ghi chú

public:
    /**
     * @brief Constructor khởi tạo đối tượng SalaryPayment.
     *
     * @param employeeId Mã nhân viên.
     * @param paymentDate Ngày thanh toán (định dạng YYYY-MM-DD).
     * @param amount Số tiền thanh toán.
     * @param advance Số tiền ứng trước.
     * @param notes Ghi chú.
     */
    SalaryPayment(const std::string& employeeId, const std::string& paymentDate, double amount, double advance, const std::string& notes);

    /**
     * @brief Lấy mã nhân viên.
     *
     * @return Mã nhân viên.
     */
    const std::string& getEmployeeId() const;

    /**
     * @brief Lấy ngày thanh toán.
     *
     * @return Ngày thanh toán (định dạng YYYY-MM-DD).
     */
    const std::string& getPaymentDate() const;

    /**
     * @brief Lấy số tiền thanh toán.
     *
     * @return Số tiền thanh toán.
     */
    double getAmount() const;

    /**
     * @brief Lấy số tiền ứng trước.
     *
     * @return Số tiền ứng trước.
     */
    double getAdvance() const;

    /**
     * @brief Lấy ghi chú.
     *
     * @return Ghi chú.
     */
    const std::string& getNotes() const;

    /**
     * @brief Cập nhật số tiền thanh toán.
     *
     * @param amount Số tiền thanh toán mới.
     */
    void setAmount(double amount);

    /**
     * @brief Cập nhật số tiền ứng trước.
     *
     * @param advance Số tiền ứng trước mới.
     */
    void setAdvance(double advance);

    /**
     * @brief Cập nhật ghi chú.
     *
     * @param notes Ghi chú mới.
     */
    void setNotes(const std::string& notes);

    /**
     * @brief Chuyển đổi đối tượng SalaryPayment thành chuỗi CSV.
     *
     * @return Chuỗi CSV chứa thông tin thanh toán lương.
     */
    std::string toCSV() const;

    /**
     * @brief Tạo đối tượng SalaryPayment từ một chuỗi CSV.
     *
     * @param csvLine Chuỗi CSV chứa thông tin thanh toán lương.
     * @return Đối tượng SalaryPayment được tạo từ chuỗi CSV.
     */
    static SalaryPayment fromCSV(const std::string& csvLine);
};

std::vector<SalaryPayment> loadSalaryPaymentsFromFile(const std::string& filename);

void saveSalaryPaymentsToFile(const std::string& filename, const std::vector<SalaryPayment>& payments);

#endif