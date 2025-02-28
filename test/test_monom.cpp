#include "polinom.h"

#include <gtest.h>

class Monom_Test : public ::testing::Test {
protected:
	void SetUp() {
		monom_1 = new Monom();
		monom_2 = new Monom();
		monom_3 = new Monom();
	};
	void SetUp_new(int k, int x, int y, int z) {
		monom_1 = new Monom(k, x, y, z);
		monom_2 = new Monom();
	};
	void TearDown() {
		delete monom_1;
		delete monom_2;
		delete monom_3;
	}
	void TearDown_new() {
		delete monom_1;
		delete monom_2;
	}
	Monom* monom_1;
	Monom* monom_2;
	Monom* monom_3;
};
TEST_F(Monom_Test, can_monom) {
	ASSERT_NO_THROW(this->SetUp());
};
TEST_F(Monom_Test, can_monom_with_data) {
	ASSERT_NO_THROW(this->SetUp_new(1, 2, 3, 4));
};
TEST_F(Monom_Test, can_monom_with_greater_degree) {
	ASSERT_ANY_THROW(this->SetUp_new(1, 12, 3, 4));
};
TEST_F(Monom_Test, can_copy_monoms) {
	this->SetUp_new(1, 2, 3, 4);
	Monom monom_copy(*monom_1);

	EXPECT_EQ(monom_1, monom_copy);
};
TEST_F(Monom_Test, monom_set_degree) {
	this->SetUp();

	monom_1->set_degree(102);

	EXPECT_EQ(monom_1->get_degree(), 102);
};
TEST_F(Monom_Test, monom_set_coef) {
	this->SetUp();

	monom_1->set_coef(45);

	EXPECT_EQ(monom_1->get_coef(), 45);
};
TEST_F(Monom_Test, correct_x_deg) {
	this->SetUp_new(1, 2, 3, 4);

	EXPECT_EQ(monom_1->x_deg(), 2);
};
TEST_F(Monom_Test, correct_y_deg) {
	this->SetUp_new(1, 2, 3, 4);

	EXPECT_EQ(monom_1->y_deg(), 3);
}
TEST_F(Monom_Test, correct_z_deg) {
	this->SetUp_new(1, 2, 3, 4);

	EXPECT_EQ(monom_1->z_deg(), 4);
};
TEST_F(Monom_Test, monoms_operator_addition_correct_degree) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(12);
	monom_2->set_degree(234);

	EXPECT_EQ((*monom_2 + *monom_1).get_degree(), 234);
};
TEST_F(Monom_Test, monoms_operator_addition_correct_coef) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(234);

	EXPECT_EQ((*monom_2 + *monom_1).get_coef(), -4);
};
TEST_F(Monom_Test, monoms_operator_addition_correct_equal) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(234);

	monom_3->set_coef(-4);
	monom_3->set_degree(234);
	//  x^2y^3z^4 + (-5)x^2y^3z^4
	EXPECT_EQ((*monom_2 + *monom_1), *monom_3);
};
TEST_F(Monom_Test, throw_monoms_operator_addition) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(634);

	ASSERT_ANY_THROW(*monom_1 + *monom_2);
};
TEST_F(Monom_Test, monoms_operator_multiplying_correct_degree) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(125);

	EXPECT_EQ((*monom_2 * *monom_1).get_degree(), 359);
};
TEST_F(Monom_Test, monoms_operator_multiplying_correct_coef) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(125);

	EXPECT_EQ((*monom_2 * *monom_1).get_coef(), -5);
};
TEST_F(Monom_Test, monoms_operator_multiplying_correct_equal) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(125);

	monom_3->set_coef(-5);
	monom_3->set_degree(359);

	EXPECT_EQ((*monom_2 * *monom_1), *monom_3);
};
TEST_F(Monom_Test, throw_monoms_operator_multiplying) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(127);

	ASSERT_ANY_THROW(*monom_1 * *monom_2);
};
TEST_F(Monom_Test, monoms_operator_multiplying_on_const) {
	this->SetUp_new(1, 2, 3, 4);

	EXPECT_EQ((*monom_1 * 7).get_coef(), 7);
};
TEST_F(Monom_Test, monoms_operator_equal) {
	this->SetUp_new(1, 2, 3, 4);

	*monom_2 = *monom_1;

	EXPECT_EQ(*monom_1 == *monom_2, 1);
};
TEST_F(Monom_Test, monoms_operator_not_equal) {
	this->SetUp_new(1, 2, 3, 4);

	monom_2->set_coef(-5);
	monom_2->set_degree(127);

	EXPECT_EQ(*monom_1 != *monom_2, 1);
};
TEST_F(Monom_Test, asign_operation_monoms) {
	this->SetUp_new(1, 2, 3, 4);

	*monom_2 = *monom_1;

	EXPECT_EQ(*monom_1, *monom_2);
};


