#include<iostream>
#include <ctime>

using namespace std;

class Base {
public:
	virtual void showClass() {
		cout << "Base" << "\n";
	};
};

class A : public Base {
public:
	virtual void showClass() {
		cout << "A" << "\n";
	}
};

class B : public Base {
public:
	virtual void showClass() {
		cout << "B" << "\n";
	}
};

class C : public Base {
public:
	virtual void showClass() {
		cout << "C" << "\n";
	}
};

class MyStorage {
private:
	Base** storage;// хранилище
	Base** tmp_storage;//временное хранилище
	int size;//размер массива
public:
	//конструктор
	MyStorage(int size) {
		this->storage = new Base*[size];
		for (int i = 0; i < size; i++) {
			this->storage[i] = NULL;
		}
		this->size = size;
	}

	// получить размер хранилища
	int getCount() {
		return this->size;
	}

	// добавить объект на указанную позицию
	// если хранилище меньше, чем заданна€ позици€,
	// то расшир€ем хранилище
	void setObject(int position, Base *object) {
		if (position < this->size) {
			this->storage[position] = object;
		}
		else {
			tmp_storage = new Base *[size];
			for (int i = 0; i < size; i++)//переписываем данные во временный массив
				tmp_storage[i] = storage[i];
			delete[] storage;//удал€етс€ только массив, а cсылка на него будет жить!!!
			int newSize = position + 1;
			storage = new Base * [newSize];
			for (int i = 0; i < newSize; i++) {
				if (i == position)
					this->storage[position] = object;
				else {
					if (i < size)
						storage[i] = tmp_storage[i];
					else
						storage[i] = NULL;
				}
			}
			this->size = newSize;
			delete[] tmp_storage;
		}
		
	}

	// получить объект на i-той позиции (без удалени€)
	Base& getObject(int i) {
		return *(this->storage[i]);
	}

	// провер€ет наличие объекта на i-той позици
	bool checkObject(int i) {
		bool result;
		if (this->storage[i] == NULL) {
			result = false;
		}
		else {
			result = true;
		}
		return result;
	}

	//удаление объекта с указанной позиции
	void deleteObject(int position) {

		tmp_storage = new Base * [size];
		for (int i = 0; i < size; i++)//переписываем данные во временный массив
			tmp_storage[i] = storage[i];
		delete[] storage;//удал€етс€ только массив, а cсылка на него будет жить!!!
		storage = new Base * [size];
		for (int i = 0; i < size; i++) {
			if (i == position)
				this->storage[position] = NULL;
			else {
				storage[i] = tmp_storage[i];
			}
		}
		delete[] tmp_storage;
	}
};

int main() {
	setlocale(LC_ALL, "RUS");

	// создаем хранилище
	MyStorage myStorage(10);

	return 0;
}