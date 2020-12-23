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

	void _direct_transmit(); // ������ �������������� �����
	void _invers_transmit(); // �������� �������������� �����

	std::vector<int64_t> _modules; // ������
	std::vector<int> _presentation; // ���������� ������������� �����
	int64_t _num; // ���� ���������� �����
	int64_t _p; // ������������ �������
	int _t; // ������� �����
};

