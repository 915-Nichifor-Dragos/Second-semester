#pragma once
#include <vector>
#include <iostream>
#include "Comparator.h"

using namespace std;

vector<string> tokenize(string str, char delimiter);

template <typename T>
void customSort(std::vector<T>& v, Comparator<T>* c);

template <typename T>
void customSort(std::vector<T>& v, Comparator<T>* c)
{
	for (int i = 0; i < v.size() - 1; i++)
		for (int j = i + 1; j < v.size(); j++)
			if (!c->compare(v[i], v[j]))
			{
				Event aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
}