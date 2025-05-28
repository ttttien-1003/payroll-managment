#pragma once
#ifndef PAYSLIP_H
#define PAYSLIP_H

#include <string>
#include <vector>
#include <unordered_map>
/**
* @struct PaySlip
* @brief Cấu trúc lưu trữ thông tin tính lương.
*
* Cấu trúc này chứa thông tin về mã nhân viên, giờ làm việc,
* lương theo giờ và tổng lương.
*/

class PaySlip {
public:
	std::string employeeId; ///< Mã nhân viên.
	int hoursWorked; ///< Số giờ làm việc.
	double hourlyRate; ///< Lương theo giờ.
	double totalSalary; ///< Tổng lương.

	/**
	 * @brief Hàm khởi tạo mặc định cho PaySlip.
	 */
	PaySlip() : employeeId(""), hoursWorked(0), hourlyRate(0.0), totalSalary(0.0) {}

	/**
	 * @brief Hàm khởi tạo với các tham số cụ thể.
	 * @param id Mã nhân viên.
	 * @param hours Số giờ làm việc.
	 * @param rate Lương theo giờ.
	 */
	PaySlip(const std::string& id, int hours, double rate)
		: employeeId(id), hoursWorked(hours), hourlyRate(rate) {
		totalSalary = hoursWorked * hourlyRate;
	}

	/**
	 * @brief Hàm khởi tạo với các tham số cụ thể, bao gồm cả tổng lương.
	 * @param id Mã nhân viên.
	 * @param hours Số giờ làm việc.
	 * @param rate Lương theo giờ.
	 * @param total Tổng lương.
	 */
	PaySlip(const std::string& id, int hours, double rate, double total)
		: employeeId(id), hoursWorked(hours), hourlyRate(rate), totalSalary(total) {}
};


#endif // !PAYSLIP_H

