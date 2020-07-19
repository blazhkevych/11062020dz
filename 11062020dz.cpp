/*
Задание.
Создайте программу, имитирующую многоквартирный дом.
Необходимо иметь классы “Человек”, “Квартира”, “Дом”.+
*******************classes “Person”, “Apartment”, “House”
Класс “Квартира” содержит динамический массив объектов класса “Человек”.+
Класс “Дом” содержит массив объектов класса “Квартира”.+
Каждый из классов содержит переменные-члены и функции-члены, которые необходимы для предметной области класса.
Обращаем ваше внимание, что память под строковые значения выделяется динамически. Например, для ФИО в классе “Человек”.
Не забывайте обеспечить классы различными конструкторами (конструктор копирования обязателен), деструкторами.
В main протестировать работу полученного набора классов.
*/
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
class Person // Человек
{
	char* FIO;
	int Age;
	char* Phone;
public:
	Person(); // конструктор без параметров
	Person(const char* f, int ag, const char* phn); // конструктор с параметрами
	Person(const Person& other); // конструктор копирования 
	inline ~Person(); // деструктор
	// геттеры
	inline const char* GetFIO() { return FIO; }
	inline int GetAge() { return Age; }
	inline const char* GetPhone() { return Phone; }
	//сеттеры
	inline void SetFIO(const char* f) { delete[] FIO; FIO = _strdup(f); }
	inline void SetAge(int a) { Age = a; };
	inline void SetPhone(const char* phn) { delete[] Phone; Phone = _strdup(phn); }
	void PrintMan(); // вывод Person
	Person& operator = (const Person& other);
};
Person::Person()
{
	FIO = nullptr;
	Age = 0;
	Phone = nullptr;
}
Person::Person(const char* f, int ag, const char* phn)
{
	if (f && strlen(f)) { FIO = new char[strlen(f) + 1]; strcpy_s(FIO, strlen(f) + 1, f); }
	else { FIO = NULL; }

	Age = ag;

	if (phn && strlen(phn)) { Phone = new char[strlen(phn) + 1]; strcpy_s(Phone, strlen(phn) + 1, phn); }
	else { Phone = NULL; }
}
Person::Person(const Person& other)
{
	FIO = _strdup(other.FIO);
	Age = other.Age;
	Phone = _strdup(other.Phone);
}
Person::~Person()
{
	delete[]FIO;
	delete[]Phone;
}
void Person::PrintMan()
{
	cout << "Фамилия, имя, отчество : " << FIO << '\n';
	cout << "Возраст : " << Age << '\n';
	cout << "Моб. телефон : " << Phone << '\n';
	cout << "**************************************************************************" << '\n';
}
Person& Person::operator=(const Person& right)
{
	if (&right != this) {
		delete[]FIO;
		FIO = _strdup(right.FIO);

		Age = right.Age;

		delete[]Phone;
		Phone = _strdup(right.Phone);
	}
	return *this;
}

