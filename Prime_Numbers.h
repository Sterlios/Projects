#pragma once
#include <vector>

using namespace std;

class Prime_Numbers
{
public:
	int GetMin();							// возвращение минимума
	int GetMax();							// возвращение максимума
	void SetInterval(vector<int> interval);	// задать объекту интервал для вычисления простых чисел
	void CalcNumb();						// вычисление простых чисел в заданном интервале
	vector<int> GetResult();				// возвращение результата

	Prime_Numbers();
	~Prime_Numbers();
private:
	vector<int> Pr_Numbers;
	vector<int> result;
	int min, max;
};

