#include "EmployeeFinder.h"
#include <algorithm>

IEmployee* EmployeeFinder::findById(const EmployeeManager& manager, const std::string& employeeId) const
{
	const auto& employees = manager.getEmployee();
    auto it = std::find_if(employees.begin(), employees.end(),
        [&employeeId](const std::unique_ptr<IEmployee>& emp) {
            return emp->getEmployeeId() == employeeId;
        });
    if (it != employees.end())
        return it->get();
    return nullptr;
}

std::vector<IEmployee*> EmployeeFinder::findByName(const EmployeeManager& manager, const std::string& name) const
{
    std::vector<IEmployee*> result;
    const auto& employees = manager.getEmployee();
    for (const auto& emp : employees)
    {
        if (emp->getName().find(name) != std::string::npos)
            result.push_back(emp.get());
    }
    return result;
}
