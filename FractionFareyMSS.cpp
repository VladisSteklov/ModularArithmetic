#include "FractionFareyMSS.h"


FractionFareyMSS::FractionFareyMSS(const std::pair<int, int>& num, const std::vector<int64_t>& modules) {
	_modules = modules;
	_num = num.first;
	_t = num.second;

	_p = 1;
	for (auto& elem : _modules) {
		_p *= elem; // Определение произведение модулей
	}
	_direct_transmit(); // Прямое преобразование числа
}

FractionFareyMSS::FractionFareyMSS(const std::vector<int>& presentation, const std::vector<int64_t>& modules, const int& t,			const int64_t& p) {
	_presentation = presentation;
	_modules = modules;
	_t = t;
	_p = p;
	_invers_transmit();
}

FractionFareyMSS FractionFareyMSS::operator+(const FractionFareyMSS& that) const {
	std::vector<int> res = std::vector<int>(this->_presentation.size());
	// min t
	int min_t = _t > that._t ? that._t : _t;
	for (size_t i = 0; i < _presentation.size(); ++i) {
		res[i] = modular::mod(std::pow(10, _t - min_t) * _presentation[i] + std::pow(10, that._t - min_t) * that._presentation[i], _modules[i]);
	}
	//Form result
	FractionFareyMSS result = FractionFareyMSS(res, _modules, min_t, _p);
	return result;
}

FractionFareyMSS FractionFareyMSS::operator-(const FractionFareyMSS& that) const {
	std::vector<int> res = std::vector<int>(this->_presentation.size());
	// min t
	int min_t = _t > that._t ? that._t : _t;
	for (size_t i = 0; i < _presentation.size(); ++i) {
		res[i] = modular::mod(std::pow(10, _t - min_t) * _presentation[i] - std::pow(10, that._t - min_t) * that._presentation[i], _modules[i]);
	}
	//Form result
	FractionFareyMSS result = FractionFareyMSS(res, _modules, min_t, _p);
	return result;
}

FractionFareyMSS FractionFareyMSS::operator*(const FractionFareyMSS& that) const {
	std::vector<int> res = std::vector<int>(this->_presentation.size());
	// min t
	int min_t = _t > that._t ? that._t : _t;
	for (size_t i = 0; i < _presentation.size(); ++i) {
		res[i] = modular::mod(std::pow(10, _t - min_t) * _presentation[i] * std::pow(10, that._t - min_t) * that._presentation[i], _modules[i]);
	}
	//Form result
	FractionFareyMSS result = FractionFareyMSS(res, _modules, min_t, _p);
	return result;
}

void FractionFareyMSS::_direct_transmit() {
	// Прямое преобразование числа - взяти модулей
	for (auto& elem : _modules) {
		_presentation.push_back(modular::mod(_num, elem));
	}
}
void FractionFareyMSS::_invers_transmit() {
	// Обратное преобразование числа
	std::vector<int> vec = std::vector<int>(_presentation.size());
	std::vector<int> reverse = std::vector<int>(_presentation.size());
	// Умножение на 10^t
	for (size_t i = 0; i < vec.size(); ++i) {
		vec[i] = modular::mod(_presentation[i] * std::pow(10, _t), _modules[i]);
	}
	// Нахождение ортоганалных базисов и обратных элементов
	for (size_t i = 0; i < reverse.size(); ++i) {
		reverse[i] = modular::mod(_p / _modules[i], _modules[i]); // Определение базиса
		if (reverse[i] != 1) {
			reverse[i] = modular::found_reverse(reverse[i], _modules[i]); // Нахождение обратного элемента
		}
	}
	// Преобразование на основе китайской теоремы
	_num = 0;
	for (size_t i = 0; i < _presentation.size(); ++i) {
		_num += _presentation[i] * reverse[i] * _p / _modules[i];
	}
	_num = modular::mod(_num, _p); // Взятие модуля
	// Проверить пренадлежность числа отрицательному интервалу
	if (_num >= ((_p - 1) / 2.0 + 1) && _num <= _p - 1) {
		// Взять арифметическое дополнение
		_num = _p - _num;
		_num *= -1;
	}
}

int FractionFareyMSS::get_num() const {
	return _num;
}

std::string FractionFareyMSS::to_string() const {
	return std::string(std::to_string(_num));
}

void FractionFareyMSS::print() const {
	std::cout << to_string() << std::endl;
}