#include "ReadStream.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;
vector<int> ReadStream::read(int i)
{
	string word,
		Number1,
		Number2,
		flag = "low",
		text;
	int Num_interval = 1;
	vector<int> interval(2);
	file.seekg(0, ios_base::beg);
	while (word != "</intervals>") {										// </intervals> - закрывающий тег, указывает на конец перечисления интервалов
		file >> word;
		if (word == "<interval>") {											// <interval> - открывающий тег очередного интервала
			if (Num_interval == i)											// совпадает ли очередной интервал в последовательности с номером потока?
			{																// если не совпадает - ниже увеличиваем значение Num_interval и продолжаем поиск следующего интервала
				file >> word;												// разбирает файл по словам отделенных пробелом, переносом строки
				while (word != "</interval>") {								// </interval> - закрывающий тег очередного интервала
					text += word;											// в text записываются найденные слова между тегами <interval> и </interval>
					file >> word;											// в результате должна получиться строка вида "<low>100</low><high>200</high>"
				}
				for (int k = 1; k < (int)(text.size() - 1); k++) {			// посимвольный перебор строки
					if ((text[k - 1] == '>') && (text[k] != '<')) {
						while ((text[k] != '<') && (flag == "low")) {		// поиск первого числа low
							Number1 += text[k];
							k++;
						}
						interval[0] = stoi(Number1.c_str());				// преобразование string в int
						while ((text[k] != '<') && (flag == "high")) {		// поиск второго числа high
							Number2 += text[k];
							k++;
						}
						if (flag == "high")
							interval[1] = stoi(Number2.c_str());			// преобразование string в int
						flag = "high";
					}
				}
				Number1 = Number2 = "";
				flag = "low";
				text = "";
				Num_interval++;
			}
			else { Num_interval++; }
		}
		else {
			if (file.eof()) { cout << "открывающего тега <interval> не обнаружено" << endl; exit(30); }
		}
	}
	return interval;
}
void ReadStream::OpenFile(string FileName)
{
	file.open(FileName);
	if (!file) { cout << "Файл " << FileName << " не открыт" << endl; exit(1000); }
	}
void ReadStream::OpenFile(string FileName, int num)
{
	file.open(FileName);
	if (!file) { cout << "Поток - " << num << " Файл " << FileName << " не открыт" << endl; exit(num * (1000)); }
}
void ReadStream::OpeninFile(string FileName)
{
	infile.open(FileName);
	if (!infile) { cout << "Файл " << FileName << " не открыт" << endl; exit(-1000); }
}
void ReadStream::OpeninFile(string FileName, int num)
{
	infile.open(FileName);
	if (!infile) { cout << "Поток - " << num << " Файл " << FileName << " не открыт" << endl; exit(num * (-1000)); }
}
void ReadStream::BeginStruct(string FileName)
{
	OpeninFile(FileName);
	infile << "<root>" << endl;
	infile << "<results>" << endl;
}
void ReadStream::WriteStruct(vector<int> Interval, vector<int> result, int Num)
{
	infile.seekp(0, ios_base::end);
	infile << "<interval num=\"" << Num << "\">" << endl;
	infile << "<low>" << Interval[0] << "</low>" << endl;
	infile << "<high>" << Interval[1] << "</high>" << endl;
	for (int i = 0; i < result.size(); i++) {
		infile << "<No" << i << ">" << result[i] << "</No" << i << ">" << endl;
	}
	infile << "</interval>" << endl;
}
void ReadStream::EndStruct()
{
	infile.seekp(0, ios_base::end);
	infile << "</results>" << endl;
	infile << "</root>" << endl;
	infile.close();
}
int ReadStream::Number_intervals()
{
	int Num = 0;
	string words;
	while (words != "</intervals>") {
		file >> words;
		if (words == "<interval>") { Num++; }
	}
	return Num;
}

ReadStream::ReadStream()
{
}

ReadStream::~ReadStream()
{
		file.close();
		infile.close();
}
