#include "EmployeePrinter.h"

void EmployeePrinter::printAllEmployees(const EmployeeManager& manager) {
	const auto& employees = manager.getEmployee();
	if (employees.empty()) {
		std::cout << "Không có nhân viên nào trong danh sách.\n";
		return;
	}
	std::cout << "Danh sách nhân viên:\n";
	for (const auto& emp : employees) {
		std::cout << "ID: " << emp->getEmployeeId() << '\n'
			<< "Tên: " << emp->getName() << "\n"
			<< "Địa chỉ: " << emp->getAddress() << "\n"
			<< "Số điện thoại: " << emp->getPhone() << "\n"
			<< "Email: " << emp->getEmail() << "\n"
			<< "Thông tin bổ sung: " << emp->getAdditionalInfo() << "\n";
		std::cout << "---------------------------------------------------------\n";
	}
}

void EmployeePrinter::printEmployeeDetails(const EmployeeManager& manager, const std::string& employeeId) {
	const auto& employees = manager.getEmployee();
	auto it = std::find_if(employees.begin(), employees.end(),
		[&employeeId](const std::unique_ptr<IEmployee>& emp) {
			return emp->getEmployeeId() == employeeId;
		});
	if (it != employees.end()) {
		const auto& emp = *it;
		std::cout << "Thông tin chi tiết nhân viên:\n"
			<< "ID: " << emp->getEmployeeId() << '\n'
			<< "Tên: " << emp->getName() << "\n"
			<< "Địa chỉ: " << emp->getAddress() << "\n"
			<< "Số điện thoại: " << emp->getPhone() << "\n"
			<< "Email: " << emp->getEmail() << "\n"
			<< "Thông tin bổ sung: " << emp->getAdditionalInfo() << "\n"
			<< "Ngày hết hạn hợp đồng: "
			<< emp->getExpiredDay() << '/'
			<< emp->getExpiredMonth() << '/'
			<< emp->getExpiredYear() << "\n";
	}
	else {
		std::cout << "Không tìm thấy nhân viên với ID: " << employeeId << '\n';
	}
}