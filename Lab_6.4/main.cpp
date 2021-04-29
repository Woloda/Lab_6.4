#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


class Row {    //клас "Row"(Рядок) для ініціалізацію елементів матриці
public:
	int* column;   //вказівник "column" вказує на масив(певна кількість стовпців матриці)

	void Set_column(int* value) { column = value; }  //Встановлення значення поля "column"
	int* Get_column() const { return column; }       //Отримання значення поля "column"

	Row(int kilkist_column = 1);    //конструктор ініціалізації класу "Row"
	int& operator [](int);        //індексація стовпця квадратної матриці
};

template <class T>	//T --- певний тип
class Matrix {      //клас "Matrix"(Матриця) для представлення матриці(двовимірного масиву) із NxN цілих чисел.
	int size;   //розмір квадратної матриці
	T* line;	//вказівник "line" вказує на масив(певна кількість рядків матриці)
public:
	Matrix();            //конструктор за умовчанням(без параметрів)
	Matrix(int);         //конструктор ініціалізації класу "Matrix"
	Matrix(int, T*);     //конструктор копіювання
	~Matrix();			 //деструктор(звільнення памяті виділеної для об'єкта-матриці)

	void Set_size(int value) { size = value; }	  //Встановлення значення поля "size"
	void Set_line(T* value) { line = value; }	  //Встановлення значення поля "line"

	int Get_size() const { return size; }         //Отримання значення поля "size"
	T* Get_line() const { return line; }        //Отримання значення поля "line"

	T& operator [](int line);      //індексація рядка квадратної матриці

	friend std::ostream& operator << <>(std::ostream&, Matrix&);   //вивід на екран(перевантаженння операції "виводу")
	friend std::istream& operator >> <>(std::istream&, Matrix&);	 //введення з клавіатури(перевантаженння операції "вводу")

	friend void operator - <>(Matrix&, Matrix&);    //віднімання матриць і отримання нової
	friend void operator + <>(Matrix&, Matrix&);    //додавання матриць і отримання нової
};

template <class T>		//T --- певний тип
Matrix<T>::Matrix() {   //конструктор за умовчанням(без параметрів)
	size = 1;

	line = new T[size];   //створення масива рядків квадратної матриці
	for (int i = 0; i < size; i++)
		line[i] = T(size);
}

//конструктор потрібен для створення рядків квадратної матриці
template <class T>		//T --- певний тип
Matrix<T>::Matrix(int kilkist_l_c) {   //конструктор ініціалізації класу "Matrix"
	size = (kilkist_l_c < 1) ? 1 : kilkist_l_c;    //перевірка значень(щоб користувач не ввів від'ємні значення)

	line = new T[size];   //створення масива рядків квадратної матриці
	for (int i = 0; i < size; i++)
		line[i] = T(size);
}

template <class T>		//T --- певний тип
Matrix<T>::Matrix(int values_s, T* value_l) {  //конструктор копіювання
	size = values_s;
	line = value_l;
}

template <class T>		//T --- певний тип
Matrix<T>::~Matrix() {  //деструктор(звільнення памяті виділеної для об'єкта-матриці)
	for (int i = 0; i < size; i++)
		if (line[i].column != nullptr)
			delete[] line[i].column;    //звільнення пам'яті виділеної для стовпців квадратної матриці

	if (line != nullptr)
		delete[] line;    //звільнення пам'яті виділеної для рядків квадратної матриці
}

template <class T>		//T --- певний тип
T& Matrix<T>::operator [](int line) {   //індексація рядка квадратної матриці
	return this->line[line];
}

template <class T>		//T --- певний тип
std::ostream& operator << (std::ostream& out, Matrix<T>& value) {    //вивід на екран(перевантаженння операції "виводу")
	out << "\nDisplay of matrix elements of size: " << value.size << "x" << value.size << "\n";
	for (int i = 0; i < value.size; i++) {
		for (int j = 0; j < value.size; j++)
			out << std::setw(5) << std::right << value[i][j];
		out << "\n";
	}
	return out;
}

template <class T>		//T --- певний тип
std::istream& operator >> (std::istream& in, Matrix<T>& value) {    //введення з клавіатури(перевантаженння операції "вводу")
	std::cout << "\nEntering the values of the elements of the matrix" << "\n";
	for (int i = 0; i < value.size; i++) {
		for (int j = 0; j < value.size; j++) {
			std::cout << "object " << "[" << i << "]" << "[" << j << "] : ";
			in >> value[i][j];
		}
	}
	return in;
}

//конструктор потрібен для створення стовпців в кожному рядку і ініціалізація елементів стовпця
Row::Row(int kilkist_column) {   //конструктор ініціалізації класу "Row"
	column = new int[kilkist_column];   //створення масива стовпців квадратної матриці

	for (int i = 0; i < kilkist_column; i++)
		column[i] = 0;
}

