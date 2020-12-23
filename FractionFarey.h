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
	
	std::string to_string() const; // �������� �����
	void print() const; // ������ �����
 
private:
	FractionFarey(const int&, const int&, const int&);
	int _module; // ������
	int _n; // ������� ����� �����
	int _numerator; // ��������� �����
	int _denominator; // ����������� �����
	int _representation; // ����� ������������� �����

	// ������ �������������� �����
	void dir_transmit();
	// �������� �������������� �����
	void inv_transmit();
	// ����������� �������� ������� ���������� ��������� ����� �� ������ module
	int extended_EucReverse() const;
	// ����������� �������� ������� - �������� ��������������
	std::pair<int, int> extended_EucFarey() const;
};

