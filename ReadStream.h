#pragma once
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class ReadStream
{
public:
	vector<int> read(int i);												// чтение интервала в исходном файле и запись его в целочисленный вектор из 2-х элементов 
	void OpenFile(string FileName);											// открытие файла для чтения (испрользуется в главном(main) потоке)
	void OpenFile(string FileName, int num);								// открытие файла для чтения (используется в дочернем потоке num)
	void OpeninFile(string FileName);										// открытие файла для записи (испрользуется в главном(main) потоке)
	void OpeninFile(string FileName, int num);								// открытие файла для записи (используется в дочернем потоке num)
	void BeginStruct(string FileName);										// открытие файла и запись в него начальных открывающих тегов
	void WriteStruct(vector<int> Interval, vector<int> result, int Num);	// запись в файл простых чисел заданного интервала
	void EndStruct();														// запись в файл конечных закрывающих тегов и закрытие файла
	int Number_intervals();													// вычисление количества интервалов заданных в исходном файле
	ReadStream();
	~ReadStream();
private:
	ifstream file;
	ofstream infile;
};