int& Row::Row::operator [](int column) {   //індексація стовпця квадратної матриці
	return this->column[column];
}

template <class T>		//T --- певний тип
void operator -(Matrix<T>& A, Matrix<T>& B) {    //віднімання матриць і отримання нової
	Matrix<T> C(A.size);
	if (A.size == B.size) {
		for (int i = 0; i < A.size; i++) {
			for (int j = 0; j < B.size; j++)
				C[i][j] = A[i][j] - B[i][j];
		}
		std::cout << "\n\nMatrix C:";
		std::cout << C;
	}
	else
		std::cout << "\n\nMatrices are not equal in size";
}

template <class T>		//T --- певний тип
void operator +(Matrix<T>& A, Matrix<T>& B) {    //додавання матриць і отримання нової
	Matrix<T> C(A.size);
	if (A.size == B.size) {
		for (int i = 0; i < A.size; i++) {
			for (int j = 0; j < B.size; j++)
				C[i][j] = A[i][j] + B[i][j];
		}
		std::cout << "\n\nMatrix C:";
		std::cout << C;
	}
	else
		std::cout << "\n\nMatrices are not equal in size";
}



typedef int Info;	//синонім "Info" - до типу "int"
struct Elem {	//клас черга
	Elem* link;		//вказівне поле на елемент
	Info info;		//інформаційне поле

	Elem(Elem* v_link = NULL, Info v_info = 0) {	//конструктор ініціалізації(параметри за умовчанням)
		link = v_link;
		info = v_info;
	}
};

template <class T>	//T --- певний тип
class Cherga {	//клас обгортка
	T* first;		//вказіник на початок черги
	T* last;		//вказіник на кінець черги
public:
	Cherga(T* v_first = NULL, T* v_last = NULL) {	//конструктор ініціалізації(параметри за умовчанням)
		first = v_first;
		last = v_last;
	}

	void Enqueue(Info);			//добавлення елемента до черги(створення черги)
	Info Dequeue();				//видалення елемента з черги(знищення черги)
	void Print();				//виводить дані про елементи черги;
};

template<class T>	//T --- певний тип
void Cherga<T>::Enqueue(Info value) {
	T* tmp = new T;
	tmp->info = value;
	tmp->link = NULL;
	if (last != NULL)
		last->link = tmp;
	last = tmp;
	if (first == NULL)
		first = tmp;
}

template<class T>	//T --- певний тип
Info Cherga<T>::Dequeue() {
	T* tmp = first->link;
	Info value = first->info;
	delete first;
	first = tmp;
	if (first == NULL)
		last = NULL;
	return value;
}

template<class T>	//T --- певний тип
void Cherga<T>::Print() {	//виводить дані про елементи черги;
	if (first == NULL)
		std::cout << "\n!!!The queue is empty!!!";

	std::cout << "\n";
	T* v_obj = first;
	while (v_obj != NULL) {
		std::cout << "  " << v_obj->info;
		v_obj = v_obj->link;
	}
}




int main(void) {
	srand((unsigned)time(NULL));
	std::cout << "\n\n//////////////////////////////////////////////////////////////////// sposob 1";

	int size_A, size_B;
	std::cout << "\n\nMatrix A:";
	std::cout << "\nEnter the size of the matrix: "; std::cin >> size_A;
	std::cout << "\n\nMatrix B:";
	std::cout << "\nEnter the size of the matrix: "; std::cin >> size_B;

	Matrix<Row> A(size_A), B(size_B);

	std::cout << "\n\nMatrix A:";
	std::cin >> A;
	std::cout << "\n\nMatrix B:";
	std::cin >> B;

	std::cout << "\n\nMatrix A:";
	std::cout << A;
	std::cout << "\n\nMatrix B:";
	std::cout << B;

	A - B;
	std::cout << "\n";
	system("pause");

	A + B;
	std::cout << "\n";
	system("pause");
	std::cout << "\n\n//////////////////////////////////////////////////////////////////// sposob 2";
	Cherga<Elem> a;

	int start = -20;
	int end = 20;

	for (int i(1); i <= 10; i++)
		a.Enqueue(start + rand() % int(end - start + 1));

	/*a.Enqueue(45);
	a.Enqueue(4);
	a.Enqueue(5);
	a.Enqueue(123);*/

	std::cout << "\n\nData output: "; 
	a.Print();	//вивід даних
	std::cout << "\n";
	system("pause");

	for (int i(1); i <= 4; i++)
		std::cout << "\n\nDelete an item "<< i <<": " << a.Dequeue();

	std::cout << "\n";
	system("pause");
	return 0;
}