# include <iostream>
# include <string.h>
#include <fstream>
#include <conio.h>
using namespace std;

//Задание 2.
//Создайте иерархию пользовательских классов - исключений.В ней должны быть классы 
// для разных ситуаций.В качестве предметной области используйте ваши
//практические и домашние задания.Например, должны
//присутствовать классы для обработки всевозможных
//математических ошибок, нехватки памяти, проблемам
//по работе с файлами и т.д.

class DateException : public exception
{
	char* message;
public:
	DateException(const char* msg) : exception(msg) {
		message = new char[strlen(msg) + 1];
		strcpy_s(message, strlen(msg) + 1, msg);
	}
	~DateException()
	{
		delete[] message;
	}
	char* GetMessage() { return message; }
};

class Date
{
	int day;
	int month;
	int year;
public:
	Date(int dayP, int monthP, int yearP);
	Date();
	Date(const Date& object);
	Date(Date&& object);
	void Put();
	int get_day() const;
	int get_month() const;
	int get_year() const;
	Date& operator=(const Date& object);
	Date& operator=(Date&& object);
	void show() const;
	bool IsCorrect() const;
};
Date::Date(int dayP, int monthP, int yearP)
	: day{ dayP }, month{ monthP }, year{ yearP }
{
	if (!IsCorrect())
	{
		throw "\nWrong date!\n";
	}
}
Date::Date() : Date(1, 1, 1900) {}
Date::Date(const Date& object)
{
	if (object.IsCorrect())
	{
		day = object.day;
		month = object.month;
		year = object.year;
	}
	else
		throw "\nWrong date!\n";
}
Date::Date(Date&& object)
{
	if (object.IsCorrect())
	{
		day = object.day;
		month = object.month;
		year = object.year;
	}
	else
		throw "\nWrong date!\n";
}
void Date::Put()
{
	int dayP, monthP, yearP;

	cout << "\nPlease enter birthday date: ";
	cin >> dayP;
	day = dayP;

	cout << "\nPlease enter birthday month: ";
	cin >> monthP;
	month = monthP;

	cout << "\nPlease enter birthday year: ";
	cin >> yearP;
	year = yearP;
}
int Date::get_day() const { return day; }
int Date::get_month() const { return month; }
int Date::get_year() const { return year; }
Date& Date::operator=(const Date& object)
{
	if (object.IsCorrect())
	{
		day = object.day;
		month = object.month;
		year = object.year;
	}
	else
		throw "\nWrong date!\n";
	return *this;
}
Date& Date::operator=(Date&& object)
{

	if (object.IsCorrect())
	{
		day = object.day;
		month = object.month;
		year = object.year;
	}
	else
		throw "\nWrong date!\n";

	return *this;
}
void Date::show() const
{
	cout << day << "." << month << "." << year;
}
bool Date::IsCorrect() const
{
	bool temp = 1;

	if (day < 1 || day > 31)
	{
		temp = 0;
		throw DateException("Wrong day!");
	}
	if (month < 1 || month > 12)
	{
		temp = 0;
		throw DateException("Wrong month!");
	}
	if (year < 1900 || year > 2100)
	{
		temp = 0;
		throw DateException("Wrong year!");
	}

	return temp;
}

class MemoryException : public exception
{
	char* message;
public:
	MemoryException(const char* msg):exception(msg)
	{
		message = new char[strlen(msg) + 1];
		strcpy_s(message, strlen(msg) + 1, msg);
	}
	char* GetMessage() { return message; }
	~MemoryException() { delete[] message; }
};

