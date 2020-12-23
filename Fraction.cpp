#include "Fraction.h"

Fraction::Fraction() {}

Fraction::Fraction(const std::string& str, const std::vector<int64_t>& modules) {
    std::string s1;
    std::string s2;
    auto pos = str.find('/');
    if (pos != std::string::npos) {
        s1 = str.substr(0, pos); // Строка числителя
        s2 = str.substr(pos + 1); // Строка знаменателя
    }
    else {
        // Только дробная часть
        s1 = str;
        s2 = "1";
    }
    // Преобразования в целое число
    _numerator = std::stoi(s1);
    _denominator = std::stoi(s2);
    _modules = modules;
}

Fraction::Fraction(const int& num, const int& dem, const std::vector<int64_t>& modules) {
    _numerator = num;
    _denominator = dem;
    _modules = modules;
}
Fraction Fraction::operator+(Fraction& that) const {
    const FractionFareyMSS num1 = FractionFareyMSS(_transform(_numerator), _modules);
    const FractionFareyMSS num2 = FractionFareyMSS(_transform(that._numerator), _modules);
    const FractionFareyMSS det1 = FractionFareyMSS(_transform(_denominator), _modules);
    const FractionFareyMSS det2 = FractionFareyMSS(_transform(that._denominator), _modules);
    return Fraction((num1 * det2 + num2 * det1).get_num(), (det1 * det2).get_num(), _modules);
}

Fraction Fraction::operator-(Fraction& that) const {
    const FractionFareyMSS num1 = FractionFareyMSS(_transform(_numerator), _modules);
    const FractionFareyMSS num2 = FractionFareyMSS(_transform(that._numerator), _modules);
    const FractionFareyMSS det1 = FractionFareyMSS(_transform(_denominator), _modules);
    const FractionFareyMSS det2 = FractionFareyMSS(_transform(that._denominator), _modules);
    return Fraction((num1 * det2 - num2 * det1).get_num(), (det1 * det2).get_num(), _modules);
}

Fraction Fraction::operator*(Fraction& that) const {
    const FractionFareyMSS num1 = FractionFareyMSS(_transform(_numerator), _modules);
    const FractionFareyMSS num2 = FractionFareyMSS(_transform(that._numerator), _modules);
    const FractionFareyMSS det1 = FractionFareyMSS(_transform(_denominator), _modules);
    const FractionFareyMSS det2 = FractionFareyMSS(_transform(that._denominator), _modules);
    return Fraction((num1 * num2).get_num(), (det1 * det2).get_num(), _modules);
}

std::pair<int, int> Fraction::_transform(int num) const {
    int s = 0;
    while (num % 10 == 0) {
        if (num == 0) break;
        num = num / 10;
        ++s;
    }
    return std::pair<int, int>(num, s);
}

std::string Fraction::to_string() const {
    return std::to_string(_numerator) + '/' + std::to_string(_denominator);
}

void Fraction::print() const {
    std::cout << to_string() << std::endl;
}