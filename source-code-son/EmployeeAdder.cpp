#include "EmployeeAdder.h"

void EmployeeAdder::add(EmployeeManager& manager, std::unique_ptr<IEmployee> emp)
{
    manager.getEmployees().push_back(std::move(emp));
}