class Contact
{
	char* name;
	char* surname;
	Date birthday;
	char* email;
	char* phone;
	void setCharArray(char*& dest, const char* source)
	{
		if (source != nullptr)
		{
			int temp = strlen(source) + 1;

			dest = new char[temp];
			strcpy_s(dest, temp, source);
		}
		else if (source == nullptr)
			dest = nullptr;			
	}
	void remove()
	{
		if (name != nullptr)
		{
			delete[] name;
		}
		if (surname != nullptr)
		{
			delete[] surname;
		}
		birthday = { 1, 1, 1900 };
		if (email != nullptr)
		{
			delete[] email;
		}
		if (phone != nullptr)
		{
			delete[] phone;
		}
	}
public:
	Contact(const char* nameP, const char* surnameP, const Date birthdayP,
		const char* emailP, const char* phoneP);
	Contact();
	~Contact();
	Contact(const Contact& object);
	Contact(Contact&& object);
	void Put();
	char* get_name() const;
	char* get_surname() const;
	char* get_email() const;
	char* get_phone() const;
	Date get_birthday() const;
	void set_name(char* nameP);
	void set_surname(char* surnameP);
	void set_email(char* emailP);
	void set_phone(char* phoneP);
	void set_birthday(Date birthdayP);
	Contact& operator=(const Contact& object);
	Contact& operator=(Contact&& object);
	void show() const;
};

Contact::Contact(const char* nameP, const char* surnameP, const Date birthdayP,
	const char* emailP, const char* phoneP)
{
	setCharArray(name, nameP);
	setCharArray(surname, surnameP);
	setCharArray(email, emailP);
	setCharArray(phone, phoneP);
	birthday = birthdayP;
}
Contact::Contact() : Contact(nullptr, nullptr, { 1, 1, 1970 }, nullptr, nullptr) {}
Contact::Contact(const Contact& object)
{
	setCharArray(name, object.name);
	setCharArray(surname, object.surname);
	setCharArray(email, object.email);
	setCharArray(phone, object.phone);
	birthday = object.birthday;
}
Contact::Contact(Contact&& object)
{
	if (object.name)
	{
		setCharArray(name, object.name);
		object.name = nullptr;
	}

	if (object.surname)
	{
		setCharArray(surname, object.surname);
		object.surname = nullptr;
	}

	birthday = object.birthday;

	if (object.email)
	{
		setCharArray(email, object.email);
		object.email = nullptr;
	}

	if (object.phone)
	{
		setCharArray(phone, object.phone);
		object.phone = nullptr;
	}
}
Contact::~Contact()
{
	remove();
}
void Contact::Put()
{
	char temp[1024];

	cout << "\nEnter name:\n";
	cin >> temp;
	if (name)
		delete[] name;
	name = new char[strlen(temp) + 1];
	if (!name) {
		throw MemoryException("Error during memory allocation !!!");
	}
	strcpy_s(name, strlen(temp) + 1, temp);

	cout << "\nEnter surname:\n";
	cin >> temp;
	if (surname)
		delete[] surname;
	surname = new char[strlen(temp) + 1];
	if (!surname) {
		throw MemoryException("Error during memory allocation !!!");
	}
	strcpy_s(surname, strlen(temp) + 1, temp);

	birthday.Put();

	cout << "\nEnter email:\n";
	cin >> temp;
	if (email)
		delete[] email;
	email = new char[strlen(temp) + 1];
	if (!email) {
		throw MemoryException("Error during memory allocation !!!");
	}
	strcpy_s(email, strlen(temp) + 1, temp);

	cout << "\nEnter phone:\n";
	cin >> temp;
	if (phone)
		delete[] phone;
	phone = new char[strlen(temp) + 1];
	if (!phone) {
		throw MemoryException("Error during memory allocation !!!");
	}
	strcpy_s(phone, strlen(temp) + 1, temp);

}
char* Contact::get_name() const
{
	return name;
}
char* Contact::get_surname() const
{
	return surname;
}
char* Contact::get_email() const
{
	return email;
}
char* Contact::get_phone() const
{
	return phone;
}
Date Contact::get_birthday() const
{
	return birthday;
}
void Contact::set_name(char* nameP)
{
	if (nameP)
	{

		if (name != nullptr)
			delete[] name;

		setCharArray(name, nameP);
	}
}
void Contact::set_surname(char* surnameP)
{
	if (surnameP)
	{
		if (surname != nullptr)
			delete[] surname;

		setCharArray(surname, surnameP);
	}

}
void Contact::set_email(char* emailP)
{
	if (emailP)
	{
		if (email != nullptr)
			delete[] email;

		setCharArray(email, emailP);
	}
}
void Contact::set_phone(char* phoneP)
{
	if (phoneP)
	{
		if (phone != nullptr)
			delete[] phone;

		setCharArray(phone, phoneP);
	}
}
void Contact::set_birthday(Date birthdayP)
{
	birthday = birthdayP;
}
Contact& Contact::operator=(const Contact& object)
{
	if (this == &object)
		return *this;

	remove();

	setCharArray(name, object.name);
	setCharArray(surname, object.surname);
	birthday = object.birthday;
	setCharArray(email, object.email);
	setCharArray(phone, object.phone);

	return *this;
}
Contact& Contact::operator=(Contact&& object)
{
	if (strlen(name) != strlen(object.name))
		delete[] name;

	setCharArray(name, object.name);
	object.name = nullptr;

	if (strlen(surname) != strlen(object.surname))
		delete[] surname;

	setCharArray(surname, object.surname);
	object.surname = nullptr;

	birthday = object.birthday;

	if (strlen(email) != strlen(object.email))
		delete[] email;

	setCharArray(email, object.email);
	object.email = nullptr;

	if (strlen(phone) != strlen(object.phone))
		delete[] phone;

	setCharArray(phone, object.phone);
	object.phone = nullptr;

	return *this;
}
void Contact::show() const
{
	cout << "Name: " << name << endl;
	cout << "Surame: " << surname << endl;
	cout << "Birthday: ";
	birthday.show();
	cout << endl;
	cout << "Email: " << email << endl;
	cout << "Phone: " << phone << endl;
}

