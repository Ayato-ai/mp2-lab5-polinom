// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
// 
// Носков И.А.
#pragma warning(disable : 4996)

const int MAX_DEG = 9;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
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


template <typename Item>
struct node {
public:
	node* next = nullptr;
	Item data;

	node(Item item, node* next = nullptr) : data(item), next(next) {};

};


template <typename Item>
class my_list {
private:
	node<Item>* m_head = nullptr;
	node<Item>* m_tail = nullptr;
	size_t sz = 0;
public:
	using value_type = Item;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	my_list() = default;
	my_list(std::initializer_list<Item> items) {
		for (auto& item : items)
			push_back(item);
	};
	size_t get_size() const noexcept {
		return sz;
	}
	Item& operator[](size_t index) {
		node<Item>* node_ = m_head;
		for (size_t i = 0; i < index; i++)
			node_ = node_->next;
		return node_->data;
	};
	void pop_back() {
		if (sz == 0)
			throw ("list_is_empty");
		if (sz == 1) {
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
			sz = 0;
			return;
		}
		node<Item>* new_node = m_head;
		for (size_t i = 0; i < sz - 2; i++)
			new_node = new_node->next;
		delete new_node->next;
		m_tail = new_node;
		sz--;
	};
	void pop_front() {
		if (sz == 0)
			throw ("list_is_empty");
		node<Item>* new_node = m_head;
		new_node = new_node->next;
		delete m_head;
		m_head = new_node;
		sz--;
	};
	void push_front(value_type item) {
		node<Item>* new_node = new node<Item>(item);
		if (m_head) {
			new_node->next = m_head;
			m_head = new_node;
		}
		else
			m_head = m_tail = new_node;
		sz++;
	};
	void push_back(value_type item) {
		node<Item>* new_node = new node<Item>(item);
		if (m_head) {
			m_tail->next = new_node;
			m_tail = new_node;
		}
		else {
			m_head = new_node;
			m_tail = new_node;
		}
		sz++;
	};
	my_list<Item>& operator=(my_list<Item>& list) {
		if (this != &list) {
			this->clear();

			for (size_t i = 0; i < list.sz; i++) {
				this->push_back(list[i]);
			}
		}
		return *this;
	}
	bool operator==(my_list<Item>& list) const {
		if (sz != list.sz)
			return false;
		my_list<Item>::iterator iter_1(begin());
		my_list<Item>::iterator iter_2(list.begin());
		for (size_t i = 0; i < sz; i++) {
			if (*iter_1 != *iter_2)
				return false;
		}
		return true;
	};
	bool operator!=(my_list<Item>& list) const {
		return !(*this == list);
	};
	void clear() {
		if (sz != 0)
			for (size_t i = 0; i < sz; i++)
				delete std::exchange(m_head, m_head->next);

		sz = 0;
		m_tail = nullptr;
		m_head = nullptr;
	};
	friend std::ostream& operator<<(std::ostream& os, my_list<Item>& list) {
		for (size_t i = 0; i < list.sz; i++)
			os << list[i] << std::endl;
		return os;
	}
	~my_list() {
		clear();
	}

	node<Item>* begin() const {
		if (m_head != nullptr)
			return m_head;
		else
			throw ("m_head_list_is_null");
	};
	node<Item>* end() const noexcept {
		return m_tail->next;
	};

	const node<Item>* cbegin() const  {
		if (m_head != nullptr)
			return m_head;
		else
			throw ("m_head_list_is_null");
	};
	const node<Item>* cend() const noexcept {
		return m_tail->next;
	};


	class iterator {
	private:
		node<Item>* m_current;

	public:
		friend class my_list<Item>;

		iterator() = default;
		explicit iterator(node<Item>* ptr) : m_current(ptr) {};

