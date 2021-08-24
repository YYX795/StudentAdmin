#ifndef ADMIN_H
#define ADMIN_H
#include<io.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<windows.h>
#include<conio.h>
#include"Student.h"

namespace ADMIN {
	//程序变量部分
	char txtname[1000];

	std::stringstream z;
	std::ifstream f;
	std::ofstream o;

	const char* txtnameSexing(const char* stunum/*引入学号*/) {
		for (int i = 0; i < 1000; i++) {
			txtname[i] = NULL;
		}

		if (_access("numbers", 0) == -1) { system("md numbers"); }

		strcpy(txtname, "numbers\\");						//文件名=“numbers\\”
		strcat(txtname, stunum);						//文件名=“numbers\\”+学号
		strcat(txtname, ".ZYL");							//文件名=“numbers\\”+学号+“.txt”
		return txtname;
	}


	//新建学生信息   创建成功则返回1，创建失败则返回0
	int NewInputMessage(st::Student Stu, int panding = 0/*判定是否强制覆盖*/) {
		txtnameSexing(Stu.number.c_str());
		//判断学生是否存在，若不在，则创建
		if (panding != 0) { goto lab; }
		f.open(txtname);
		if (!f.fail()) {
			MessageBox(NULL, TEXT("学生已存在!"), NULL, NULL);
			return 0;
		}
		f.close();

	lab:
		o.open(txtname);
		if (o.fail()) { return 0; }
		o << Stu.name << std::endl;
		o << Stu.test.Chinese << std::endl;
		o << Stu.test.Math << std::endl;
		o << Stu.test.English << std::endl;
		o.close();
		return 1;
	}

	st::Student GetScore(std::string snum/*学号*/) {								//读取成绩
		txtnameSexing(snum.c_str());
		st::Test test;
		std::string str;								//传参数
		int end = 0;										//判断是否正常结束
		f.open(txtname);
		if (f.fail()) {
			MessageBox(NULL, TEXT("该学生不存在"), NULL, NULL);
			st::Student err(0);
			return err;
		}
		else {
			char getchar[100];							//临时数组，用于数据类型转换
			int c = 0;									//getchar的下标
			int which = 1;								//往哪一个变量送数据（1姓名 2学号 3语文成绩 4数学成绩 5英语成绩）
			do {
				f.get(getchar[c]);

				if (getchar[c] == '\n') {
					getchar[c] = '\0';					//把换行换成结束符

					switch (which) {
					case 1:
						str = getchar;
						break;
					case 2:
						z << getchar;
						z >> test.Chinese;
						z.clear();
						break;
					case 3:
						z << getchar;
						z >> test.Math;
						z.clear();
						break;
					case 4:
						z << getchar;
						z >> test.English;
						z.clear();
						end = 1;
						break;
					}
					which++;
					//清理数组数据
					c = 0;
					strcpy(getchar, "\0");
				}
				else { c++; }
			} while (!f.eof());
			f.close();
			if (end == 1) {	//如果正常结束，则返回Student类
				st::Student Stu(str, snum, test);
				return  Stu;
			}
		}
	}

	int DeleteMessage(std::string str/*学号*/) {			//删除文件
		char DeletedTxtName[1000];
		strcpy(DeletedTxtName, "del ");
		strcat(DeletedTxtName, txtnameSexing(str.c_str()));
		system(DeletedTxtName);
		f.open(txtname);
		if (f.fail()) { MessageBox(NULL, TEXT("该学生已成功删除"), TEXT("提示"), NULL); return 1; }
		else { MessageBox(NULL, TEXT("删除失败"), NULL, NULL); return 0; }
		f.close();
	}

	int ChangeMessage(st::Student Stu) {
		return NewInputMessage(Stu, 1);
	}
}
#endif