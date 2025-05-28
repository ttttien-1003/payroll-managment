#include "PayrollCalculator.h"
#include "Attendance.h"
#include "SalaryPayment.h"
#include "PaySlip.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>


// Định nghĩa (và khởi tạo) thành viên tĩnh 'holidays'
std::vector<std::string> PayrollCalculator::holidays;

/**
 * @brief Constructor khởi tạo PayrollCalculator với mức lương theo giờ.
 *
 * @param rate Mức lương theo giờ (VND).
 */
PayrollCalculator::PayrollCalculator(double rate) : hourlyRate(rate) {}

/**
 * @brief Thêm ngày lễ vào danh sách ngày lễ.
 *
 * @param holiday Ngày lễ có định dạng MM-DD.
 */
void PayrollCalculator::addHoliday(const std::string& holiday) {
    holidays.push_back("01/01");
    holidays.push_back("04/30");
    holidays.push_back("05/01");
    holidays.push_back("09/02");
	holidays.push_back("02/09");

}

/**
 * @brief Kiểm tra xem một ngày có phải là ngày lễ hay không.
 *
 * @param date Ngày cần kiểm tra (YYYY-MM-DD).
 * @return true nếu là ngày lễ, false nếu không.
 */
bool PayrollCalculator::isHoliday(const std::string& date) const {
	// Chuyển đổi định dạng từ YYYY-MM-DD sang MM-DD
	std::string monthDay = date.substr(5, 2) + "/" + date.substr(8, 2);
    for (const auto& h : holidays) {
        if (h == monthDay) return true;
    }
    return false;
}

/**
 * @brief Lấy mức lương theo giờ.
 *
 * @return Mức lương theo giờ (VND).
 */
double PayrollCalculator::getHourlyRate() const {
    return hourlyRate;
}

/**
 * @brief Tính toán lương cho từng nhân viên dựa trên dữ liệu chấm công.
 *
 * Với mỗi bản ghi chấm công, nếu ngày đó là ngày lễ thì số giờ làm việc được nhân ba.
 * Sau đó cộng dồn số giờ theo mã nhân viên và nhân với đơn giá để tạo ra danh sách tính lương.
 *
 * @param records Danh sách bản ghi chấm công.
 * @return Danh sách các phiếu tính lương (PaySlip).
 */
std::vector<PaySlip> PayrollCalculator::calculatePayroll(const std::vector<Attendance>& records) const {
    std::unordered_map<std::string, double> hoursWorked;

    for (const auto& record : records) {
        double hours = record.calculateWorkHours();
        if (isHoliday(record.getWorkDate())) {
            hours *= 3.0; // Hệ số ngày lễ
        }
        hoursWorked[record.getEmployeeId()] += hours;
    }

    std::vector<PaySlip> payments;
    for (const auto& entry : hoursWorked) {
        double totalSalary = entry.second * hourlyRate;
        payments.emplace_back(entry.first, entry.second, hourlyRate, totalSalary);
    }

    return payments;
}