		iterator& operator++() {
			m_current = m_current->next;
			return *this;
		};
		node<Item>* get_ptr() const {
			return m_current;
		};
		iterator& operator++(int index) {
			for (size_t i = 0; i < index; i++)
				m_current = m_current->next;
			return *this;
		};
		iterator& operator=(iterator& iter) {
			if (*this != iter)
				m_current = iter.m_current;
			return *this;
		};
		bool operator==(iterator& iter) const {
			if (m_current == iter.m_current)
				return true;
			else
				return false;
		};
		bool operator!=(iterator& iter) const {
			return !(*this == iter);
		};
		Item operator*() const {
			return m_current->data;
		};
		iterator& change(node<Item>* ptr) {
			m_current = ptr;
			return *this;
		};
		~iterator() {
			m_current = nullptr;
		};
	};
	class const_iterator {
	private:
		const node<Item>* m_current;

	public:
		friend class my_list<Item>;

		const_iterator() = default;
		explicit const_iterator(const node<Item>* ptr) : m_current(ptr) {};
		const_iterator& operator++() {
			m_current = m_current->next;
			return *this;
		};
		const node<Item>* get_ptr() const {
			return m_current;
		};
		iterator& operator++(int index) {
			for (size_t i = 0; i < index; i++)
				m_current = m_current->next;
			return *this;
		};
		iterator& operator=(const_iterator& iter) {
			if (this != iter)
				m_current = iter.m_current;
			return *this;
		};
		bool operator==(const_iterator& iter) const {
			if (m_current == iter.m_current)
				return true;
			else
				return false;
		};
		bool operator!=(const_iterator& iter) const {
			return !(*this == iter);
		};
		Item operator*() const {
			return m_current->data;
		};
		const_iterator& change(const node<Item>* ptr) {
			m_current = ptr;
			return *this;
		};
		~const_iterator() {
			m_current = nullptr;
		};
	};

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
			throw ("degree_ancorrect");
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
	friend class Polynom;
	
	~Monom() {};
};

