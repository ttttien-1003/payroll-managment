#ifndef _EMPLOYEE_EDITOR_H_
#define _EMPLOYEE_EDITOR_H_

#include "IEmployee.h"
#include "employeeManager.h"
#include <vector>
#include <memory>

/**
 * @brief Lớp phụ trách chỉnh sửa thông tin nhân viên trong danh sách.
 */
class EmployeeEditor {
private:
	std::vector<std::unique_ptr<IEmployee>>& employees; // Tham chiếu đến danh sách nhân viên hiện tại
public:
    /**
     * @brief Constructor nhận danh sách nhân viên hiện tại.
     * @param employeesList Tham chiếu đến vector chứa nhân viên.
     */
    EmployeeEditor(EmployeeManager& employeesList);

    /**
     * @brief Cập nhật tên của nhân viên theo ID.
     * @param id Mã nhân viên.
     * @param newName Tên mới.
     * @return true nếu cập nhật thành công, false nếu không tìm thấy.
     */
    bool editNameById(const std::string& id, const std::string& newName);

    /**
     * @brief Cập nhật số điện thoại của nhân viên theo ID.
     * @param id Mã nhân viên.
     * @param newPhone Số điện thoại mới.
     * @return true nếu cập nhật thành công.
     */
    bool editPhoneById(const std::string& id, const std::string& newPhone);

	/**
	 * @brief Cập nhật email của nhân viên theo ID.
	 * @param id Mã nhân viên.
	 * @param newEmail Email mới.
	 * @return true nếu cập nhật thành công.
	 */
	bool editEmailById(const std::string& id, const std::string& newEmail);

    /**
     * @brief Cập nhật toàn bộ thông tin nhân viên theo ID.
     * @param id Mã nhân viên.
     * @param newName Tên mới.
     * @param newPhone Số điện thoại mới.
     * @param newEmail Email mới.
     * @return true nếu cập nhật thành công.
     */
    bool editAllById(const std::string& id, const std::string& newName, const std::string& newPhone, const std::string& newEmail);
};

#endif
