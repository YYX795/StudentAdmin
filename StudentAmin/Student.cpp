#include<iostream>
#include"Student.h"
namespace st {
	void Student::PrintAll() {
		std::cout << "姓名:" << this->name << std::endl;
		std::cout << "学号:" << this->number << std::endl;
		std::cout << "语文成绩:" << this->test.Chinese << std::endl;
		std::cout << "数学成绩:" << this->test.Math << std::endl;
		std::cout << "英语成绩:" << this->test.English << std::endl;
	}

	Student::Student(std::string name, std::string number, Test test) {
		this->name = name;
		this->number = number;
		this->test = test;
	}

	Student::Student(int Sign) {
		this->Sign = Sign;
	}

	int Student::GetSign() {
		return this->Sign;
	}
}