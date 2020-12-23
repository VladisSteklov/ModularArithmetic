#include "FractionFarey.h"


// ctors
FractionFarey::FractionFarey(const std::string& fraction, const int& n) : FractionFarey(fraction, 0, n) {};

FractionFarey::FractionFarey(const std::string& fraction, const int& module, const int& n) : _module(module), _n(n) {
    std::string s1;
    std::string s2;
    auto pos = fraction.find('/');
    if (pos != std::string::npos) {
        s1 = fraction.substr(0, pos); // Строка числителя
        s2 = fraction.substr(pos + 1); // Строка знаменателя
    } else {
        // Только дробная часть
        s1 = fraction;
        s2 = "1";
    }
    // Преобразования в целое число
    _numerator = std::stoi(s1);
    _denominator = std::stoi(s2);
    auto min_module = 2 * _n * _n + 1;
    if (module < min_module) {
        // Задать модуль по умолчанию по формуле, если он равен нулю
        _module = min_module;
    }
    dir_transmit(); // Получение целого числа - представления дроби по модулю
}
// private ctor
FractionFarey::FractionFarey(const int& representation, const int& module, const int& n) : _representation(representation), _module(module), _n(n) {};

void FractionFarey::dir_transmit() {
    if (_denominator == 1) { // Нет знаменателя
        _representation = modular::mod(_numerator, _module);
        return;
    }
    auto reverse = extended_EucReverse(); // Найти обратное число к знаменателю
    _representation = modular::mod(reverse * (modular::mod(_numerator, _module)), _module);
}

void FractionFarey::inv_transmit() {
    auto fraction = extended_EucFarey();
    _numerator = fraction.first;
    _denominator = fraction.second;
    if (_denominator < 0 && _numerator > 0) {
        // Изменить знаки для лучшего отображения
        _denominator *= -1;
        _numerator *= -1;
    }
}

int FractionFarey::extended_EucReverse() const {
    int matr[2][2] = {{ _module, 0}, { _denominator, 1} };
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
    return modular::mod(matr[0][1], _module);
}
std::pair<int, int> FractionFarey::extended_EucFarey() const {
    if (_representation == 0) return std::pair<int, int>(0, 1); // Целое представление 0 соответствует дроби 0/1
    int matr[2][2] = { { _module, 0}, { _representation, 1} };
    int q, remaind, a;
    std::pair<int, int> result;
    do {
        q = matr[0][0] / matr[1][0]; // Частное
        remaind = matr[0][0] % matr[1][0]; // Остаток
        a = matr[0][1] - (matr[1][1] * q); // a(i) = a(i-2) - ((a-1)*q(i))
        // Перестановка
        matr[0][0] = matr[1][0];
        matr[1][0] = remaind;
        matr[0][1] = matr[1][1];
        matr[1][1] = a;
        if (matr[0][0] <= _n && matr[0][1] <= _n) return std::pair<int, int>(matr[0][0], matr[0][1]);
    } while (matr[1][0] != 0);
    return std::pair<int, int>(0, 0);
}

FractionFarey FractionFarey::operator+(FractionFarey& that) const {
    auto res = modular::mod(_representation + that._representation, _module);
    FractionFarey result = FractionFarey(res, _module, _n);
    result.inv_transmit();
    return result;
}
FractionFarey FractionFarey::operator-(FractionFarey& that) const {
    auto res = modular::mod(_representation - that._representation, _module);
    FractionFarey result = FractionFarey(res, _module, _n);
    result.inv_transmit();
    return result;
}
FractionFarey FractionFarey::operator*(FractionFarey& that) const {
    auto res = modular::mod(_representation * that._representation, _module);
    FractionFarey result = FractionFarey(res, _module, _n);
    result.inv_transmit();
    return result;
}
FractionFarey FractionFarey::operator/(FractionFarey& that) const {
    // Найти обратный элемент к that._representation
    // Деление сводится к умножению по модулю
    FractionFarey ff = that;
    ff._numerator = 1;
    ff._denominator = that._representation;
    auto reverse = ff.extended_EucReverse(); // Найти обратный элемент
    auto res = modular::mod(_representation * reverse, _module);
    FractionFarey result = FractionFarey(res, _module, _n);
    result.inv_transmit();
    return result;
}

std::string FractionFarey::to_string() const {
    auto result = std::to_string(_numerator) + '/' + std::to_string(_denominator);
    result += "\tМодулярное представление числа в модуле " +std::to_string(_module) + ": " + std::to_string(_representation);
    return result;
}

void FractionFarey::print() const {
    std::cout << to_string() << std::endl;
}