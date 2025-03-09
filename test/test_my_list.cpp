#include "polinom.h"
#include <gtest.h>

template<typename Item>
class My_List_Test : public ::testing::Test {
protected:
	void SetUp() {
		list_1 = new my_list<Item>;
		list_2 = new my_list<Item>;
		list_3 = new my_list<Item>;

		(*list_1).push_back(1);
		(*list_1).push_back(2);
		(*list_1).push_back(3);
		//[1]->[2]->[3]

		(*list_2).push_back(4);
		(*list_2).push_back(5);
		(*list_2).push_back(6);
		//[4]->[5]->[6]

		(*list_3).push_back(1);
		(*list_3).push_back(2);
		(*list_3).push_back(3);
		//[1]->[2]->[3]
	}
	void SetUpNewList() {
		list_1 = new my_list<Item>;

		(*list_1).push_back(1);
		(*list_1).push_back(2);
		// [1]->[2]
	}
	void TearDown() {
		delete list_1;
		delete list_2;
		delete list_3;
	}
	void TearDownNewList() {
		delete list_1;
	}
	my_list<Item>* list_1;
	my_list<Item>* list_2;
	my_list<Item>* list_3;
};

TYPED_TEST_CASE_P(My_List_Test);

TYPED_TEST_P(My_List_Test, throw_can_create_list) {
	ASSERT_NO_THROW(this->SetUpNewList());
};
TYPED_TEST_P(My_List_Test, list_cirrect_get_size) {
	this->SetUpNewList();

	EXPECT_EQ((*this->list_1).get_size(), 2);
}; 
TYPED_TEST_P(My_List_Test, list_operator_bracket) {
	this->SetUpNewList();

	EXPECT_EQ((*this->list_1)[1], 2);
};
TYPED_TEST_P(My_List_Test, list_pop_back_correct_size) {
	this->SetUpNewList();

	(*this->list_1).pop_back();
	//[1]
	EXPECT_EQ((*this->list_1).get_size(), 1);
};
TYPED_TEST_P(My_List_Test, throw_list_pop_back_ancorrect_size) {
	this->SetUpNewList();

	(*this->list_1).pop_back();
	(*this->list_1).pop_back();

	ASSERT_ANY_THROW((*this->list_1).pop_back());
};
TYPED_TEST_P(My_List_Test, list_pop_front_correct_size) {
	this->SetUpNewList();

	(*this->list_1).pop_front();
	// [2]
	EXPECT_EQ((*this->list_1).get_size(), 1);
};
TYPED_TEST_P(My_List_Test, throw_list_pop_front_ancorrect_size) {
	this->SetUpNewList();

	(*this->list_1).pop_front();
	(*this->list_1).pop_front();

	ASSERT_ANY_THROW((*this->list_1).pop_front());
};
TYPED_TEST_P(My_List_Test, list_push_back_correct_size) {
	this->SetUpNewList();

	(*this->list_1).push_back(3);
	//[1]->[2]->[3]
	EXPECT_EQ((*this->list_1).get_size(), 3);
};
TYPED_TEST_P(My_List_Test, list_push_front_correct_size) {
	this->SetUpNewList();

	(*this->list_1).push_front(3);
	//[3]->[1]->[2]
	EXPECT_EQ((*this->list_1).get_size(), 3);
};
TYPED_TEST_P(My_List_Test, list_operator_assign) {
	this->SetUp();

	(*this->list_1) = (*this->list_2);

	EXPECT_EQ((*this->list_1) == (*this->list_2), 1);
};
TYPED_TEST_P(My_List_Test, list_operator_equal) {
	this->SetUp();

	EXPECT_EQ((*this->list_1) == (*this->list_3), 1);
};
TYPED_TEST_P(My_List_Test, list_operator_not_equal) {
	this->SetUp();

	EXPECT_EQ((*this->list_1) != (*this->list_2), 1);
};
TYPED_TEST_P(My_List_Test, list_clear) {
	this->SetUp();

	(*this->list_1).clear();

	EXPECT_EQ((*this->list_1).get_size(), 0);
};

REGISTER_TYPED_TEST_CASE_P(My_List_Test, throw_can_create_list, list_cirrect_get_size, list_operator_bracket, list_pop_back_correct_size, throw_list_pop_back_ancorrect_size,
	list_pop_front_correct_size, throw_list_pop_front_ancorrect_size, list_push_back_correct_size, list_push_front_correct_size, list_operator_assign, list_operator_equal, list_operator_not_equal, list_clear);
typedef ::testing::Types<int, long long, char, long> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, My_List_Test, ContainerTypes);