void resetCharArray(char*& dest, const char* source)
{
	if (source != nullptr)
	{
		if (dest != nullptr)
			delete[] dest;

		int strSize = strlen(source) + 1;
		dest = new char[strSize];
		strcpy_s(dest, strSize, source);
	}
}

class IndexException : public exception
{
	char* message;
public:
	IndexException(const char* msg) : exception(msg) {
		message = new char[strlen(msg) + 1];
		strcpy_s(message, strlen(msg) + 1, msg);
	}
	~IndexException()
	{
		delete[] message;
	}
	char* GetMessage() { return message; }
};
class FileException : public exception
{
	char* message;
public:
	FileException(const char* msg) : exception(msg) {
		message = new char[strlen(msg) + 1];
		strcpy_s(message, strlen(msg) + 1, msg);
	}
	~FileException()
	{
		delete[] message;
	}
	char* GetMessage() { return message; }
};


class Contacts
{
	enum { EMPTY = -1, FULL = 100 };
	Contact* st;
	int top;
public:
	Contacts();
	void Push(const Contact contactP);
	void Push();
	void Delete(int temp);
	Contact Pop();
	void Clear();
	bool IsEmpty();
	bool IsFull();
	int GetCount();
	void set_contact(const Contact& contactP, int idx);
	Contact get_contact(int temp);
	void SaveToFile(int i);
	void LoadFromFile();
	void Show() const;
	void SaveAllToFile();
};
Contacts::Contacts()
{
	top = EMPTY;
	st = nullptr;
}
void Contacts::Clear()
{
	top = EMPTY;
	if (st)
		delete[] st;
	st = nullptr;
}
bool Contacts::IsEmpty()
{
	return top == EMPTY;
}
bool Contacts::IsFull()
{
	return top == FULL;
}
int Contacts::GetCount()
{
	return top + 1;
}
void Contacts::Delete(int temp)
{
	if (!IsEmpty())
	{
		int idx = temp - 1;

		if (idx < 0 || idx > top)
			throw IndexException("Error!!! Out of array range!\n");

		Contact* tem = new Contact[top];

		for (size_t i = 0; i < top; i++)
		{
			if (i < idx)
				tem[i] = st[i];
			else
				tem[i] = st[i + 1];
		}

		top--;

		if (st != nullptr)
			delete[] st;
		st = new Contact[top + 1];
		for (size_t i = 0; i < top + 1; i++)
		{
			st[i] = tem[i];
		}

		delete[] tem;
	}
}
void Contacts::Push(const Contact contactP)
{
	Contact* temp = new Contact[top + 2];
	for (size_t i = 0; i < top + 1; i++)
		temp[i] = st[i];

	temp[++top] = contactP;
	if (st != nullptr)
		delete[] st;
	st = new Contact[top + 1];
	for (int i = 0; i <= top; i++)
		st[i] = temp[i];
	delete[] temp;
}
void Contacts::Push()
{
	Contact* temp = new Contact[top + 2];
	for (size_t i = 0; i < top + 1; i++)
		temp[i] = st[i];
	top++;
	if (st != nullptr)
		delete[] st;
	st = new Contact[top + 1];
	for (int i = 0; i <= top; i++)
		st[i] = temp[i];
	delete[] temp;
}
Contact Contacts::Pop()
{
	Contact t;

	if (!IsEmpty())
	{
		Contact* temp = new Contact[top];

		for (size_t i = 0; i < top; i++)
			temp[i] = st[i];

		t = st[top--];

		delete[] st;
		st = new Contact[top + 1];
		for (size_t i = 0; i <= top; i++)
			st[i] = temp[i];
		delete[] temp;
	}

	return t;
};
Contact Contacts::get_contact(int temp)
{
	Contact tem;

	if (!IsEmpty())
	{
		if (temp < 0 || temp > top)
		{
			throw IndexException("\n Wrong Element Position!\n");
		}
		else
		{
			tem = st[temp];
		}
	}

	return tem;
}
void Contacts::set_contact(const Contact& contactP, int idx)
{
	if (idx < 0 || idx > top + 1)
	{
		throw IndexException("Error!!! Out of array index!!!\n");
	}
	st[idx] = contactP;
}
void Contacts::SaveToFile(int i)
{
	if (i < 0 || i > top)
	{
		throw IndexException("\nIndex is wrong!\n");
	}
	int size; char* temp = nullptr;
	fstream f("Contacts.txt", ios::out | ios::binary | ios::app);
	if (!f)
	{
		throw FileException("\nFile is not opened for writing!\n");
	}

	size = strlen(st[i].get_name());
	f.write((char*)&size, sizeof(int));
	resetCharArray(temp, st[i].get_name());
	f.write((char*)temp, size * sizeof(char));

	size = strlen(st[i].get_surname());
	f.write((char*)&size, sizeof(int));
	resetCharArray(temp, st[i].get_surname());
	f.write((char*)temp, size * sizeof(char));

	size = st[i].get_birthday().get_day();
	f.write((char*)&size, sizeof(int));

	size = st[i].get_birthday().get_month();
	f.write((char*)&size, sizeof(int));

	size = st[i].get_birthday().get_year();
	f.write((char*)&size, sizeof(int));

	size = strlen(st[i].get_email());
	f.write((char*)&size, sizeof(int));
	resetCharArray(temp, st[i].get_email());
	f.write((char*)temp, size * sizeof(char));

	size = (int)strlen(st[i].get_phone());
	f.write((char*)&size, sizeof(int));
	resetCharArray(temp, st[i].get_phone());
	f.write((char*)temp, size * sizeof(char));

	f.close();
	delete[] temp;
}
void Contacts::LoadFromFile() {
	fstream f("Contacts.txt", ios::in | ios::binary);
	if (!f) {
		throw FileException("\nFile is not opened for reading!\n\n");
	}
	char* temp = nullptr;
	int size;
	int dayP, monthP, yearP;
	int i = 0;
	//В цикле зачитываем содержимое файла
	while (f.read((char*)&size, sizeof(int))) {
		Push();

		if (temp != nullptr)
			delete[] temp;

		temp = new char[size + 1];

		f.read((char*)temp, size * sizeof(char));
		temp[size] = '\0';
		st[i].set_name(temp);

		f.read((char*)&size, sizeof(int));

		if (temp != nullptr)
			delete[] temp;
		temp = new char[size + 1];

		f.read((char*)temp, size * sizeof(char));
		temp[size] = '\0';
		st[i].set_surname(temp);

		f.read((char*)&dayP, sizeof(int));
		f.read((char*)&monthP, sizeof(int));
		f.read((char*)&yearP, sizeof(int));
		st[i].set_birthday({ dayP, monthP, yearP });

		f.read((char*)&size, sizeof(int));
		if (temp != nullptr)
			delete[] temp;
		temp = new char[size + 1];

		f.read((char*)temp, size * sizeof(char));
		temp[size] = '\0';
		st[i].set_email(temp);

		f.read((char*)&size, sizeof(int));
		if (temp != nullptr)
			delete[] temp;

		temp = new char[size + 1];

		f.read((char*)temp, size * sizeof(char));
		temp[size] = '\0';
		st[i].set_phone(temp);

		i++;
	}

	delete[] temp;

}
void Contacts::Show() const
{
	cout << endl;
	for (size_t i = 0; i <= top; i++)
	{
		cout << "Contact " << i + 1 << " is:\n";
		st[i].show();
		cout << "\n";
	}
}
void Contacts::SaveAllToFile()
{
	for (int i = 0; i <= top; i++)
	{
		SaveToFile(i);
	}
}

