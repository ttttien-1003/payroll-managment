#ifndef _APP_H_
#define _APP_H_

#include "employeeManager.h"

class App
{
private:
	EmployeeManager empManager;
public:
	App();

	void run();
};


#endif