class Apartment // Квартира
{
	int CountPersons; // кол-во людей в квартире
	Person* Persons; // Класс “Квартира” содержит динамический массив объектов класса “Человек”.
public:
	int NumberOfApartment; // номер квартиры
	Apartment() : NumberOfApartment(0), Persons(0), CountPersons(0) {}
	Apartment(int number) : NumberOfApartment(number), Persons(0), CountPersons(0) {} // квартира с номером
	Apartment(int number, const Person& pers) : NumberOfApartment(number) { Push(pers); } // номер + человек
	Apartment(const Apartment& A); // конструктор копии
	//геттеры	
	inline int GetCountPersons() { return CountPersons; }
	//сеттеры	
	inline void SetCountPersons(int CntPrsns) { CountPersons = CntPrsns; };
	~Apartment() { Clear(); }
	void Clear();
	void Push(const Person& pers);
	//void Push(); //ручками (по заданию не нужно ?!?!?!?)
	void PrintApartment();
	Apartment& operator = (const Apartment& right);
};
Apartment::Apartment(const Apartment& A)
{
	NumberOfApartment = A.NumberOfApartment;
	CountPersons = A.CountPersons;
	Persons = new Person[A.CountPersons];
	for (size_t i = 0; i < CountPersons; i++)
		Persons[i] = A.Persons[i];
}
void Apartment::Clear()
{
	delete[]Persons;
	Persons = nullptr; // ???
	CountPersons = 0; /// ???
}
void Apartment::Push(const Person& pers)
{
	Person* newMassOfPersons = new Person[CountPersons + 1];
	for (int i = 0; i < CountPersons; i++)
		newMassOfPersons[i] = Persons[i];
	delete[]Persons;
	Persons = newMassOfPersons;
	Persons[CountPersons] = pers;
	CountPersons++;
}
//void Apartment::Push()
//{
//	cout << "Введите данные о жильце:" << endl;
//	cout << "Введите фамилию, имя, отчество: ";
//	char buf_FIO[50];
//	cin.getline(buf_FIO, 50);
//	cout << "\nВозраст: ";
//	int buf_Age;
//	cin >> buf_Age;
//	cout << "\nМобильный телефон: ";
//	char buf_phone[50];
//	cin.getline(buf_phone, 50);
//	Push(Person(buf_FIO, buf_Age, buf_phone));
//}
void Apartment::PrintApartment()
{
	cout << "Квартира номер : " << NumberOfApartment << endl;
	cout << "Кол-во жильцов в квартире : " << CountPersons << endl;
	for (int i = 0; i < CountPersons; i++) {
		Persons[i].PrintMan();
	}
}
Apartment& Apartment::operator=(const Apartment& right)
{
	if (&right != this) {
		delete[]Persons;
		Apartment(*right); // або 
		/*
		NumberOfApartment = right.NumberOfApartment;
	CountPersons = right.CountPersons;
	Persons = new Person[A.CountPersons];
	for (size_t i = 0; i < CountPersons; i++)
		Persons[i] = right.Persons[i];
		*/
	}
	return *this;
}

class House // Дом
{
	char* Street;
	char* HouseNumber; // char * для номеров типа 99/13
	int CountApartments; // кол-во квартир
	Apartment* Apartments; // Класс “Дом” содержит массив объектов класса “Квартира”.
public:
	House() :Street(0), HouseNumber(0), CountApartments(0), Apartments(0) {};
	House(const char* Strt, const char* HsNmbr) :Street(_strdup(Strt)), HouseNumber(_strdup(HsNmbr)), CountApartments(0), Apartments(0) {};
	House(const char* Strt, const char* HsNmbr, const Apartment& apart) :Street(_strdup(Strt)), HouseNumber(_strdup(HsNmbr)), CountApartments(0) { Push(apart); };
	House(const House& apart); // конструктор копии
	//геттеры
	inline const char* GetStreet() { return Street; }
	inline const char* GetHouseNumber() { return HouseNumber; }
	inline int GetCountApartments() { return CountApartments; }
	//сеттеры
	inline void SetStreet(const char* f) { delete[] Street; Street = _strdup(f); }
	inline void SetHouseNumber(const char* HsNmbr) { delete[] HouseNumber; HouseNumber = _strdup(HsNmbr); }
	inline void SetCountApartments(int CntAprtmnts) { CountApartments = CntAprtmnts; };
	~House() { Clear(); }
	void Clear();
	void Push(const Apartment& apart);
	void PrintHouse();
	House& operator = (const House& right);
};
House::House(const House& apart)
{
	Street = _strdup(apart.Street);
	HouseNumber = _strdup(apart.HouseNumber);
	CountApartments = apart.CountApartments;
	Apartments = new Apartment[apart.CountApartments];
	for (size_t i = 0; i < CountApartments; i++)
		Apartments[i] = apart.Apartments[i];
}
void House::Clear()
{
	delete[]Street;
	delete[]HouseNumber;
	CountApartments = 0; /// ???
	delete[]Apartments;
	Apartments = nullptr; // ???
}
void House::Push(const Apartment& apart)
{
	Apartment* newMassOfApartments = new Apartment[CountApartments + 1];
	for (int i = 0; i < CountApartments; i++)
		newMassOfApartments[i] = Apartments[i];
	delete[]Apartments;
	Apartments = newMassOfApartments;
	Apartments[CountApartments] = apart;
	CountApartments++;
}
void House::PrintHouse()
{
	cout << "Улица : " << Street << endl;
	cout << "Дом номер: " << HouseNumber << endl;
	cout << "Кол-во квартир в доме: " << CountApartments << endl;
	for (int i = 0; i < CountApartments; i++) {
		Apartments[i].PrintApartment();
	}
}
House& House::operator=(const House& right)
{
	if (&right != this) {
		delete[]Apartments;
		Apartment(*right); // або 
		/*
		NumberOfApartment = right.NumberOfApartment;
	CountPersons = right.CountPersons;
	Persons = new Person[A.CountPersons];
	for (size_t i = 0; i < CountPersons; i++)
		Persons[i] = right.Persons[i];
		*/
	}
	return *this;
}

