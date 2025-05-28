#ifndef _EMPLOYEE_REMOVER_H_
#define _EMPLOYEE_REMOVER_H_

#include "EmployeeManager.h"
#include <string>

/**
 * @brief Lớp thực hiện chức năng xóa nhân viên khỏi EmployeeManager theo ID.
 */
class EmployeeRemover
{
public:
    /**
     * @brief Xóa nhân viên theo ID.
     * @param manager Tham chiếu tới EmployeeManager.
     * @param employeeId ID của nhân viên cần xóa.
     * @return true nếu xóa thành công, false nếu không tìm thấy.
     */
    bool remove(EmployeeManager& manager, const std::string& employeeId);
};

#endif
