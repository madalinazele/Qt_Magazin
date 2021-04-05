#pragma once

#include "Domain.h"
#include <vector>
#include <string>
using namespace std;

class ValidateException {
	vector<string> msg;
public:
	ValidateException(const vector<string>& errors) : msg{ errors } {}

	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

class Validator {
public:
	void validate(const Product& p);
};
