// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
// 
// Носков И.А.
#pragma warning(disable : 4996)

const int MAX_DEG = 9;

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
enum types { number, operation, variable, nun };

class Term {
private:
	types type;
public:
	Term(types type = nun) : type(type) {};
	types get_type() const noexcept {
		return type;
	}
};

class Number : public Term {
private:
	int value;
public:
	Number(int value = 0) : value(value), Term(number) {};
	int get_number() const noexcept {
		return value;
	};
};

class Operation : public Term {
private:
	char oper;
public:
	Operation(char oper = ' ') : oper(oper), Term(operation) {};
	char get_operation() const noexcept {
		return oper;
	}
};

class Variable : public Term {
private:
	char var;
public:
	Variable(char var = ' ') : var(var), Term(variable) {};
	char get_variable() const noexcept {
		return var;
	}
};

class Monom {
private:
	int degree;
	int k;
public:
	Monom(int k = 0, int x = 0, int y = 0, int z = 0): degree(100 * x + 10 * y + z), k(k){
		if (x < MAX_DEG && y < MAX_DEG && z < MAX_DEG) {
			degree = 100 * x + 10 * y + z;
			k = k;
		}
		else
			throw("degree_greater_nine");
	};
	Monom(const Monom& monom) {
		degree = monom.degree;
		k = monom.k;
	};
	int get_coef() const noexcept {
		return k;
	}
	int get_degree() const noexcept {
		return degree;
	}
	void set_coef(int coef) {
		k = coef;
	}
	void set_degree(int d) {
		degree = d;
	}
	int x_deg() const {
		return degree / 100;
	};
	int y_deg() const {
		return (degree / 10) % 10;
	};
	int z_deg() const {
		return degree % 10;
	};
	bool is_deg_correct() const {
		return (x_deg() <= MAX_DEG && y_deg() <= MAX_DEG && z_deg() <= MAX_DEG);
	}
	Monom operator+(const Monom& monom) const {
		Monom result;
		if (degree == monom.degree) {
			result.k = k + monom.k;
			result.degree = degree;
		}
		else
			throw ("error");
		return result;
	};
	Monom operator*(const Monom& monom) const {
		Monom result;
		result.k = k * monom.k;
		if (x_deg() + monom.x_deg() > MAX_DEG)
			throw ("degree_X_greater_nine");
		if (y_deg() + monom.y_deg() > MAX_DEG)
			throw ("degree_Y_greater_nine");
		if (z_deg() + monom.z_deg() > MAX_DEG)
			throw ("degree_Z_greater_nine");
		result.degree = degree + monom.degree;
		return result;
	};
	Monom operator*(int c) const {
		Monom result;
		result.k = k * c;
		result.degree = degree;
		return result;
	};
	Monom& operator=(const Monom& monom) {
		if (this != &monom) {
			degree = monom.degree;
			k = monom.k;
		}
		return *this;
	};
	bool operator==(const Monom& monom) const {
		if (degree == monom.degree && k == monom.k)
			return true;
		else
			return false;
	};
	bool operator!=(const Monom& monom) const {
		return !(*this == monom);
	};


	~Monom() {};
};

class Polynom {
private:
	list<Monom> lists;
public:

	friend vector<Term*> sintax_analis(string str);

	friend bool analis(const vector<Term*> terms);

