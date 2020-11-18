#include <stdio.h>
#include <iostream>
#include <iomanip>

#include <stdbool.h>
#include <stdlib.h>

using namespace std;

template<class T>
class MyArray
{
private:
	T* Array;
	int Size;
public:
	//«начение по умолчанию
	MyArray()
	{
		Array = nullptr;
		Size = 0;
	}
	//¬ыделение пам€ти под заданное число элементов
	MyArray(int Size)
	{
		this->Size = Size;
		Array = new T[this->Size];
		for (int i = 0; i < this->Size; Array[i] = NULL, i++);
	}

	~MyArray() { if (Array != nullptr)delete[] Array; } //очищение пам€ти от массива

	T& operator[](int index) { return Array[index]; } //перегрузка оператора индексировани€

	int getSize() { return Size; } //получение размера массива

	void Push(const T& obj)
	{
		T* newArray = new T[Size];
		for (int i = 0; i < Size; i++) newArray[i] = Array[i];

		++Size;
		Array = new T[Size];
		if (Size > 1)for (int i = 0; i < Size - 1; i++) Array[i] = newArray[i];
		Array[Size - 1] = obj;
		delete[] newArray;
	}

	void Pop(int index)
	{
		int i = 0;
		T* newArray = new T[Size - 1];
		for (i = 0; i < index; i++) newArray[i] = Array[i];
		for (i = index + 1; i < Size; i++) newArray[i - 1] = Array[i];
		--Size;

		Array = new T[Size];
		for (i = 0; i < Size; i++) Array[i] = newArray[i];
		delete[] newArray;
	}
};

template<class T> void Reverse(MyArray<T>&);

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "en_US.UTF-8");
	system("cls");

	MyArray<int> arr(5);

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	arr.Push(6);
	arr.Push(7);
	arr.Push(8);
	arr.Push(9);
	arr.Push(10);
	arr.Push(11);

	cout << "Size of array :  " << arr.getSize() << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "Array         : "; for (int i = 0; i < arr.getSize(); cout << arr[i] << " ", i++); cout << endl;

	Reverse(arr);
	cout << "Reversed array: ";  for (int i = 0; i < arr.getSize(); cout << arr[i] << " ", i++); cout << endl;
	cout << "------------------------------------------------------------------------" << endl << endl;

	for (int i = 0; i < 11; arr.Pop(0), i++);
	cout << "All elements have been poped from array" << endl;
	cout << "Size of array :  " << arr.getSize() << endl << endl;

	cout << " >>>>> TEST COMPLETED SUCCESSFULLY <<<<<" << endl;

	return 0;
}

template<class T> void Reverse(MyArray<T>& Array)
{
	int size = Array.getSize();
	for (int i = 0; i < size / 2; i++) swap(Array[i], Array[size - 1 - i]);
}