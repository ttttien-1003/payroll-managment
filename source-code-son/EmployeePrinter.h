#pragma once
#ifndef EMPLOYEE_PRINTER_H
#define EMPLOYEE_PRINTER_H

#include "EmployeeManager.h"

class EmployeePrinter {
public:
	/**
	 * @brief In thông tin của tất cả nhân viên trong EmployeeManager.
	 * @param manager Tham chiếu tới EmployeeManager chứa danh sách nhân viên.
	 */
	static void printAllEmployees(const EmployeeManager& manager);

	/**
	 * @brief In thông tin chi tiết của một nhân viên theo ID.
	 * @param manager Tham chiếu tới EmployeeManager chứa danh sách nhân viên.
	 * @param employeeId ID của nhân viên cần in thông tin.
	 */
	static void printEmployeeDetails(const EmployeeManager& manager, const std::string& employeeId);
};

#endif