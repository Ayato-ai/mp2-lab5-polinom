#include "polinom.h"
#include <gtest.h>
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

vector<Term*> sintax_analis(string str);

bool analis(const vector<Term*> terms);

class Polinom_Test : public ::testing::Test {
protected:
	void SetUp() {
		polinom_1 = new Polynom();
		polinom_2 = new Polynom();
		polinom_3 = new Polynom();
	}
	void SetUp_new(string str) {
		polinom_1 = new Polynom(sintax_analis(str));
		polinom_2 = new Polynom();
		polinom_3 = new Polynom();
	}
	void SetUp_three_new(string str_1, string str_2, string str_3) {
		polinom_1 = new Polynom(sintax_analis(str_1));
		polinom_2 = new Polynom(sintax_analis(str_2));
		polinom_3 = new Polynom(sintax_analis(str_3));
	}
	void TearDown() {
		delete polinom_1;
		delete polinom_2;
		delete polinom_3;
	}
	void TearDown_new() {
		delete polinom_1;
		delete polinom_2;
		delete polinom_3;
	}
	void TearDown_three_new() {
		delete polinom_1;
		delete polinom_2;
		delete polinom_3;
	}
	Polynom* polinom_1;
	Polynom* polinom_2;
	Polynom* polinom_3;
};
TEST_F(Polinom_Test, can_polinom) {
	ASSERT_NO_THROW(this->SetUp());
};
TEST_F(Polinom_Test, can_polinom_with_data) {
	ASSERT_NO_THROW(this->SetUp_new("xz-6"));
};
TEST_F(Polinom_Test, throw_can_polinom) {
	ASSERT_ANY_THROW(this->SetUp_new("5+zx^12"));
};
TEST_F(Polinom_Test, can_copy_polinom) {
	this->SetUp_new("9+2zx^3");

	Polynom polinom_copy(*this->polinom_1);

	EXPECT_EQ(*this->polinom_1, polinom_copy);
};
TEST_F(Polinom_Test, polinom_operator_addition) {
	this->SetUp_three_new("5+x", "z-y^2", "5+x-y^2+z");

	EXPECT_EQ(*this->polinom_1 + *this->polinom_2, *this->polinom_3);
};
TEST_F(Polinom_Test, polinom_operator_addition_with_similar_terms) {
	this->SetUp_three_new("5+xz", "-9-y^2-xz", "-4-y^2");

	EXPECT_EQ(*this->polinom_1 + *this->polinom_2, *this->polinom_3);
};
TEST_F(Polinom_Test, polinom_operator_multiplying) {
	this->SetUp_three_new("5+x", "-9-y^2", "-45-9x-5y^2-xy^2");

	EXPECT_EQ(*this->polinom_1 * *this->polinom_2, *this->polinom_3);
};
/*
TEST_F(Polinom_Test, throw_polinom_operator_multiplying) {

};
TEST_F(Polinom_Test, polinom_operator_multiplying_on_const) {

};
TEST_F(Polinom_Test, polinom_operator_equal) {

};
TEST_F(Polinom_Test, polinom_operator_not_equal) {

};
TEST_F(Polinom_Test, polinom_operator_asign) {

};
TEST_F(Polinom_Test, polinom_operator_to_string) {

};
TEST_F(Polinom_Test, polinom_value_at_point) {

};
*/