#pragma once
#include <string>
#include <iostream>
#include "FractionFareyMSS.h"

class Fraction {
public:
	Fraction();
	Fraction(const std::string&, const std::vector<int64_t>&);
	Fraction(const int&, const int&, const std::vector<int64_t>&);

	Fraction operator+(Fraction&) const;
	Fraction operator-(Fraction&) const;
	Fraction operator*(Fraction&) const;

	std::string to_string() const; // Получить дробь
	void print() const; // Печать дроби

private:
	int _numerator; // Числитель дроби
	int _denominator; // Знаменатель дроби
	std::vector<int64_t> _modules;
	std::pair<int, int> _transform(int) const;
};

