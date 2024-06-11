#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

int selectionSort(int numberArray[], int size, double& duration,int& comparisons);
void swap(int* a, int* b);
void generateRandomArray(int* numberArray, int size);
void printResults(int numberArray[], int size, int comparisons, double duration, int type);

void printArray(int numberArray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << numberArray[i] << " ";
	}
	cout << endl;
}

void printResults(int numberArray[], int size, int comparisons, double duration,int type) {

	switch (type)
	{
	case 1:
		cout << "Selection Sort" << endl;
		printArray(numberArray, size);
		cout << "Number of comparisons: " << comparisons << endl;
		cout << "Time taken: " << duration << " milliseconds" << endl;
		break;
	case 2:
		cout << "Insertion Sort" << endl;
		printArray(numberArray, size);
		cout << "Number of comparisons: " << comparisons << endl;
		cout << "Time taken: " << duration << " milliseconds" << endl;
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


int selectionSort(int numberArray[], int size, double& duration,int& comparisons) {

	auto start = high_resolution_clock::now();

	for (int i = 0; i < size - 1; i++) {
		for (int y = i + 1; y < size; y++) {
			comparisons++;
			if (numberArray[i] > numberArray[y]) swap(numberArray[i], numberArray[y]);
		}
	}

	auto end = high_resolution_clock::now();

	duration = duration_cast<chrono::duration<double, milli>>(end - start).count();

	return comparisons;
}

int insertionSort(int numberArray[], int size, double& duration,int& comparisons) {

	printArray(numberArray, size);

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

	duration = duration_cast<chrono::duration<double, milli>>(end - start).count();

	return comparisons;
}

int main() {

	int arraySize;

	cout <<"Enter the size of the array: ";
	cin >> arraySize;

	int* numberArray = new int[arraySize];
	generateRandomArray(numberArray, arraySize);

	double duration;
	int comparisons;

	int* copyArray = new int[arraySize];
	copy(numberArray, numberArray + arraySize, copyArray);

	printArray(numberArray, arraySize);
	comparisons = selectionSort(copyArray, arraySize, duration = 0, comparisons = 0);
	printResults(copyArray, arraySize, comparisons, duration,1);

	printArray(numberArray, arraySize);
	comparisons = insertionSort(numberArray, arraySize, duration=0, comparisons=0);
	printResults(numberArray, arraySize, comparisons, duration,2);

	
	return 0;
}
