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
	//�����������
	char txtname[1000];

	std::stringstream z;
	std::ifstream f;
	std::ofstream o;

	const char* txtnameSexing(const char* stunum/*����ѧ��*/) {
		for (int i = 0; i < 1000; i++) {
			txtname[i] = NULL;
		}

		if (_access("numbers", 0) == -1) { system("md numbers"); }

		strcpy(txtname, "numbers\\");						//�ļ���=��numbers\\��
		strcat(txtname, stunum);						//�ļ���=��numbers\\��+ѧ��
		strcat(txtname, ".ZYL");							//�ļ���=��numbers\\��+ѧ��+��.txt��
		return txtname;
	}


	//�½�ѧ����Ϣ   �����ɹ��򷵻�1������ʧ���򷵻�0
	int NewInputMessage(st::Student Stu, int panding = 0/*�ж��Ƿ�ǿ�Ƹ���*/) {
		txtnameSexing(Stu.number.c_str());
		//�ж�ѧ���Ƿ���ڣ������ڣ��򴴽�
		if (panding != 0) { goto lab; }
		f.open(txtname);
		if (!f.fail()) {
			MessageBox(NULL, TEXT("ѧ���Ѵ���!"), NULL, NULL);
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

	st::Student GetScore(std::string snum/*ѧ��*/) {								//��ȡ�ɼ�
		txtnameSexing(snum.c_str());
		st::Test test;
		std::string str;								//������
		int end = 0;										//�ж��Ƿ���������
		f.open(txtname);
		if (f.fail()) {
			MessageBox(NULL, TEXT("��ѧ��������"), NULL, NULL);
			st::Student err(0);
			return err;
		}
		else {
			char getchar[100];							//��ʱ���飬������������ת��
			int c = 0;									//getchar���±�
			int which = 1;								//����һ�����������ݣ�1���� 2ѧ�� 3���ĳɼ� 4��ѧ�ɼ� 5Ӣ��ɼ���
			do {
				f.get(getchar[c]);

				if (getchar[c] == '\n') {
					getchar[c] = '\0';					//�ѻ��л��ɽ�����

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
					//������������
					c = 0;
					strcpy(getchar, "\0");
				}
				else { c++; }
			} while (!f.eof());
			f.close();
			if (end == 1) {	//��������������򷵻�Student��
				st::Student Stu(str, snum, test);
				return  Stu;
			}
		}
	}

	int DeleteMessage(std::string str/*ѧ��*/) {			//ɾ���ļ�
		char DeletedTxtName[1000];
		strcpy(DeletedTxtName, "del ");
		strcat(DeletedTxtName, txtnameSexing(str.c_str()));
		system(DeletedTxtName);
		f.open(txtname);
		if (f.fail()) { MessageBox(NULL, TEXT("��ѧ���ѳɹ�ɾ��"), TEXT("��ʾ"), NULL); return 1; }
		else { MessageBox(NULL, TEXT("ɾ��ʧ��"), NULL, NULL); return 0; }
		f.close();
	}

	int ChangeMessage(st::Student Stu) {
		return NewInputMessage(Stu, 1);
	}
}
#endif