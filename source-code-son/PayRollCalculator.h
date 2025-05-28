#ifndef PAYROLL_CALCULATOR_H
#define PAYROLL_CALCULATOR_H

#include <vector>
#include <string>
#include "Attendance.h"
#include "SalaryPayment.h"
#include "PaySlip.h"


/**
 * @class PayrollCalculator
 * @brief Lớp tính toán lương dựa trên thông tin chấm công.
 *
 * Lớp này xử lý danh sách chấm công để tính toán các khoản lương
 * tương ứng cho từng nhân viên, có kiểm tra ngày lễ.
 */
class PayrollCalculator {
private:
    double hourlyRate; ///< Mức lương theo giờ (VND)
    static std::vector<std::string> holidays; ///< Danh sách ngày lễ (các ngày lễ của 1 năm) (MM-DD)

    /**
     * @brief Kiểm tra một ngày có phải ngày lễ không.
     *
     * @param date Ngày làm việc (YYYY-MM-DD).
     * @return true nếu là ngày lễ, false nếu không.
     */
    bool isHoliday(const std::string& date) const;

public:
    /**
     * @brief Constructor với mức lương theo giờ.
     *
     * @param rate Mức lương theo giờ (VND).
     */
    PayrollCalculator(double rate);

    /**
	* @brief Lấy mức lương theo giờ.
    * 
	* @return Mức lương theo giờ (VND).
	*/
    double getHourlyRate() const;

    /**
     * @brief Thêm ngày lễ vào danh sách.
     *
     * @param holiday Ngày lễ theo định dạng YYYY-MM-DD.
     */
    void addHoliday(const std::string& holiday);

    /**
     * @brief Tính lương cho mỗi nhân viên dựa vào dữ liệu chấm công.
     *
     * @param records Danh sách dữ liệu chấm công.
     * @return Danh sách thanh toán lương.
     */
    std::vector<PaySlip> calculatePayroll(const std::vector<Attendance>& records) const;

};

#endif