int Contacts_Menu()
{
	int temp;
	cout << "\nPlease make your choice:\n";
	cout << " 1 - to see all contacts\n";
	cout << " 2 - to add new contact\n";
	cout << " 3 - to edit contact\n";
	cout << " 4 - to delete contact\n";
	cout << " 0 - to exit programm\n";
	cout << "\nYour choice is - ";
	cin >> temp;

	return temp;
}

int main() {

	try
	{
		Contacts M2;
		M2.LoadFromFile();

		int t;

		do {
			switch (Contacts_Menu()) {
			case 1:
				M2.Show();
				break;
			case 2:
			{Contact c1;
			c1.Put();
			M2.Push(c1);
			t = M2.GetCount();
			M2.SaveToFile(t - 1);
			cout << "New contact added!\n";
			break;
			}
			case 3:
			{
				cout << "\mPlese enter contact number to edit: ";
				cin >> t;

				cout << "\nEnter new contact details:\n";
				Contact c2;
				c2.Put();
				M2.set_contact(c2, t - 1);
				remove("Contacts.txt");
				M2.SaveAllToFile();
				break;
			}
			case 4:
			{
				cout << "\Plese enter contact number to delete: ";
				cin >> t;

				M2.Delete(t);
				remove("Contacts.txt");
				M2.SaveAllToFile();
				break;
			}
			case 0:
				cout << "Good Buy!\n";
				return 0;
			default:
				cout << "Wrong choice!\n";
			}
		} while (1);


	}
	catch (const char* su) {
		std::cout << "\n\nException!!! " << su << endl;
	}
	catch (DateException& de)
	{
		cout <<"\nDate Error! " << de.GetMessage() << "\n\n";
	}
	catch (MemoryException& me)
	{
		cout <<"\nMemory Error! " << me.GetMessage() << "\n\n";
	}
	catch (IndexException& ie)
	{
		cout << "\nIndex Error! " << ie.GetMessage() << "\n\n";
	}
	catch (exception& ex)
	{
		cout << "\n Class exception error! " << ex.what() << "\n\n";
	}
	catch (...)
	{
		cout << "\nSome error!\n\n";
	}
	return 0;
}