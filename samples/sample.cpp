#include <iostream>
#include "polinom.h"
using namespace std;

int main() {
	
	setlocale(2, "rus");
	int var = 0;
	string str_1, str_2;
	int c;
	Polynom result;
	cout << "Введите номер операции" << endl;
	cout << "1) Сложение" << endl << "2) Умножение" << endl << "3) Умножение на скаляр" << endl;
	cin >> var;
	if (var == 1) {
		cout << "Первый полином - ";
		cin >> str_1;
		cout << "Второй полином - ";
		cin >> str_2;

		Polynom polinom_1(sintax_analis(str_1));
		Polynom polinom_2(sintax_analis(str_2));

		result = polinom_1 + polinom_2;
	}
	else if(var == 2){
		cout << "Первый полином - ";
		cin >> str_1;
		cout << "Второй полином - ";
		cin >> str_2;

		Polynom polinom_1(sintax_analis(str_1));
		Polynom polinom_2(sintax_analis(str_2));

		result = polinom_1 * polinom_2;
	}
	else if (var == 3) {

		cout << "Полином - ";
		cin >> str_1;
		cout << "Константа  - ";
		cin >> c;

		Polynom polinom_1(sintax_analis(str_1));

		result = polinom_1 * c;
	}
	else {
		cout << "Неверный ввод" << endl;
		return 0;
	}

	cout << result.String() << endl;
	cout << "Значение полинома в точке (1, -5, 4) = " << result.value_at_point(1, -5, 4) << endl;
}