//МЕНЮ
void print_menu() {
	system("cls"); // очищаем экран
	cout << "Имитация многоквартирного дома !" << endl;
	cout << "1. Построить Дом" << endl;
	cout << "2. Создать в доме квартиру" << endl;
	cout << "3. Сотворить Жильца" << endl;
	cout << "4. Показать результаты фантазии" << endl;
	cout << "5. Вернуться в реальный мир" << endl;
	cout << "->";
}
int get_variant(int count) {
	int variant;
	string s; // строка для считывания введённых данных
	getline(cin, s); // считываем строку
	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf_s(s.c_str(), "%d", &variant) != 1 || variant < 1 || variant > count) {
		cout << "Неверный ввод. Попробуй еще раз: "; // выводим сообщение об ошибке
		getline(cin, s); // считываем строку повторно
	}
	return variant;
}
int main()
{
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	SetConsoleCP(1251); //встановлює потрібну кодову таблицю, на потік введення
	SetConsoleOutputCP(1251); //встановлює потрібну кодову таблицю, на потік виводу.	
	/*cout << "Класс Человек : " << '\n';
	Person a("Елена Анатольевна Пупкина", 23, "+380931234567");
	a.PrintMan();
	Person b("Виктор Александрович Уханов", 32, "+380");
	b.PrintMan();
	cout << "Класс Квартира : " << '\n';
	Apartment c(3, a);
	c.PrintApartment();
	cout << "Класс Дом : " << '\n';
	House d("Хлебная", "99/5", c);
	d.PrintHouse();*/

	int variant; // выбранный пункт меню
	do {
		print_menu(); // выводим меню на экран
		variant = get_variant(5); // получаем номер выбранного пункта меню
		House a; // House a[sizeof(House)];
		Apartment b;
		Person c;
		switch (variant) {
		case 1:
			cout << "Введите данные о Доме " << '\n';
			char buf_Street[50];
			cout << "Улица : " << '\n';
			cin.getline(buf_Street, 50);
			a.SetStreet(buf_Street);

			char buf_HouseNumber[50];
			cout << "Номер дома : " << '\n';
			cin.getline(buf_HouseNumber, 50);
			a.SetHouseNumber(buf_HouseNumber);

			int buf_CountApartments;
			cout << "Кол-во квартир : " << '\n';
			cin >> buf_CountApartments;
			a.SetCountApartments(buf_CountApartments);
			break;
		case 2:
			cout << "Введите данные о Квартире " << '\n';
			cout << "Кол-во людей в квартире : " << '\n';
			int buf_CountPersons; // вылетает
			cin >> buf_CountPersons;
			b.SetCountPersons(buf_CountPersons);
			break;
		case 3:
			char buf_FIO[50];
			int buf_Age;
			char buf_Phone[50];
			cout << "Введите данные о Жильце " << '\n';
			cout << "Фамилия, имя, отчество : " << '\n';
			cin.getline(buf_FIO, 50);
			cout << "Возраст : " << '\n';
			cin >> buf_Age;
			cin.get();
			cout << "Моб. телефон : " << '\n';
			cin.getline(buf_Phone, 50);
			break;
		case 4:
			a.PrintHouse();
			break;
		}

		if (variant != 5)
			system("pause"); // задерживаем выполнение, чтобы пользователь мог увидеть результат выполнения выбранного пункта
	} while (variant != 5);

	return 0;
}
