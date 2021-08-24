#include<iostream>
#include"Student.h"
namespace st {
	void Student::PrintAll() {
		std::cout << "����:" << this->name << std::endl;
		std::cout << "ѧ��:" << this->number << std::endl;
		std::cout << "���ĳɼ�:" << this->test.Chinese << std::endl;
		std::cout << "��ѧ�ɼ�:" << this->test.Math << std::endl;
		std::cout << "Ӣ��ɼ�:" << this->test.English << std::endl;
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