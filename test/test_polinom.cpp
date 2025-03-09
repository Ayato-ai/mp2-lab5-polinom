#include "polinom.h"
#include <gtest.h>

class Polinom_Test : public ::testing::Test {
protected:
	void SetUp_void() {
		;
	} 
	void SetUp() {
		polinom_1 = new Polynom();
	}
	void SetUp_new(string str) {
		polinom_1 = new Polynom(sintax_analis(str));
		polinom_2 = new Polynom();
	}
	void SetUp_three_new(string str_1, string str_2, string str_3) {
		polinom_1 = new Polynom(sintax_analis(str_1));
		polinom_2 = new Polynom(sintax_analis(str_2));
		polinom_3 = new Polynom(sintax_analis(str_3));
	}
	void TearDown() {
		delete polinom_1;
	}
	void TearDown_new() {
		delete polinom_1;
		delete polinom_2;
	}
	void TearDown_three_new() {
		delete polinom_1;
		delete polinom_2;
		delete polinom_3;
	}
	Polynom* polinom_1;
	Polynom* polinom_2;
	Polynom* polinom_3;
};/*
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

TEST_F(Polinom_Test, throw_polinom_operator_multiplying) {
	this->SetUp_three_new("5+xz^4", "-9-y^2-xz^7", "0");

	ASSERT_ANY_THROW(*this->polinom_1 * *this->polinom_2);
};
TEST_F(Polinom_Test, polinom_operator_multiplying_on_const) {
	this->SetUp_three_new("23+xz^2-5z", "69+3xz^2-15z", "5+z");

	EXPECT_EQ(*this->polinom_1 * 3, *this->polinom_2);
};
TEST_F(Polinom_Test, polinom_operator_equal) {
	this->SetUp_three_new("23+xz^2-5z", "23+xz^2-5z", "5+z");

	EXPECT_EQ(*this->polinom_1 == *this->polinom_2, 1);
};
TEST_F(Polinom_Test, polinom_operator_not_equal) {
	this->SetUp_three_new("23+xz^2-5z", "69+3xz^2-15z", "5+z");

	EXPECT_EQ(*this->polinom_1 != *this->polinom_2, 1);
};
TEST_F(Polinom_Test, polinom_operator_asign) {
	this->SetUp_new("9+2zx^3");

	*this->polinom_2 = *this->polinom_1;

	EXPECT_EQ(*this->polinom_1, *this->polinom_2);
};
TEST_F(Polinom_Test, polinom_operator_to_string) {
	this->SetUp_new("2zx^3-9");

	EXPECT_EQ(this->polinom_1->String(), "-9+2x^3z");
};
TEST_F(Polinom_Test, polinom_value_at_point) {
	this->SetUp_new("2zx^3-9");

	EXPECT_EQ(this->polinom_1->value_at_point(1, 2, 3), -3);
};
TEST_F(Polinom_Test, polinom_add_empty_polinom) {
	this->SetUp_three_new("5+xz-xy^3", "0", "0");

	EXPECT_EQ(*this->polinom_1 + *this->polinom_2 == *this->polinom_1, 1);
}
*/
TEST_F(Polinom_Test, polinom_sintax_analis_correct) {
	this->SetUp_void();

	EXPECT_EQ(analis(sintax_analis("5+xz^4-56xy^5z^2+565z^7")), true);
}
TEST_F(Polinom_Test, polinom_sintax_analis_not_correct) {
	this->SetUp_void();

	EXPECT_EQ(analis(sintax_analis("5+xz^4-56x^4y^5z^2++565z^7")), false);
}