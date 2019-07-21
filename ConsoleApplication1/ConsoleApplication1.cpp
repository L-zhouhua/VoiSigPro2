// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
void save(short *b1, double *b2, int n);
int main(int argc, char * argv[])
{
	double* buf = new double[20000];
	ifstream infile;
	infile.open("double.dat");
	string s;
	int i = 0;
	while (getline(infile, s))
	{
		buf[i] = stod(s);
		cout << buf[i] << endl;
		i++;
	}
	delete(buf);
	buf = NULL;
	return 0;
}
