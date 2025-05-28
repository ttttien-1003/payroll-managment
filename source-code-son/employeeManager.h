#ifndef _EMPLOYEE_MANAGER_H_
#define _EMPLOYEE_MANAGER_H_

#include <vector>
#include <memory>
#include <string>
#include "IEmployee.h"

/**
 * @brief Lớp quản lý danh sách nhân viên.
 *
 * Lưu trữ danh sách nhân viên, cung cấp các phương thức truy cập dữ liệu.
 */
class EmployeeManager
{
private:
    std::vector<std::unique_ptr<IEmployee>> employees;

public:
    /**
     * @brief Lấy danh sách con trỏ đến nhân viên.
     * @return Tham chiếu đến vector chứa unique_ptr nhân viên.
     */
    std::vector<std::unique_ptr<IEmployee>>& getEmployees();

    /**
     * @brief Lấy danh sách nhân viên (chỉ đọc).
     */
    const std::vector<std::unique_ptr<IEmployee>>& getEmployee() const;
};


#endif
