#include <stdio.h>
#include <iostream>
#include <iomanip>

#include <stdbool.h>
#include <stdlib.h>

#include <cstring>
#include <string>

using namespace std;


// ����� �����. ������� ������ ���������� � �����.
class Book
{
public:
	string ISBN;
	string Autor;
	string BookName;
	int PublishYear;
	int Price;

	//���������� �� ���������
	Book()
	{
		ISBN = "None";
		Autor = "None";
		BookName = "None";
		PublishYear = -1;
		Price = -1;
	}

	~Book(){}

	//����������� �����������
	Book(const Book& book)
	{
		ISBN = book.ISBN;
		Autor = book.Autor;
		BookName = book.BookName;
		PublishYear = book.PublishYear;
		Price = book.Price;
	}
	//���������� ������������
	Book& operator=(const Book& book)
	{
		ISBN = book.ISBN;
		Autor = book.Autor;
		BookName = book.BookName;
		PublishYear = book.PublishYear;
		Price = book.Price;

		return *this;
	}
	
	string getISBN() const { return ISBN; } //��������� ISBN

	//��������� ���� ���������� � �����
	void getInfo() const
	{
		cout << "Book info" << endl;
		cout << "--------------------------------" << endl;
		cout << "ISBN         | " << ISBN << endl;
		cout << "Author       | " << Autor << endl;
		cout << "Book name    | " << BookName << endl;
		cout << "Publish year | " << PublishYear << endl;
		cout << "Price        | " << Price << endl;
	}

	friend class Order;
};
//����� ���������� � ������ ( ���������� � ���������� )
class OrderInfo
{
public:
	int OrderNum;
	string Adress;
	string Date;
	string DoneDate;

	//�������� �� ���������
	OrderInfo()
	{
		OrderNum = -1;
		Adress = "None";
		Date = "None";
		DoneDate = "None";
	}
	~OrderInfo(){}

	//�����������
	OrderInfo(const OrderInfo& orderinfo)
	{
		OrderNum = orderinfo.OrderNum;
		Adress = orderinfo.Adress;
		Date = orderinfo.Date;
		DoneDate = orderinfo.DoneDate;
	}
	//���������� ������������
	OrderInfo& operator=(const OrderInfo& orderinfo)
	{
		OrderNum = orderinfo.OrderNum;
		Adress = orderinfo.Adress;
		Date = orderinfo.Date;
		DoneDate = orderinfo.DoneDate;

		return *this;
	}

	int getOrder() const { return OrderNum; } //��������� ������ ������

	//��������� ���� ���������� � ������
	void getInfo() const
	{
		cout << "Order info" << endl;
		cout << "--------------------------------" << endl;
		cout << "Order number |" << OrderNum << endl;
		cout << "Adress       |" << Adress << endl;
		cout << "Date         |" << Date << endl;
		cout << "Done date    |" << DoneDate << endl;
	}

	//������������� ������� ��� ������� � ����� ������
	friend class Order;
	friend OrderInfo CreateOrderInfo(void);
	friend void ShowAllOrderInfo(OrderInfo* OrderInfos, int SIZE_OI);

	friend void TEST(void);
};
//����� ������. ������ ������ �� ���������� � ��� �����
class Order
{
public:
	const Book* book; //������ �� ��������� �����
	const OrderInfo* orderinfo; //������ �� ���������� ����������

	//��������� ����������
	Order()
	{
		book = nullptr;
		orderinfo = nullptr;
	}

	//����������� ������ � ��������� ��������
	Order(Book& book, OrderInfo& orderinfo)
	{
		this->book = &book;
		this->orderinfo = &orderinfo;
	}

	//����������� ������
	Order(const Order& order)
	{
		book = new Book(*(order.book));
		orderinfo = new OrderInfo(*(order.orderinfo));
	}

	~Order() {}

	//���������� ������������
	Order& operator=(const Order& order)
	{
		book = new Book(*(order.book));
		orderinfo = new OrderInfo(*(order.orderinfo));
		return *this;
	}

	//��������� ���������� � ������
	void getInfo()
	{
		cout << "ISBN  |" << book->ISBN << endl;
		cout << "Order |" << orderinfo->OrderNum << endl;
	}

	void getBookInfo() { book->getInfo(); } //��������� ���� ���������� � ����� ������
	void getOrderInfo() { orderinfo->getInfo(); } //��������� ���� ���������� � ����������
};


int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	system("cls");

	Book book;
	book.ISBN = "457-9-821-28775";
	book.Autor = "Ryan Reed Michel";
	book.BookName = "How to design a brain";
	book.PublishYear = 2038;
	book.Price = 9999;

	OrderInfo orderinfo;
	orderinfo.OrderNum = 31547;
	orderinfo.Adress = "M31.D103.G8736.P4.S0";
	orderinfo.Date = "27.12.3079";
	orderinfo.DoneDate = "08.02.3080";

	Order order(book, orderinfo);

	cout << "=====  Book  ==========================" << endl << endl;
	cout << "ISBN: " << book.getISBN() << endl << endl;
	book.getInfo();
	cout << endl;

	cout << "=====  Order infromation  =============" << endl << endl;
	cout << "Order: " << orderinfo.getOrder() << endl << endl;
	orderinfo.getInfo();
	cout << endl;

	cout << "=====  Order  =========================" << endl << endl;
	order.getInfo(); cout << endl;
	order.getBookInfo();  cout << endl;
	order.getOrderInfo();  cout << endl;

	cout << endl << " >>>>> TEST COMPLETED SUCCESSFULLY <<<<<" << endl;

	return 0;
}