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
		this->storage = new Base*[size];
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
	void setObject(int position, Base *object) {
		if (position < this->size) {
			this->storage[position] = object;
		}
		else {
			tmp_storage = new Base *[size];
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
};

int main() {
	setlocale(LC_ALL, "RUS");

	// ������� ���������
	MyStorage myStorage(10);

	return 0;
}