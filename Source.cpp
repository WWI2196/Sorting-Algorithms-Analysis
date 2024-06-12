#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

int selectionSort(int numberArray[], int size, double& runTime,int& comparisons);
void swap(int* a, int* b);
void generateRandomArray(int* numberArray, int size);
void printResults(int numberArray[], int size, int comparisons, double runTime, int type);


void printArray(int numberArray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << numberArray[i] << " ";
	}
	cout << endl;
}

void printResults(int numberArray[], int size, int comparisons, double runTime,int type) {

	switch (type)
	{
	case 1:
		cout << "Selection Sort" << endl;
		printArray(numberArray, size);
		cout << "Number of comparisons: " << comparisons << endl;
		cout << "Time taken: " << runTime << " milliseconds" << endl;
		break;
	case 2:
		cout << "Insertion Sort" << endl;
		printArray(numberArray, size);
		cout << "Number of comparisons: " << comparisons << endl;
		cout << "Time taken: " << runTime << " milliseconds" << endl;
		break;
	default:
		break;
	}
	
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void generateRandomArray(int* numberArray, int size) {
	for (int i = 0; i < size; i++) {
		numberArray[i] = (rand() % (size*10))+1;
	}
}


int selectionSort(int numberArray[], int size, double& runTime,int& comparisons) {

	auto start = high_resolution_clock::now();

	for (int i = 0; i < size - 1; i++) {
		for (int y = i + 1; y < size; y++) {
			comparisons++;
			if (numberArray[i] > numberArray[y]) swap(numberArray[i], numberArray[y]);
		}
	}

	auto end = high_resolution_clock::now();

	runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();

	return comparisons;
}

int insertionSort(int numberArray[], int size, double& runTime,int& comparisons) {

	auto start = high_resolution_clock::now();

	for (int i = 1; i < size; i++) {
		int j = i;
		comparisons++;

		while (j > 0 && numberArray[j] < numberArray[j - 1]) {
			swap(&numberArray[j], &numberArray[j - 1]);
			j--;
			comparisons++;
		}
	}

	auto end = high_resolution_clock::now();

	runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();

	return comparisons;
}

void displayMenu() {
    cout << "1. Test an individual sorting algorithm\n";
    cout << "2. Test multiple sorting algorithms\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

void displaySubMenu() {
	cout << "1. Selection Sort\n";
	cout << "2. Insertion Sort\n";
	cout << "3. Merge Sort\n";
	cout << "4. Quick Sort\n";
	cout << "5. Counting Sort\n";
	cout << "Choose an algorithm: ";
}

void sortSelection(int* numberArray, int arraySize, int(*sortFunction)(int*, int, double&, int&), int sortType) {
	double runTime = 0;
	int comparisons = 0;

	int* copyArray = new int[arraySize];

	copy(numberArray, numberArray + arraySize, copyArray);

	cout << "Array before sorting: ";
	printArray(numberArray, arraySize);
	printResults(copyArray, arraySize, sortFunction(copyArray, arraySize, runTime, comparisons), runTime, sortType);
	cout << endl;

	delete[] copyArray;
}

int main() {

	int arraySize;

	cout <<"Enter the size of the array: ";
	cin >> arraySize;

	int* numberArray = new int[arraySize];
	generateRandomArray(numberArray, arraySize);

	
	sortSelection(numberArray, arraySize, selectionSort, 1);
	sortSelection(numberArray, arraySize, insertionSort, 2);

	delete[] numberArray;
	
	return 0;
}
