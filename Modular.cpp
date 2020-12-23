#include "Modular.h"

int modular::mod(const int64_t& num, const int64_t& module) {
	auto res = std::fmod(num, module);
	if (res < 0) res += module;
	return res;
}

int modular::found_reverse(const int& num, const int& module) {
	if (num == 0) return 0;
	int matr[2][2] = { { module, 0}, { num, 1} };
	int q, remaind, a;
	do {
		q = matr[0][0] / matr[1][0]; // Частное
		remaind = matr[0][0] % matr[1][0]; // Остаток
		a = matr[0][1] - (matr[1][1] * q); // a(i) = a(i-2) - ((a-1)*q(i))
		// Перестановка
		matr[0][0] = matr[1][0];
		matr[1][0] = remaind;
		matr[0][1] = matr[1][1];
		matr[1][1] = a;
	} while (matr[1][0] != 0);
	return modular::mod(matr[0][1], module);
}
