#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

int selectionSort(int numberArray[], int size, double& runTime, int& comparisons);
void swap(int* a, int* b);
void generateRandomArray(int* numberArray, int size);
void printResults(int numberArray[], int size, int comparisons, double runTime, int type);
void sortSelection(int* numberArray, int arraySize, int sortType);
void merge(int arr[], int l, int m, int r, int& comparisons);
void printArray(int numberArray[], int size);
int insertionSort(int numberArray[], int size, double& runTime, int& comparisons);
void mergeSort(int numberArray[], int l, int r, int& comparisons);

void printArray(int numberArray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << numberArray[i] << " ";
	}
	cout << endl;
}

void printResults(int numberArray[], int size, int comparisons, double runTime, int type) {

	switch (type)
	{
	case 1:
		cout << "Selection Sort" << endl;
		break;
	case 2:
		cout << "Insertion Sort" << endl;
		break;
	case 3:
		cout << "Merge Sort" << endl;
		break;
	default:
		break;
	}

	/*printArray(numberArray, size);*/
	cout << "Number of comparisons: " << comparisons << endl;
	cout << "Time taken: " << runTime << " milliseconds" << endl;

}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void generateRandomArray(int* numberArray, int size) {
	srand(time(0));

	for (int i = 0; i < size; i++) {
		numberArray[i] = (rand() % (size * 10)) + 1; // Random number between 1 and 10*size
	}
}


int selectionSort(int numberArray[], int size, double& runTime, int& comparisons) {

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

int insertionSort(int numberArray[], int size, double& runTime, int& comparisons) {

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

void merge(int arr[], int l, int m, int r, int& comparisons) {
	int i, j;
	int n1 = m - l + 1;
	int n2 = r - m;

	int* L = new int[n1];  // Dynamically allocate memory for L
	int* R = new int[n2];  // Dynamically allocate memory for R

	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
		comparisons++;
	}

	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
		comparisons++;
	}

	i = 0;
	j = 0;

	while (i < n1 && j < n2) {
		comparisons++;
		if (L[i] <= R[j]) {
			arr[l] = L[i];
			i++;
		}
		else {
			arr[l] = R[j];
			j++;
		}
		l++;
	}

	while (i < n1) {
		arr[l] = L[i];
		i++;
		l++;
		comparisons++;
	}

	while (j < n2) {
		arr[l] = R[j];
		j++;
		l++;
		comparisons++;
	}

	delete[] L;  // Deallocate memory for L
	delete[] R;  // Deallocate memory for R
}

void mergeSort(int numberArray[], int l, int r, int& comparisons) {
	if (l < r) {
		comparisons++;
		int m = l + (r - l) / 2;

		mergeSort(numberArray, l, m, comparisons);
		mergeSort(numberArray, m + 1, r, comparisons);

		merge(numberArray, l, m, r, comparisons);
	}

}


void displaySubMenu() {
	cout << "1. Selection Sort\n";
	cout << "2. Insertion Sort\n";
	cout << "3. Merge Sort\n";
	cout << "4. Quick Sort\n";
	cout << "5. Counting Sort\n";
	cout << "Choose an algorithm: ";
}

void sortSelection(int* numberArray, int arraySize, int sortType) {
	double runTime = 0;
	int comparisons = 0;

	int* copyArray = new int[arraySize];

	copy(numberArray, numberArray + arraySize, copyArray);

	/*cout << "Array before sorting: ";
	printArray(numberArray, arraySize);*/

	switch (sortType) {
	case 1:
		selectionSort(copyArray, arraySize, runTime, comparisons = 0);
		printResults(copyArray, arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	case 2:
		insertionSort(copyArray, arraySize, runTime, comparisons = 0);
		printResults(copyArray, arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	case 3: { //to ensure that the initialization of start and end variables occurs within the scope of each case that requires them. One way to achieve this is by wrapping the code for each case inside braces {}.
		auto start = high_resolution_clock::now();
		mergeSort(copyArray, 0, arraySize - 1, comparisons = 0);
		auto end = high_resolution_clock::now();
		runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();
		printResults(copyArray, arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	}
	default:
		cout << "Invalid sort type selected!" << endl;
		break;
	
	}

	delete[] copyArray;
}

int main() {

	int arraySize;

	cout << "Enter the size of the array: ";
	cin >> arraySize;

	int* numberArray = new int[arraySize];
	generateRandomArray(numberArray, arraySize);


	sortSelection(numberArray, arraySize, 1);
	sortSelection(numberArray, arraySize, 2);
	sortSelection(numberArray, arraySize, 3);

	delete[] numberArray;

	return 0;
}