	Polynom() {
		Monom head(0, 0, 0, 0);
		lists.push_back(head);
	};
	Polynom(vector<Term*> terms) {
		if (!analis(terms))
			throw("sintax_error");
		Monom head(0, 0, 0, 0);
		lists.push_back(head);
		types pos;
		bool sign = false;
		int c = 0, x = 0, y = 0, z = 0;

		if (terms[0]->get_type() == number) {
			pos = number;
			c = ((Number*)terms[0])->get_number();
		}
		if (terms[0]->get_type() == operation) {
			if (((Operation*)terms[0])->get_operation() == '-')
				sign = true;
			pos = operation;
		}
		if (terms[0]->get_type() == variable) {
			if (((Variable*)terms[0])->get_variable() == 'x')
				x = 1;
			if (((Variable*)terms[0])->get_variable() == 'y')
				y = 1;
			if (((Variable*)terms[0])->get_variable() == 'z')
				z = 1;
			pos = variable;
			c = 1;
		}

		for (int i = 1; i < terms.size(); i++) {
			switch (terms[i]->get_type()) {
			case operation:
				if (((Operation*)terms[i])->get_operation() != '^') {
					if (sign)
						c = -c;
					Monom next(c, x, y, z);
					lists.push_back(next);
					c = 0; x = 0; y = 0; z = 0;
					sign = false;
					if (((Operation*)terms[i])->get_operation() == '-')
						sign = true;
				}
				pos = operation;
				break;
			case number:
				if (pos == operation)
					if (((Operation*)terms[i - 1])->get_operation() == '^') {
						if (((Variable*)terms[i - 2])->get_variable() == 'x')
							x = ((Number*)terms[i])->get_number();
						if (((Variable*)terms[i - 2])->get_variable() == 'y')
							y = ((Number*)terms[i])->get_number();
						if (((Variable*)terms[i - 2])->get_variable() == 'z')
							z = ((Number*)terms[i])->get_number();
					}
					else
						c = ((Number*)terms[i])->get_number();
				pos = number;
				break;
			case variable:
				if (((Variable*)terms[i])->get_variable() == 'x')
					x = 1;
				if (((Variable*)terms[i])->get_variable() == 'y')
					y = 1;
				if (((Variable*)terms[i])->get_variable() == 'z')
					z = 1;
				if (c == 0)
					c = 1;
				pos = variable;
				break;
			default:
				break;
			}
		}
		if (sign)
			c = -c;
		Monom next_(c, x, y, z);
		lists.push_back(next_);
		sort_lists();
	};
	Polynom(Polynom& polynom) {
		if (this != &polynom) {
			lists.clear();

			list<Monom>::iterator iterator_1;
			iterator_1 = polynom.lists.begin();

			while (iterator_1 != polynom.lists.end()) {
				Monom next(*iterator_1);
				lists.push_back(next);
				++iterator_1;
			}
		}
	};
	void sort_lists() {
		vector<Monom> vector_monoms;
		list<Monom>::iterator iterator_1;
		iterator_1 = lists.begin();


		while (iterator_1 != lists.end()) {
			vector_monoms.push_back(*iterator_1);
			++iterator_1;
		}
		sort(vector_monoms.begin(), vector_monoms.end(), [](const Monom& first, const Monom& second) { return first.get_degree() < second.get_degree(); });

		int j = 1;
		for (int i = 0; i < vector_monoms.size() - 1; i++) {
			j = 1;
			while ((i + j) < vector_monoms.size() && vector_monoms[i].get_degree() == vector_monoms[i + j].get_degree()) {
				vector_monoms[i] = (vector_monoms[i] + vector_monoms[i + j]);
				vector_monoms[i + j].set_coef(0);
				j++;
			}
			i += j - 1;
		}
		lists.clear();
		for (int i = 0; i < vector_monoms.size(); i++) {
			if (vector_monoms[i].get_coef() != 0)
				lists.push_back(vector_monoms[i]);
		}
	};
	Polynom operator+(const Polynom& polynom) const {
		Polynom result;
		list<Monom>::const_iterator iterator_1, iterator_2;

		iterator_1 = lists.begin();
		iterator_2 = polynom.lists.begin();

		while (iterator_1 != lists.end()) {
			result.lists.push_back(*iterator_1);
			++iterator_1;
		}
		while (iterator_2 != polynom.lists.end()) {
			result.lists.push_back(*iterator_2);
			++iterator_2;
		}
		//result.lists.push_back(*iterator_1);
		//result.lists.push_back(*iterator_2);

		result.sort_lists();
		return result;
	};
	//Polynom operator-(const Polynom& polynom) const {};
	Polynom operator*(const Polynom& polynom) const {
		Polynom result;
		list<Monom>::const_iterator iterator_1, iterator_2;

		iterator_1 = lists.begin();
		iterator_2 = polynom.lists.begin();

		while (iterator_1 != lists.end()) {
			while (iterator_2 != polynom.lists.end()) {
				result.lists.push_back(*iterator_1 * *iterator_2);
				++iterator_2;
			}
			iterator_2 = polynom.lists.begin();
			++iterator_1;
		}

		result.sort_lists();
		return result;
	};
	Polynom operator*(int c) const {
		Polynom result;
		list<Monom>::const_iterator iterator_1;
		iterator_1 = lists.begin();

		while (iterator_1 != lists.end()) {
			result.lists.push_back(*iterator_1 * c);
			++iterator_1;
		}
		result.sort_lists();
		return result;
	};
	Polynom& operator=(const Polynom& polynom) {
		if (this != &polynom) {
			list<Monom>::const_iterator iterator_1;
			iterator_1 = polynom.lists.begin();

			lists.clear();
			while (iterator_1 != polynom.lists.end()) {
				Monom next(*iterator_1);
				lists.push_back(next);
				++iterator_1;
			}
		}
		return *this;
	};
	bool operator==(const Polynom& polynom) const {
		list<Monom>::const_iterator iterator_1, iterator_2;
		iterator_1 = lists.begin();
		iterator_2 = polynom.lists.begin();

		while (iterator_1 != lists.end() || iterator_2 != polynom.lists.end()) {
			if (*iterator_1 != *iterator_2)
				return false;
			++iterator_1;
			++iterator_2;
		}
		if (iterator_1 != lists.end() && iterator_2 != polynom.lists.end())
			return false;
		return true;
	};
	bool operator!=(const Polynom& polynom) const {
		return !(*this == polynom);
	};
	string String() const {
		string result;
		list<Monom>::const_iterator iterator_1;
		iterator_1 = lists.begin();

		while (iterator_1 != lists.end()) {
			if (iterator_1 == lists.begin()) {
				if (iterator_1->get_coef() == 1) {
					if (iterator_1->get_degree() == 0)
						result += '1';
				}
				else if (iterator_1->get_coef() == -1)
					result += '-';
				else
					result += to_string(iterator_1->get_coef());
			}
			else {
				if (iterator_1->get_coef() > 1) {
					result += '+';
					result += to_string(iterator_1->get_coef());
				}
				else if (iterator_1->get_coef() == 1)
					result += '+';
				else if (iterator_1->get_coef() == -1)
					result += '-';
				else
					result += to_string(iterator_1->get_coef());
			}

			if (iterator_1->x_deg() == 1)
				result += 'x';
			if (iterator_1->x_deg() > 1) {
				result += "x^";
				result += to_string(iterator_1->x_deg());
			}

			if (iterator_1->y_deg() == 1)
				result += 'y';
			if (iterator_1->y_deg() > 1) {
				result += "y^";
				result += to_string(iterator_1->y_deg());
			}

			if (iterator_1->z_deg() == 1)
				result += 'z';
			if (iterator_1->z_deg() > 1) {
				result += "z^";
				result += to_string(iterator_1->z_deg());
			}
			++iterator_1;
		}
		return result;
	};
	int value_at_point(int x, int y, int z) const {
		int result = 0;
		list<Monom>::const_iterator iterator_1;
		iterator_1 = lists.begin();

		while (iterator_1 != lists.end()) {
			result += iterator_1->get_coef() * pow(x, iterator_1->x_deg()) * pow(y, iterator_1->y_deg()) * pow(z, iterator_1->z_deg());
			++iterator_1;
		}
		return result;
	};

	~Polynom() {};
};
