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
	Base** storage;// ���������
	Base** tmp_storage;//��������� ���������
	int size;//������ �������
public:
	//�����������
	MyStorage(int size) {
		this->storage = new Base * [size];
		for (int i = 0; i < size; i++) {
			this->storage[i] = NULL;
		}
		this->size = size;
	}

	// �������� ������ ���������
	int getCount() {
		return this->size;
	}

	// �������� ������ �� ��������� �������
	// ���� ��������� ������, ��� �������� �������,
	// �� ��������� ���������
	void setObject(int position, Base* object) {
		if (position < this->size) {
			this->storage[position] = object;
		}
		else {
			tmp_storage = new Base * [size];
			for (int i = 0; i < size; i++)//������������ ������ �� ��������� ������
				tmp_storage[i] = storage[i];
			delete[] storage;//��������� ������ ������, � c����� �� ���� ����� ����!!!
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

	// �������� ������ �� i-��� ������� (��� ��������)
	Base& getObject(int i) {
		return *(this->storage[i]);
	}

	// �������� ���������� ������. i - ������� ������
	Base& getPreviousObject(int i) {
		if (i > 0 && this->checkObject(i - 1)) {
			return *(this->storage[i - 1]);
		}
	}

	// �������� ����������� ������. i - ������� ������
	Base& getNextObject(int i) {
		if (i < this->size && this->checkObject(i + 1)) {
			return *(this->storage[i + 1]);
		}
	}

	// ��������� ������� ������� �� i-��� ������
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

	//�������� ������� � ��������� �������
	void deleteObject(int position) {

		tmp_storage = new Base * [size];
		for (int i = 0; i < size; i++)//������������ ������ �� ��������� ������
			tmp_storage[i] = storage[i];
		delete[] storage;//��������� ������ ������, � c����� �� ���� ����� ����!!!
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

	//������� �������� �� ����� ������� � �������� ����� showClass � ���� ��������
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

	//������� �������� ����� showClass � i-���� �������, ���� ������ ����������
	void callShowMethod(int i) {
		if (i < this->size && this->checkObject(i)) {
			return this->storage[i]->showClass();
		}
		else {
			cout << "NoObject" << "\n";
		}
	}

	//������� ���������� ���������� �������� � ���������
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

	// ������� ���������
	MyStorage myStorage(10);

	srand(time(NULL));

	//��������� ������ ��� ����� ���������� �� 100 ��������
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

	//��������� ����� ������ ����� ���������� �� 100 ��������
	int end_time_100 = clock();

	cout << "______________���� ��������� ������ 100 ��������______________" << "\n";


	myStorage.callShowMethod();


	cout << "______________���� ��������� ������ 100 ��������______________" << "\n";

	int search_time_100 = end_time_100 - start_time_100; // ������� �����
	cout << "����� ������: " << search_time_100 << "\n\n\n";


	//��������� ������ ��� ����� ���������� �� 1000 ��������
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

	//��������� ����� ������ ����� ���������� �� 1000 ��������
	int end_time_1000 = clock();

	cout << "______________���� ��������� ������ 1000 ��������______________" << "\n";


	myStorage.callShowMethod();


	cout << "______________���� ��������� ������ 1000 ��������______________" << "\n";

	int search_time_1000 = end_time_1000 - start_time_1000; // ������� �����
	cout << "����� ������: " << search_time_1000 << "\n\n\n";


	//��������� ������ ��� ����� ���������� �� 10000 ��������
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

	//��������� ����� ������ ����� ���������� �� 1000 ��������
	int end_time_10000 = clock();

	cout << "______________���� ��������� ������ 10000 ��������______________" << "\n";

	myStorage.callShowMethod();

	cout << "______________���� ��������� ������ 10000 ��������______________" << "\n";

	int search_time_10000 = end_time_10000 - start_time_10000; // ������� �����
	cout << "����� ������: " << search_time_10000 << "\n\n\n";

	return 0;
}