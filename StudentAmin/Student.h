#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
namespace st {
	typedef struct Test {
		double Chinese;
		double Math;
		double English;
	}Test;

	class Student {
	public:
		void PrintAll();
		Student(std::string name, std::string number, Test test);
		Student(int sign);
		int GetSign();
		std::string name;
		std::string number;
		Test test;
	private:
		int Sign = 1;
	};
}
#endif // !STUDENT_H