inline bool analis(vector<Term*> terms) {
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

inline vector<Term*> sintax_analis(string str) {
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

class Polynom {
private:
	my_list<Monom> lists;
public:
	friend vector<Term*> sintax_analis(string str);

	friend bool analis(vector<Term*> terms);

	Polynom() {
		Monom head(0, 0, 0, 0);
		lists.push_back(head);
	};
	Polynom(vector<Term*> terms) {
		if (!analis(terms))
			throw("sintax_error");
		Monom head(0, 0, 0, 0);
		lists.push_back(head);
		types pos{};
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

			my_list<Monom>::iterator iterator_1(polynom.lists.begin());

			while (iterator_1.get_ptr() != polynom.lists.end()) {
				Monom next(*iterator_1);
				lists.push_back(next);
				++iterator_1;
			}
		}
	};
	void sort_lists() {
		vector<Monom> vector_monoms;
		my_list<Monom>::iterator iterator_1(lists.begin());

		while (iterator_1.get_ptr() != lists.end()) {
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
		if (lists.get_size() == 0) {
			Monom head(0, 0, 0, 0);
			lists.push_back(head);
		}
	};
	Polynom operator+(const Polynom& polynom) const {
		Polynom result;
		my_list<Monom>::const_iterator iterator_1(lists.cbegin());
		my_list<Monom>::const_iterator iterator_2(polynom.lists.cbegin());

		while (iterator_1.get_ptr() != lists.cend()) {
			result.lists.push_back(*iterator_1);
			++iterator_1;
		}
		while (iterator_2.get_ptr() != polynom.lists.cend()) {
			result.lists.push_back(*iterator_2);
			++iterator_2;
		}

		result.sort_lists();
		return result;
	};

	Polynom operator*(const Polynom& polynom) const {
		Polynom result;
		my_list<Monom>::const_iterator iterator_1(lists.cbegin());
		my_list<Monom>::const_iterator iterator_2(polynom.lists.cbegin());

		while (iterator_1.get_ptr() != lists.cend()) {
			while (iterator_2.get_ptr() != polynom.lists.cend()) {
				result.lists.push_back(*iterator_1 * *iterator_2);
				++iterator_2;
			}
			iterator_2.change(polynom.lists.cbegin());
			++iterator_1;
		}

		result.sort_lists();
		return result;
	};
	Polynom operator*(int c) const {
		Polynom result;
		my_list<Monom>::const_iterator iterator_1(lists.cbegin());

		while (iterator_1.get_ptr() != lists.cend()) {
			result.lists.push_back(*iterator_1 * c);
			++iterator_1;
		}
		result.sort_lists();
		return result;
	};
	Polynom& operator=(const Polynom& polynom) {
		if (this != &polynom) {
			my_list<Monom>::const_iterator iterator_1(polynom.lists.cbegin());

			lists.clear();
			while (iterator_1.get_ptr() != polynom.lists.cend()) {
				Monom next(*iterator_1);
				lists.push_back(next);
				++iterator_1;
			}
		}
		return *this;
	};
	bool operator==(const Polynom& polynom) const {
		my_list<Monom>::const_iterator iterator_1(lists.cbegin());
		my_list<Monom>::const_iterator iterator_2(polynom.lists.cbegin());

		while (iterator_1.get_ptr() != lists.cend() || iterator_2.get_ptr() != polynom.lists.cend()) {
			if (*iterator_1 != *iterator_2)
				return false;
			++iterator_1;
			++iterator_2;
		}
		if (iterator_1.get_ptr() != lists.cend() && iterator_2.get_ptr() != polynom.lists.cend())
			return false;
		return true;
	};
	bool operator!=(const Polynom& polynom) const {
		return !(*this == polynom);
	};
	string String() const {
		string result;
		my_list<Monom>::const_iterator iterator_1(lists.begin());

		while (iterator_1.get_ptr() != lists.cend()) {
			if (iterator_1.get_ptr() == lists.cbegin()) {
				if ((iterator_1.get_ptr())->data.get_coef() == 1) {
					if ((iterator_1.get_ptr())->data.get_degree() == 0)
						result += '1';
				}
				else if ((iterator_1.get_ptr())->data.get_coef() == -1)
					result += '-';
				else
					result += to_string((iterator_1.get_ptr())->data.get_coef());
			}
			else {
				if ((iterator_1.get_ptr())->data.get_coef() > 1) {
					result += '+';
					result += to_string((iterator_1.get_ptr())->data.get_coef());
				}
				else if ((iterator_1.get_ptr())->data.get_coef() == 1)
					result += '+';
				else if ((iterator_1.get_ptr())->data.get_coef() == -1)
					result += '-';
				else
					result += to_string((iterator_1.get_ptr())->data.get_coef());
			}

			if (iterator_1.get_ptr()->data.x_deg() == 1)
				result += 'x';
			if (iterator_1.get_ptr()->data.x_deg() > 1) {
				result += "x^";
				result += to_string(iterator_1.get_ptr()->data.x_deg());
			}

			if (iterator_1.get_ptr()->data.y_deg() == 1)
				result += 'y';
			if (iterator_1.get_ptr()->data.y_deg() > 1) {
				result += "y^";
				result += to_string(iterator_1.get_ptr()->data.y_deg());
			}

			if (iterator_1.get_ptr()->data.z_deg() == 1)
				result += 'z';
			if (iterator_1.get_ptr()->data.z_deg() > 1) {
				result += "z^";
				result += to_string(iterator_1.get_ptr()->data.z_deg());
			}
			++iterator_1;
		}
		return result;
	};
	int value_at_point(int x, int y, int z) const {
		int result = 0;
		my_list<Monom>::iterator iterator_1(lists.begin());

		while (iterator_1.get_ptr() != lists.end()) {
			result += (iterator_1.get_ptr())->data.get_coef() * pow(x, iterator_1.get_ptr()->data.x_deg()) * pow(y, iterator_1.get_ptr()->data.y_deg()) * pow(z, iterator_1.get_ptr()->data.z_deg());
			++iterator_1;
		}
		return result;
	};

	~Polynom() {
		lists.~my_list();
	};
};
