#ifndef _EMPLOYEE_FINDER_H_
#define _EMPLOYEE_FINDER_H_

#include "EmployeeManager.h"
#include <string>
#include <vector>

/**
 * @brief Lớp thực hiện chức năng tìm kiếm nhân viên.
 */
class EmployeeFinder
{
public:
    /**
     * @brief Tìm nhân viên theo ID.
     * @param manager Tham chiếu tới EmployeeManager.
     * @param employeeId ID nhân viên cần tìm.
     * @return Con trỏ tới nhân viên nếu tìm thấy, nullptr nếu không.
     */
    IEmployee* findById(const EmployeeManager& manager, const std::string& employeeId) const;

    /**
     * @brief Tìm nhân viên theo tên (có thể trả về nhiều kết quả).
     * @param manager Tham chiếu tới EmployeeManager.
     * @param name Tên cần tìm (có thể là một phần của tên).
     * @return Vector con trỏ tới nhân viên thỏa điều kiện.
     */
    std::vector<IEmployee*> findByName(const EmployeeManager& manager, const std::string& name) const;
};

#endif
