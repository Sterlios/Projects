#include "Prime_Numbers.h"



int Prime_Numbers::GetMin()
{
	return this->min;
}

int Prime_Numbers::GetMax()
{
	return this->max;
}

void Prime_Numbers::SetInterval(vector<int> interval)
{
	this->min = interval[0];
	this->max = interval[1];
	CalcNumb();
}

void Prime_Numbers::CalcNumb()
{
	Pr_Numbers.push_back(2);
	for (int i = 3; i < max; i++){
		for (int j = 0; j < (int)Pr_Numbers.size(); j++){
			if (i % Pr_Numbers[j] == 0) { break; }
			else 
				if (j == Pr_Numbers.size() - 1) { 
					Pr_Numbers.push_back(i);
					if (i > min) { result.push_back(i); }
			}
		}
	}
}

vector<int> Prime_Numbers::GetResult()
{
	return this->result;
}

Prime_Numbers::Prime_Numbers()
{
}

Prime_Numbers::~Prime_Numbers()
{
}
