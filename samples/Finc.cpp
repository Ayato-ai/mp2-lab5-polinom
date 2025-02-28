#include "polinom.h"

vector<Term*> sintax_analis(const string str) {
	vector<Term*> terms;
	int number_status = 0;
	string n;
	for (int i = 0; i < str.size(); i++) {
		if (number_status == 0) {
			if (str[i] == '+' || str[i] == '-' || str[i] == '^') {
				terms.push_back(new Operation(str[i]));
			}
			else if (str[i] >= '0' && str[i] <= '9') {
				number_status = 1;
				n += str[i];
			}
			else if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z') {
				terms.push_back(new Variable(str[i]));
			}
		}
		else {
			if (str[i] >= '0' && str[i] <= '9') {
				n += str[i];
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '^') {
				number_status = 0;
				terms.push_back(new Number(stoi(n)));
				terms.push_back(new Operation(str[i]));
				n.clear();
			}
			else if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z') {
				number_status = 0;
				terms.push_back(new Number(stoi(n)));
				terms.push_back(new Variable(str[i]));
				n.clear();
			}
		}
	}
	if (number_status) {
		terms.push_back(new Number(stoi(n)));
	}
	return terms;
};

bool analis(const vector<Term*> terms) {
	types pos = nun;
	if (terms[0]->get_type() == number) {
		pos = number;
	}
	if (terms[0]->get_type() == operation) {
		if (((Operation*)terms[0])->get_operation() == '^')
			return false;
		pos = operation;
	}
	if (terms[0]->get_type() == variable) {
		pos = variable;
	}
	if (terms[0])
		for (int i = 1; i < terms.size(); i++) {
			switch (terms[i]->get_type()) {
			case number:
				if (pos == number || pos == variable)
					return false;
				pos = number;
				break;
			case operation:
				if (pos == operation)
					return false;
				if (((Operation*)terms[i])->get_operation() == '^')
					if (pos != variable)
						return false;
				pos = operation;
				break;
			case variable:
				if (pos == operation)
					if (((Operation*)terms[i - 1])->get_operation() == '^')
						return false;
				pos = variable;
				break;
			default:
				break;
			}
		}
	if (terms[terms.size() - 1]->get_type() == operation)
		return false;
	return true;
};