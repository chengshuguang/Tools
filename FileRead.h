// -----------------------------------------------------------------------------
//  功能强大而简单的读写文件的FileRead函数
//  Wu Xuping 2012-03-10
//  测试环境:
//  C++ builder 2010
//  MinGW 4.5.1 windows
//  使用很简单,看看最后附上的测试代码即可
//  FileRead.hpp一定要保存为UTF-8的格式,因为这是MinGW的默认格式
// -----------------------------------------------------------------------------
#ifndef FileRead_H
#define FileRead_H
// --------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

 // =============================================================================
 // FileRead::将文件读入字符串数组中
 // =============================================================================
void FileRead(string FileName, vector<string>&FileStringVector) {
	// 这个函数是基于流的方式,速度也比较快
	if (FileStringVector.size() > 0) {
		FileStringVector.clear();
	}
	ifstream fin(FileName.c_str());
	if (!fin.bad()) {
		string sLine; // 行字符串
		while (getline(fin, sLine)) {
			FileStringVector.push_back(sLine);
		}
	}
	fin.close();
};

// =============================================================================
// FileRead::将文件一次性读入读入字符串中
// =============================================================================
void FileRead(string FileName, string &FileString) {
	FileString = "";
	char * buffer;
	// 使用文件流
	ifstream ifs;
	ifs.open(FileName.c_str(), ios::binary);
	// 测试文件中字符数目
	ifs.seekg(0, ios::end);
	long length = ifs.tellg();
	ifs.seekg(0, ios::beg);
	// 分配内存
	buffer = new char[length];
	// 读文件
	ifs.read(buffer, length);
	// 复制给FileString
	FileString = buffer;
	ifs.close();
	// 一定要释放内存
	delete[]buffer;

};
// ------------------------------------------------------------------------------
#endif
