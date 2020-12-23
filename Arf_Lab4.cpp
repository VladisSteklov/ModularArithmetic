#include <vector>
#include "FractionFareyMSS.h"
#include "FractionFarey.h"
#include "Fraction.h"
// Метод Гаусса для решение системы уравнений из 2-ух неизвестных
std::pair <FractionFarey, FractionFarey> gauss_method(std::vector<std::vector<FractionFarey>>&);
Fraction scalar_product(const int&, const std::pair<int, int>&);
bool is_prime(const int&);

int main() {
	setlocale(LC_ALL, "Russian");

	std::vector<int64_t> modules1 = { 3, 5, 7 };
	std::vector<int64_t> modules2 = { 7, 11, 19 };
	std::vector<int64_t> modules3 = { 3, 5, 7, 11, 19 };
	FractionFareyMSS ffm1 = FractionFareyMSS(std::pair<int, int>(23, 2), { 15319 });
	FractionFareyMSS ffm2 = FractionFareyMSS(std::pair<int, int>(3, 0), { 15319 });
	(ffm1 + ffm2).print();
	(ffm1 - ffm2).print();
	(ffm1 * ffm2).print();

	//auto res = scalar_product(4, std::pair<int, int>(-5, 5));
}

std::pair<FractionFarey, FractionFarey> gauss_method(std::vector<std::vector<FractionFarey>>& matrix) {
	// Матрица размера 2*3
	// Приведение матрицы к виду единичной матрицы - прямой ход
	auto koef = matrix[1][0] / matrix[0][0];
	for (size_t i = 0; i < 3; ++i) {
		auto r = matrix[0][i] * koef;
		matrix[1][i] = matrix[1][i] - r;
	}
	// Обратный ход
	koef = matrix[0][1] / matrix[1][1];
	for (size_t i = 0; i < 3; ++i) {
		auto r = matrix[1][i] * koef;
		matrix[0][i] = matrix[0][i] - r;
	}
	return std::pair<FractionFarey, FractionFarey>(matrix[0][2] / matrix[0][0], matrix[1][2] / matrix[1][1]);
}

// Скалярное произведение векторов
Fraction scalar_product(const int& n, const std::pair<int,int>& range) {
	// Формирование диапозона
	std::vector<int> rng = std::vector<int>(range.second - range.first + 1);
	int f = range.first;
	for (size_t i = 0; i < rng.size(); ++i) {
		rng[i] = f;
		++f;
	}
	// Опредение максимального возможного числителя и знаменателя и выбор модуля
	// Максимальный возможный числитель n*(Nmax^(2n)), знаменатель - Nmax^(2n)
	int n_max = std::abs(range.first) > std::abs(range.second) ? range.first : range.second;
	long int order = n * std::pow(n_max, 2 * n); // Максимальный порядок
	long int last_module = ( 2 * order  + 1)/(31 * 103) + 1;
	// Найти простое число большее last_module
	while (!is_prime(last_module)) {
		++last_module;
	}
	std::vector<int64_t> module = { 31, 223, last_module };

	// Инициализация исходных векторов
	srand(time(0));
	std::vector<Fraction> first, second;
	for (size_t i = 0, j = 0; i < n; ++i, ++j) {
		if (j == rng.size()) j = 0;
		Fraction ff1 = Fraction(range.first + rand() % (range.second - range.first + 1), rng[j], module);
		Fraction ff2 = Fraction(range.first + rand() % (range.second - range.first + 1), rng[j], module);
		first.push_back(ff1);
		second.push_back(ff2);
	}

	// Cкалярное произведение
	Fraction result = Fraction(0, 1, module);
	for (size_t i = 0; i < n; ++i) {
		auto mul = first[i] * second[i];
		result = result + mul;
	}
	return result;
}


bool is_prime(const int& n) {
	// ввести n c клавиатуры
	if (n == 4) return false;
	for (size_t i = 2; i < std::sqrt(n); ++i) {
		if (n % i == 0) {
			// вывести, что n  не простое, так как делится на i
			return false;
		}
	}
	// вывесьт что n простое.
	return true;
}