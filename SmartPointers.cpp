// SmartPointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>

class baseClass {
public:
	baseClass() : m_a(0)
	{
		std::cout << "Called the baseClass constructor." << std::endl;
	};

	~baseClass()
	{
		std::cout << "Called the baseClass destructor." << std::endl;
	};

	int m_a;
};

int main()
{
	auto baseClassDeleter1 = [](baseClass* pBaseClass)->void
	{
		std::cout << "Called the baseClassDeleter1." << std::endl;

		if (pBaseClass)
			delete pBaseClass;
	};

	auto baseClassDeleter2 = [](baseClass* pBaseClass)->void
	{
		std::cout << "Called the baseClassDeleter2." << std::endl;

		if (pBaseClass)
			delete pBaseClass;
	};

	using upBASE_CLASS = std::unique_ptr<baseClass, void(*)(baseClass* pBaseClass)>;
	//using upBASE_CLASS = std::unique_ptr<baseClass, decltype(baseClassDeleter1)>;
	upBASE_CLASS upBaseClass1(new baseClass, baseClassDeleter1);
	upBASE_CLASS upBaseClass2{ nullptr, baseClassDeleter1 };

	upBaseClass1->m_a = 1;

	if (upBaseClass1 && !upBaseClass2) {
		upBaseClass2 = std::move(upBaseClass1);
	}

	if (!upBaseClass1) {
		std::cout << "upBaseClass1 is empty" << std::endl;
	}

	using spBASE_CLASS = std::shared_ptr<baseClass>;
	//spBASE_CLASS spBaseClass1{ new baseClass, baseClassDeleter1 };
	//spBASE_CLASS spBaseClass2{ new baseClass, baseClassDeleter2 };
	//spBaseClass1 = spBaseClass2;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
