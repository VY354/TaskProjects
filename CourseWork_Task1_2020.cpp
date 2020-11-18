#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

class Point
{
private:
	float X;
	float Y;
public:
	//точка (0;0)
	Point()
	{
		X = 0;
		Y = 0;
	}
	//передача координат точеки
	Point(float x, float y)
	{
		X = x;
		Y = y;
	}

	//присваение значения одной точки другой
	Point& operator=(const Point& other)
	{
		X = other.X;
		Y = other.Y;
		return *this;
	}

	float getX() { return X; } //получение X
	float getY() { return Y; } //получение Y

	void setX(float x) { X = x; } //установка X
	void setY(float y) { Y = y; } //установка Y

	void setPoint(float x, float y) //установка точки
	{
		X = x;
		Y = y;
	}

	//дружественная функция для вывода полей
	friend ostream& operator<<(ostream& out, const Point& point);
};

class Rectangle
{
private:
	Point LeftBottom;
	Point RigthTop;
public:

	//по умолчанию все точки прямоугольника имеют координаты (0;0)
	Rectangle()
	{
		LeftBottom.setPoint(0, 0);
		RigthTop.setPoint(0, 0);
	}
	//передача точек, по которым строится прямоугольник
	Rectangle(const Point& LeftBottom, const Point& RigthTop)
	{
		this->LeftBottom = LeftBottom;
		this->RigthTop = RigthTop;
	}

	//копирование другово прямоугольник
	Rectangle(const Rectangle& other)
	{
		LeftBottom = other.LeftBottom;
		RigthTop = other.RigthTop;
	}

	//перегрузка оператора присвоения
	Rectangle& operator=(const Rectangle& other)
	{
		LeftBottom = other.LeftBottom;
		RigthTop = other.RigthTop;
		return *this;
	}

	~Rectangle() {}

	//сдвиг прямоугольника на указанные значения
	void Move(float Xoffest, float Yoffset)
	{
		LeftBottom.setX(LeftBottom.getX() + Xoffest); LeftBottom.setY(LeftBottom.getY() + Yoffset);
		RigthTop.setX(RigthTop.getX() + Xoffest); RigthTop.setY(RigthTop.getY() + Yoffset);
	}

	//сжатие прямоугольника
	void Squeeze(float SqueezeValue)
	{
		RigthTop.setX(RigthTop.getX() / SqueezeValue);
		RigthTop.setY(RigthTop.getY() / SqueezeValue);
	}

	//растяжение прямоугольника
	void Strech(float StrechValue)
	{
		RigthTop.setX(RigthTop.getX() * StrechValue);
		RigthTop.setY(RigthTop.getY() * StrechValue);
	}

	//метод для создания прямоугольника минимального размера, в который поместятся два заданных
	void CreateMinRect(Rectangle& Base1, Rectangle& Base2)
	{
		float maxWidth = max(max(Base1.getLength(), Base1.getWidth()), max(Base2.getLength(), Base2.getWidth()));

		float minLen = min(min(Base1.getLength(), Base1.getWidth()), min(Base2.getLength(), Base2.getWidth()));
		minLen += fabs(min(Base1.getLength(), Base1.getWidth()) - min(Base2.getLength(), Base2.getWidth()));

		LeftBottom.setPoint(0, 0);
		RigthTop.setPoint(minLen, maxWidth);
	}

	Point& getLeftBottom() { return LeftBottom; } //получение левой точки
	Point& getRigthTop() { return RigthTop; } //получение правой точки

	float getLength() { return fabs(RigthTop.getX() - LeftBottom.getX()); } //получение длины
	float getWidth() { return fabs(RigthTop.getY() - LeftBottom.getY()); } //получение ширины (высоты)
	float getArea() { return this->getLength() * this->getWidth(); } //получение площади
	float getPerimeter() { return 2 * (this->getLength() + this->getWidth()); } //получение периметра
};


//перегрузка оператора вывода для прямоугольника
ostream& operator<<(ostream& out, const  Point& point)
{
	cout << setw(5) << left << point.X << " ; " << setw(5) << left << point.Y;
	return out;
}

