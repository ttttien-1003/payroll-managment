#include "EmployeeRemover.h"
#include <algorithm>

bool EmployeeRemover::remove(EmployeeManager& manager, const std::string& employeeId)
{
    auto& employees = manager.getEmployees();
    auto it = std::find_if(employees.begin(), employees.end(),
        [&employeeId](const std::unique_ptr<IEmployee>& emp) {
            return emp->getEmployeeId() == employeeId;
        });
    if (it != employees.end())
    {
        employees.erase(it);
        return true;
    }
    return false;
}
