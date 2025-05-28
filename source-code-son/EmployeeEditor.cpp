#include "EmployeeEditor.h"

/**
* @brief Constructor nhận danh sách nhân viên hiện tại.
* @param employeesList Tham chiếu đến vector chứa nhân viên.
*/
EmployeeEditor::EmployeeEditor(EmployeeManager& employeesList)
	: employees(employeesList.getEmployees()) {
}

/**
* @brief Cập nhật số điện thoại nhân viên theo ID.
* @param id Mã nhân viên.
* @param newPhone Số điện thoại mới.
* @return true nếu cập nhật thành công, false nếu không tìm thấy nhân viên.
*/
bool EmployeeEditor::editPhoneById(const std::string& id, const std::string& newPhone) {
	for (const auto& emp : employees) {
		if (emp->getEmployeeId() == id) {
			emp->setPhone(newPhone);
			return true;
		}
	}
	return false; // Không tìm thấy nhân viên với ID này
}

/**
* @brief Cập nhật email của nhân viên theo ID.
* @param id Mã nhân viên.
* @param newEmail Email mới.
* @return true nếu cập nhật thành công, false nếu không tìm thấy nhân viên.
*/
bool EmployeeEditor::editEmailById(const std::string& id, const std::string& newEmail) {
	for (const auto& emp : employees) {
		if (emp->getEmployeeId() == id) {
			emp->setEmail(newEmail);
			return true;
		}
	}
	return false; // Không tìm thấy nhân viên với ID này
}

/**
* @brief Cập nhật toàn bộ thông tin nhân viên theo ID.
* @param id Mã nhân viên.
* @param newName Tên mới.
* @param newPhone Số điện thoại mới.
* @param newEmail Email mới.
* @return true nếu cập nhật thành công, false nếu không tìm thấy nhân viên.
*/
bool EmployeeEditor::editAllById(const std::string& id, const std::string& newName, const std::string& newPhone, const std::string& newEmail) {
	for (const auto& emp : employees) {
		if (emp->getEmployeeId() == id) {
			emp->setName(newName);
			emp->setPhone(newPhone);
			emp->setEmail(newEmail);
			return true;
		}
	}
	return false; // Không tìm thấy nhân viên với ID này
}

/**
* @brief Cập nhật tên của nhân viên theo ID.
* @param id Mã nhân viên.
* @param newName Tên mới.
* @return true nếu cập nhật thành công, false nếu không tìm thấy nhân viên.
*/
bool EmployeeEditor::editNameById(const std::string& id, const std::string& newName) {
	for (const auto& emp : employees) {
		if (emp->getEmployeeId() == id) {
			emp->setName(newName);
			return true;
		}
	}
	return false; // Không tìm thấy nhân viên với ID này
}