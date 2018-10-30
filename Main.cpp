#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "Prime_Numbers.h"
#include "ReadStream.h"

using namespace std;

mutex mtx;
ReadStream FileData; 
ReadStream FileResult;
string filenameData;
string filenameResult;
int queue_thread;

void thread_proc(int tnum) {
	vector<int> Result;
	Prime_Numbers P_Num;
	ReadStream FileD;
	vector<int> interval(2);
	FileD.OpenFile(filenameData, tnum);							// Открытие исходного файла 
	interval = FileD.read(tnum);								// Чтение интервалов из исходного файла
	P_Num.SetInterval(interval);								// отправка интервалов объекту для вычисления простых чисел
	Result = P_Num.GetResult();									// вычисление простых чисел
	while (1) {													// ожидание потока своей очереди
		if (queue_thread == tnum - 1) {
			FileResult.WriteStruct(interval, Result, tnum);		// запись результатов в новый файл
			queue_thread++;
			break;
		}
	}
	lock_guard<mutex> lock(mtx);
}

int main()
{
	setlocale(LC_ALL, "rus");
	int i = 1, Number_intervals = 0;
	vector<thread> threads;
	cout << "Введите название файла с интервалами - ";
	cin >> filenameData;
	cout << "Введите название файла для результатов - ";
	cin >> filenameResult;
	queue_thread = 0;
	FileData.OpenFile(filenameData);							// открытие исходного файла
	Number_intervals = FileData.Number_intervals();				// вычисление количества интервалов в исходном файле
	FileResult.BeginStruct(filenameResult);						// запись начальных тегов в результирующий файл
	while (i < Number_intervals + 1) {							// Создание потоков от 1 до количества интервалов в исходном файле включительно
		thread thr(thread_proc, i);
		threads.emplace_back(move(thr));
		i++;
	}
	for (auto& thr : threads) {									// ожидание завершения каждого потока
		thr.join();
	}
	FileResult.EndStruct();										// запись конечных тегов в результирующий файл
	cout << "Done!" << endl;
	return 1;
}
