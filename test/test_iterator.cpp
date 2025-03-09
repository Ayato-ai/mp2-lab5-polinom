#include "polinom.h"
#include <gtest.h>

class Iterator_Test : public ::testing::Test {
protected:
	void SetUp() {
		list_1 = new my_list<Monom>;
		list_2 = new my_list<Monom>;

		(*list_1).push_back(Monom(1, 1, 1, 1));
		(*list_1).push_back(Monom(2, 1, 1, 2));
		// list_1 = xyz + 2xyz^2
		(*list_2).push_back(Monom(-1, 1, 1, 1));
		//list_2 = -xyz
		iter_1 = new my_list<Monom>::iterator((*list_1).begin());
		iter_2 = new my_list<Monom>::iterator((*list_2).begin());
	}
	void SetUpOne() {
		list_1 = new my_list<Monom>;
		iter_1 = new my_list<Monom>::iterator;
	}
	void TearDown() {
		delete iter_1;
		delete iter_2;

		delete list_1;
		delete list_2;
	};
	void TearDownOne() {
		delete list_1;
		delete iter_1;
	};
	my_list<Monom>* list_1;
	my_list<Monom>* list_2;
	my_list<Monom>::iterator* iter_1;
	my_list<Monom>::iterator* iter_2;
};

TEST_F(Iterator_Test, throw_create_iterator) {
	ASSERT_NO_THROW(this->SetUpOne());
};
TEST_F(Iterator_Test, iterator_operator_increment) {
	this->SetUp();

	++(*iter_1);

	EXPECT_NE((*iter_1).get_ptr(), list_1->begin());
};
TEST_F(Iterator_Test, iterator_operator_increment_value) {
	this->SetUp();

	++(*iter_1);

	EXPECT_EQ(*(*iter_1), Monom(2, 1, 1, 2));
}
TEST_F(Iterator_Test, iterator_operator_assign) {
	this->SetUp();

	++(*iter_1);
	(*iter_1) = (*iter_2);

	EXPECT_EQ(*(*iter_1), Monom(-1, 1, 1, 1));
};
TEST_F(Iterator_Test, iterator_operator_equal) {
	this->SetUp();

	++(*iter_1);
	(*iter_1) = (*iter_2);

	EXPECT_EQ((*iter_1) == (*iter_2), true);
};
TEST_F(Iterator_Test, iterator_operator_not_equal) {
	this->SetUp();

	EXPECT_EQ((*iter_1) != (*iter_2), true);
};
TEST_F(Iterator_Test, iterator_operator_dereference) {
	this->SetUp();

	EXPECT_EQ(*(*iter_1), Monom(1, 1, 1, 1));
};
TEST_F(Iterator_Test, iterator_change_pointer) {
	this->SetUp();

	++(*iter_1);
	(*iter_1).change(list_1->begin());

	EXPECT_EQ(*(*iter_1), Monom(1, 1, 1, 1));
};

