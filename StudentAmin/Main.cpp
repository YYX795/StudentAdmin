#include<iostream>
#include"Admin.h"
#include"Student.h"
#include<io.h>
#include<Windows.h>
using namespace st;

class Frame {
public:
	int reslut = 0;
	int Menu(void);//主界面
	void Number(void);//统计学生数
	void Input(void);//添加
	void Delete(void);//删除
	void Modify(void);//修改
	void Search(void);//搜索
	void Run(int command);//执行命令
	void Exit(void);//退出
	Student InputMessage(void);//输入信息
	Student InputMessage(std::string num);//重载输入信息
	int findfile(std::string path, std::string mode);//统计文件数
};

int main(void) {
	SetConsoleTitle(L"学生管理系统");
	Frame form;
	while (true) {
		int command;
		command = form.Menu();
		form.Run(command);
		if (_access("numbers", 0) == -1) {
			system("md numbers");
		}
	}
}

void Frame::Run(int comand) {
	switch (comand) {
	case 0:
		;
		break;
	case 1:
		this->Exit();
		break;
	case 2:
		this->Input();
		break;
	case 3:
		this->Search();
		break;
	case 4:
		this->Delete();
		break;
	case 5:
		this->Modify();
		break;
	case 6:
		this->Number();
		break;
	case 7:
		this->Menu();
		break;
	default:
		std::cout << "ERROR!" << std::endl;
		break;
	}
}

int Frame::Menu(void) {
	std::cin.clear();
	system("cls");
	std::cout << "\n\n\n\n" << std::endl;
	std::cout << "\t\t\t|-------------------------STUDENTADMIN--------------------------|\n" << std::endl;
	std::cout << "\t\t\t|\t1 . exit						|\n" << std::endl;
	std::cout << "\t\t\t|\t2 . input						|\n" << std::endl;
	std::cout << "\t\t\t|\t3 . search						|\n" << std::endl;
	std::cout << "\t\t\t|\t4 . delete						|\n" << std::endl;
	std::cout << "\t\t\t|\t5 . modify						|\n" << std::endl;
	std::cout << "\t\t\t|\t6 . number						|\n" << std::endl;
	std::cout << "\t\t\t|---------------------------------------------------------------|\n" << std::endl;
	std::cout << "\t\t\tchoose 1-6:";
	std::cin >> this->reslut;
	if (std::cin.good()) {
		return reslut;
	}
	else {
		std::cout << "ERROR" << std::endl;
		return 1;
	}
}

void Frame::Exit(void) {
	exit(1);
}

void Frame::Input(void) {
	system("cls");
	std::cin.clear();
	std::cin.ignore(100, '\n');
	Student student = this->InputMessage();
	if (student.GetSign() == 0) {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	if(ADMIN::NewInputMessage(student)){
		student.PrintAll();
	}
	else {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	system("pause");
}

void Frame::Delete(void) {
	system("cls");
	std::cin.clear();
	std::cin.ignore(100, '\n');
	std::cout << "请输入你要删除的学号:";
	std::string num;
	std::cin >> num;
	if (!std::cin.good()) {
		return;
	}
	std::cout << '\n';
	std::cout << "删除结果!" << std::endl;
	Student st = ADMIN::GetScore(num);
	if (st.GetSign() == 1) {
		st.PrintAll();
	}else {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	if (ADMIN::DeleteMessage(num)) {
		std::cout << "成功" << std::endl;
	}else {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	system("pause");
}

void Frame::Modify(void) {
	system("cls");
	std::cin.clear();
	std::cin.ignore(100, '\n');
	std::cout << "请输入你要修改的学号:";
	std::string num;
	std::cin >> num;
	if (!std::cin.good()) {
		return;
	}
	std::cout << '\n';
	Student st = ADMIN::GetScore(num);
	if (st.GetSign() == 1) {
		Student student= this->InputMessage(num);
		if (student.GetSign()==0 ) {
			std::cout << "失败" << std::endl;
			system("pause");
			return;
		}
		if (ADMIN::ChangeMessage(student)) {
			std::cout << "成功" << std::endl;
		}
		else {
			std::cout << "失败" << std::endl;
			system("pause");
			return;
		}
		
	}
	else {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	system("pause");
}

void Frame::Search(void) {
	system("cls");
	std::cin.clear();
	std::cin.ignore(100, '\n');
	if (_access("numbers", 0) == -1) {
		system("md numbers");
	}
	std::cout << "请输入你要搜索的学号:";
	std::string num;
	std::cin >> num;
	if (!std::cin.good()) {
		return;
	}
	std::cout << '\n';
	std::cout << "搜素结果:" << std::endl;
	Student st = ADMIN::GetScore(num);
	if (st.GetSign()==1) {
		st.PrintAll();
	}
	else {
		std::cout << "失败" << std::endl;
		system("pause");
		return;
	}
	system("pause");
}

void Frame::Number(void) {
	system("cls");
	std::cin.clear();
	std::cin.ignore(100, '\n');
	std::cout << "学生数量:" << std::endl;
	std::cout << this->findfile("numbers","\\*.ZYL") << std::endl;
	system("pause");
}

Student Frame::InputMessage(void) {
	std::string name, number;
	double chinese, math, English;
	std::cout << "请输入姓名:";
	std::cin >> name;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入学号:";
	std::cin >> number;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入语文成绩:";
	std::cin >> chinese;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	if (!(0 <= chinese && chinese <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入数学成绩:";
	std::cin >> math;
	if (!std::cin.good()) {
		std::cin.clear();
	}
	if (!(0 <= math && math <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入英语成绩:";
	std::cin >> English;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	if (!(0 <= English && English <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	Test test;
	test.Chinese = chinese;
	test.English = English;
	test.Math = math;
	Student student = Student(name, number, test);
	return student;
}

Student Frame::InputMessage(std::string num) {
	std::string name;
	double chinese, math, English;
	std::cout << "请输入姓名:";
	std::cin >> name;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入语文成绩:";
	std::cin >> chinese;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	if (!(0 <= chinese && chinese <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入数学成绩:";
	std::cin >> math;
	if (!std::cin.good()) {
		std::cin.clear();
	}
	if (!(0 <= math && math <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	std::cout << "请输入英语成绩:";
	std::cin >> English;
	if (!std::cin.good()) {
		st::Student err(0);
		return err;
	}
	if (!(0 <= English && English <= 100)) {
		std::cout << "输入错误！请输入一个0-100的数" << std::endl;
		system("pause");
		st::Student err(0);
		return err;
	}
	std::cout << '\n';
	Test test;
	test.Chinese = chinese;
	test.English = English;
	test.Math = math;
	Student student = Student(name, num, test);
	return student;
}

int Frame::findfile(std::string path, std::string mode)
{
	int n = 0;
	_finddata_t file;
	intptr_t HANDLE;
	std::string Onepath = path + mode;
	HANDLE = _findfirst(Onepath.c_str(), &file);
	if (HANDLE == -1L)
	{
		std::cout << "失败或者无学生" << std::endl;
		return 0;
	}
	do {
		//判断是否有子目录  
		if (file.attrib & _A_SUBDIR)
		{
			//判断是否为"."当前目录，".."上一层目录
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0))
			{
				std::string newPath = path + "\\" + file.name;
				findfile(newPath, mode);
			}
		}
		else
		{
			n++;
		}
	} while (_findnext(HANDLE, &file) == 0);
	_findclose(HANDLE);
	return n;
}