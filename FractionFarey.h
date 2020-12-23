#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include "Modular.h"

class FractionFarey {
public:
	FractionFarey(const std::string&, const int&);
	FractionFarey(const std::string& fraction, const int& module, const int& n);

	FractionFarey operator+(FractionFarey&) const;
	FractionFarey operator-(FractionFarey&) const;
	FractionFarey operator/(FractionFarey&) const;
	FractionFarey operator*(FractionFarey&) const;
	
	std::string to_string() const; // Получить дробь
	void print() const; // Печать дроби
 
private:
	FractionFarey(const int&, const int&, const int&);
	int _module; // Модуль
	int _n; // Порядок дроби Фарея
	int _numerator; // Числитель дроби
	int _denominator; // Знаменатель дроби
	int _representation; // Целое представление числа

	// Прямое преобразование числа
	void dir_transmit();
	// Обратное преобразование числа
	void inv_transmit();
	// Расширенный алгоритм Евклида нахождения обратного числа по модулю module
	int extended_EucReverse() const;
	// Расширенный алгоритм Евклида - обратное преобразование
	std::pair<int, int> extended_EucFarey() const;
};

