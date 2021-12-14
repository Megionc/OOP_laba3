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
		this->storage = new Base * [size];
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
	// если хранилище меньше, чем заданная позиция,
	// то расширяем хранилище
	void setObject(int position, Base* object) {
		if (position < this->size) {
			this->storage[position] = object;
		}
		else {
			tmp_storage = new Base * [size];
			for (int i = 0; i < size; i++)//переписываем данные во временный массив
				tmp_storage[i] = storage[i];
			delete[] storage;//удаляется только массив, а cсылка на него будет жить!!!
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

	// получить объект на i-той позиции (без удаления)
	Base& getObject(int i) {
		return *(this->storage[i]);
	}

	// получить предыдущий объект. i - текуший объект
	Base& getPreviousObject(int i) {
		if (i > 0 && this->checkObject(i - 1)) {
			return *(this->storage[i - 1]);
		}
	}

	// получить последующий объект. i - текуший объект
	Base& getNextObject(int i) {
		if (i < this->size && this->checkObject(i + 1)) {
			return *(this->storage[i + 1]);
		}
	}

	// проверяет наличие объекта на i-той позици
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
		delete[] storage;//удаляется только массив, а cсылка на него будет жить!!!
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

	//функция проходит по всему массиву и вызывает метод showClass у всех объектов
	void callShowMethod() {
		for (int i = 0; i < size; i++) {
			if (this->checkObject(i)) {
				this->storage[i]->showClass();
			}
			else {
				cout << "NoObject" << "\n";
			}
		}
	}

	//функция вызывает метод showClass у i-того объекта, если объект существует
	void callShowMethod(int i) {
		if (i < this->size && this->checkObject(i)) {
			return this->storage[i]->showClass();
		}
		else {
			cout << "NoObject" << "\n";
		}
	}

	//функция возвращает количество объектов в хранилище
	int getCountObject() {
		int counter = 0;
		for (int i = 0; i < this->size; i++) {
			if (this->checkObject(i)) {
				counter = counter + 1;
			}
		}
		return counter;
	}
};

int main() {
	setlocale(LC_ALL, "RUS");

	// создаем хранилище
	MyStorage myStorage(10);

	srand(time(NULL));

	//запускаем таймер для цикла состоящего из 100 итераций
	int start_time_100 = clock();

	for (int i = 0; i < 100; i++) {
		int randAction = rand() % 3;

		switch (randAction) {
		case 0: {
			int position = rand() % 101;
			int object = rand() % 3;
			switch (object) {
			case 0: {
				myStorage.setObject(position, new A());
				break;
			}
			case 1: {
				myStorage.setObject(position, new B());
				break;
			}
			case 2: {
				myStorage.setObject(position, new C());
				break;
			}
			}
		}
		case 1: {
			int positionDelete = rand() % 100;
			myStorage.deleteObject(positionDelete);
			break;
		}
		case 2: {
			int positionShow = rand() % 100;
			myStorage.callShowMethod(positionShow);
			break;
		}
		}

	}

	//фиксируем конец работы цикла состоящего из 100 итераций
	int end_time_100 = clock();

	cout << "______________ниже результат первых 100 итераций______________" << "\n";


	myStorage.callShowMethod();


	cout << "______________выше результат первых 100 итераций______________" << "\n";

	int search_time_100 = end_time_100 - start_time_100; // искомое время
	cout << "Время работы: " << search_time_100 << "\n\n\n";


	//запускаем таймер для цикла состоящего из 1000 итераций
	int start_time_1000 = clock();

	for (int i = 0; i < 1000; i++) {
		int randAction = rand() % 3;

		switch (randAction) {
		case 0: {
			int position = rand() % 101;
			int object = rand() % 3;
			switch (object) {
			case 0: {
				myStorage.setObject(position, new A());
				break;
			}
			case 1: {
				myStorage.setObject(position, new B());
				break;
			}
			case 2: {
				myStorage.setObject(position, new C());
				break;
			}
			}
		}
		case 1: {
			int positionDelete = rand() % 100;
			myStorage.deleteObject(positionDelete);
			break;
		}
		case 2: {
			int positionShow = rand() % 100;
			myStorage.callShowMethod(positionShow);
			break;
		}
		}

	}

	//фиксируем конец работы цикла состоящего из 1000 итераций
	int end_time_1000 = clock();

	cout << "______________ниже результат первых 1000 итераций______________" << "\n";


	myStorage.callShowMethod();


	cout << "______________выше результат первых 1000 итераций______________" << "\n";

	int search_time_1000 = end_time_1000 - start_time_1000; // искомое время
	cout << "Время работы: " << search_time_1000 << "\n\n\n";


	//запускаем таймер для цикла состоящего из 10000 итераций
	int start_time_10000 = clock();

	for (int i = 0; i < 10000; i++) {
		int randAction = rand() % 3;

		switch (randAction) {
		case 0: {
			int position = rand() % 101;
			int object = rand() % 3;
			switch (object) {
			case 0: {
				myStorage.setObject(position, new A());
				break;
			}
			case 1: {
				myStorage.setObject(position, new B());
				break;
			}
			case 2: {
				myStorage.setObject(position, new C());
				break;
			}
			}
		}
		case 1: {
			int positionDelete = rand() % 100;
			myStorage.deleteObject(positionDelete);
			break;
		}
		case 2: {
			int positionShow = rand() % 100;
			myStorage.callShowMethod(positionShow);
			break;
		}
		}

	}

	//фиксируем конец работы цикла состоящего из 1000 итераций
	int end_time_10000 = clock();

	cout << "______________ниже результат первых 10000 итераций______________" << "\n";

	myStorage.callShowMethod();

	cout << "______________выше результат первых 10000 итераций______________" << "\n";

	int search_time_10000 = end_time_10000 - start_time_10000; // искомое время
	cout << "Время работы: " << search_time_10000 << "\n\n\n";

	return 0;
}