// ГЛАВНАЯ ФУНКЦИЯ
int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	system("cls");

	cout << endl;
	cout << " 2  .------.  3" << endl;
	cout << "    |      |    " << endl;
	cout << " 1  `------`  4" << endl;
	cout << endl << "--------------------------------------------" << endl;
	cout << endl;

	Point PL1(0, 0), PR1(13, 9);
	Point PL2(0, 0), PR2(10, 11);

	Rectangle R1(PL1, PR1);
	Rectangle R2(PL2, PR2);

	cout << " Original rectangles" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " R1 | " << "length: " << setw(10) << left << R1.getLength() << " | " << "Width: " << setw(10) << left << R1.getWidth() << " | " << "Perimeter: " << setw(10) << left << R1.getPerimeter() << " | " << "Area: " << setw(10) << left << setw(10) << left << R1.getArea() << endl;
	cout << " R2 | " << "length: " << setw(10) << left << R2.getLength() << " | " << "Width: " << setw(10) << left << R2.getWidth() << " | " << "Perimeter: " << setw(10) << left << R2.getPerimeter() << " | " << "Area: " << setw(10) << left << R2.getArea() << endl;

	cout << endl;
	cout << " R1, R2  Coordinates (X1 ; Y1 | X2 ; Y2)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " 1 | " << setw(5) << left << R1.getLeftBottom() << " | " << setw(5) << left << R2.getLeftBottom() << endl;
	cout << " 3 | " << setw(5) << left << R1.getRigthTop() << " | " << setw(5) << left << R2.getRigthTop() << endl;
	cout << endl;

	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	Rectangle R3;
	R3.CreateMinRect(R1, R2);

	cout << endl;
	cout << " R3 based on R1 and R2" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " R3 | " << "length: " << setw(10) << left << R3.getLength() << " | " << "Width: " << setw(10) << left << R3.getWidth() << " | " << "Perimeter: " << setw(10) << left << R3.getPerimeter() << " | " << "Area: " << setw(10) << left << R3.getArea() << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
	cout << " R3  Coordinates (X ; Y)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " 1 | " << setw(5) << left << R3.getLeftBottom() << endl;
	cout << " 3 | " << setw(5) << left << R3.getRigthTop() << endl;
	cout << endl;

	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	R3.Move(10, 10);

	cout << endl;
	cout << " R3 rectangle moved on (x;y) = (10;10) from original point" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " R3 | " << "length: " << setw(10) << left << R3.getLength() << " | " << "Width: " << setw(10) << left << R3.getWidth() << " | " << "Perimeter: " << setw(10) << left << R3.getPerimeter() << " | " << "Area: " << setw(10) << left << R3.getArea() << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
	cout << " R3  Coordinates (X ; Y)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " 1 | " << setw(5) << left << R3.getLeftBottom() << endl;
	cout << " 3 | " << setw(5) << left << R3.getRigthTop() << endl;
	cout << endl;

	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	R1.Squeeze(2);

	cout << endl;
	cout << " R1 rectangle squeezed by 2" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " R1 | " << "length: " << setw(10) << left << R1.getLength() << " | " << "Width: " << setw(10) << left << R1.getWidth() << " | " << "Perimeter: " << setw(10) << left << R1.getPerimeter() << " | " << "Area: " << setw(10) << left << R1.getArea() << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
	cout << " R1  Coordinates (X ; Y)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " 1 | " << setw(5) << left << R1.getLeftBottom() << endl;
	cout << " 3 | " << setw(5) << left << R1.getRigthTop() << endl;
	cout << endl;

	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	R2.Strech(2);

	cout << endl;
	cout << " R2 rectangle streched by 2" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " R2 | " << "length: " << setw(10) << left << R2.getLength() << " | " << "Width: " << setw(10) << left << R2.getWidth() << " | " << "Perimeter: " << setw(10) << left << R2.getPerimeter() << " | " << "Area: " << setw(10) << left << R2.getArea() << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
	cout << " R2  Coordinates (X ; Y)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	cout << " 1 | " << setw(5) << left << R2.getLeftBottom() << endl;
	cout << " 3 | " << setw(5) << left << R2.getRigthTop() << endl;
	cout << endl;

	cout << "-----------------------------------------------------------------------------------------------------------" << endl;

	cout << endl << " >>>>> TEST COMPLETED SUCCESSFULLY <<<<<" << endl;

	return 0;
}