#include <iostream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

#pragma region Special_Abilities
void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tTemplates" << endl;
}
void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Press enter to continue: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion

class Array {
private: 

	int* array;
	int size;

	template <typename T1, typename T2>
	void CopyArray(T1*& oldArr, const T2* newArr, const int sizeP) {

		if (oldArr != nullptr)delete[] oldArr;

		if (sizeP > 0) {

			oldArr = new T1[sizeP];
			for (size_t i{ 0 }; i != sizeP; i++) { oldArr[i] = newArr[i]; }

		}
		else oldArr = nullptr;

	}

public: 

	Array(const int* arrayP, const int size) {
		CopyArray(array, arrayP, size);
	}

	Array(const int* arrayP) :Array(arrayP, 0) {}

	Array() :Array(0, 0){}

	~Array() { delete[] array; }

	int GetSize() const { return size; }

	Array& operator +=(int num) {

		int* tempArray = new int[size + 1];

		for (size_t i = 0; i < size; ++i) {
			tempArray[i] = array[i];
		}
		tempArray[size] = num;

		delete[] array;
		array = tempArray;

		++size;

		return *this;
	}

	Array& operator -=(int num) {

		assert(size > 0 and "Array empty!");

		vector<int> tempArray;
		for (size_t i{ 0 }; i != size; i++) {

			if (array[i] != num)tempArray.push_back(array[i]);

		}

		if (tempArray.size() != 0)CopyArray(array, tempArray.data(), tempArray.size());
		else array = nullptr;

		size = tempArray.size();

		return *this;

	}

	friend ostream& operator <<(ostream& out, const Array& objectArray);

	int& operator [](int index) {
		return array[index];
	}

	int operator [](int index) const {
		return array[index];
	}

	template <typename T>
	friend T FindMinimalNum(const Array& objectArray);

	template <typename T>
	friend T FindMaximalNum(const Array& objectArray);

	friend void SortArray(Array& objectArray, int first, int last);

	template <typename T>
	friend int FindIndexNum(Array& objectArray, int first, int last, T num);
};

ostream& operator <<(ostream& out, const Array& objectArray) {

	assert(objectArray.size > 0 and "Array empty!");

	for (size_t i = 0; i != objectArray.size; i++)out << objectArray[i] << " | ";
	return out;
}

template <typename T>
T FindMinimalNum(const Array& objectArray) {

	assert(objectArray.size > 0 and "Array empty!");

	auto min = objectArray[0];

	for (size_t i = 1; i != objectArray.size; i++) {

		if (min > objectArray[i])min = objectArray[i];

	}

	return min;

}

template <typename T>
T FindMaximalNum(const Array& objectArray) {

	assert(objectArray.size > 0 and "Array empty!");

	auto max = objectArray[0];

	for (size_t i = 1; i != objectArray.size; i++) {

		if (max < objectArray[i])max = objectArray[i];

	}

	return max;

}

void SortArray(Array& objectArray,int first, int last) {

	assert(objectArray.size > 0 and "Array empty!");

	if (first < last) {

		int left = first, right = last, midle = objectArray.array[(first + last) / 2];

		do {

			while (objectArray.array[left] < midle)++left;
			while (objectArray.array[right] > midle)--right;

			if (left <= right) {
				swap(objectArray.array[left], objectArray.array[right]);
				left++;
				right--;
			}

		} while (left < right);
		SortArray(objectArray, first, right);
		SortArray(objectArray, left, last);
	}

}

template <typename T>
int FindIndexNum(Array& objectArray, int left, int right, T num) {

	assert(objectArray.size > 0 and "Array empty!");

	while (true) {

		int midle = (left + right) / 2;

		if (num < objectArray.array[midle])right = midle - 1;
		else if (num > objectArray.array[midle])left = midle + 1;
		else return midle;

		if (left > right)return -1;

	}

}


int main() {

	int choice{ 0 }, num{ 0 };
	Array objectArray;

	do {

		do {

			ClearScrean();
			cout << "[1] - Print mass\n[2] - Add number in array\n[3] - Delete number in array\n"
				 << "[4] - Find minimal number\n[5] - Find maximal number\n"
				 << "[6] - Sort array\n[7] - Find number\n[8] - Change number\n[0] - Exit" << endl;

			if (choice >= 0 && choice <= 8)cout << "Enter your choice: ";
			else cout << "There is no such choice! Enter your choice again: ";

			cin >> choice;

		} while (choice < 0 || choice > 8);

		ClearScrean();

		switch (choice) {

		case 1: cout << objectArray << endl; break;

		case 2:
			cout << "Enter number for add: "; 
			cin >> num; 
			objectArray += num; 
			break;

		case 3:
			cout << "Enter the number that will be deleted: "; 
			cin >> num;
			objectArray -= num; 
			break;

		case 4: 
			cout << "Minimal number: " << FindMinimalNum<int>(objectArray) << endl; 
			break;

		case 5:
			cout << "Maximal number: " << FindMaximalNum<int>(objectArray) << endl;
			break;

		case 6:SortArray(objectArray, 0, objectArray.GetSize() - 1); break;

		case 7:
			cout << "Enter the number for find(Before searching for a number, sort it!): ";
			cin >> num;
			num = FindIndexNum(objectArray, 0, objectArray.GetSize() - 1, num) + 1;
			ClearScrean();
			if (num != -1)cout << "Your number is on " << num << " place in array" << endl;
			else cout << "In array none your number!" << endl;
			break;

		case 8:
			cout << "Enter the number for change(Before searching for a number, sort it!): ";
			cin >> num;
			num = FindIndexNum(objectArray, 0, objectArray.GetSize() - 1, num);
			ClearScrean();
			if (num != -1) {
				cout << "Enter the number you will change to: ";
				cin >> objectArray[num];

			}
			else cout << "In array none your number!" << endl;
			break;
		}

		if (choice != 0)Enter();

	} while (choice != 0);

	return 0;
}