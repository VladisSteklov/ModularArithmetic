#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "Modular.h"


class FractionFareyMSS {
public:
	//ctors
	FractionFareyMSS(const std::pair<int, int>&, const std::vector<int64_t>&);

	// Math Operations
	FractionFareyMSS operator+(const FractionFareyMSS&) const;
	FractionFareyMSS operator-(const FractionFareyMSS&) const;
	FractionFareyMSS operator*(const FractionFareyMSS&) const;

	int get_num() const;
	// Prints
	std::string to_string() const;
	void print() const;

private:
	FractionFareyMSS(const std::vector<int>&, const std::vector<int64_t>&, const int&, const int64_t&);

	void _direct_transmit(); // Прямое преобразование числа
	void _invers_transmit(); // Обратное преобразование числа

	std::vector<int64_t> _modules; // Модули
	std::vector<int> _presentation; // Модулярное представление числа
	int64_t _num; // Само десятичное число
	int64_t _p; // Произведение модулей
	int _t; // Порядок числа
};

