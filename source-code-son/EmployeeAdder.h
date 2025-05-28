#ifndef _EMPLOYEE_ADDER_H_
#define _EMPLOYEE_ADDER_H_

#include "EmployeeManager.h"

/**
 * @brief Lớp thực hiện chức năng thêm nhân viên vào EmployeeManager.
 */
class EmployeeAdder
{
public:

	/**
	 * @brief Khởi tạo đối tượng EmployeeAdder.
	 */
	EmployeeAdder() = default;
    /**
     * @brief Thêm nhân viên vào danh sách.
     * @param manager Tham chiếu tới EmployeeManager.
     * @param emp unique_ptr tới đối tượng nhân viên cần thêm.
     */
    void add(EmployeeManager& manager, std::unique_ptr<IEmployee> emp);
};

#endif
