#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int NAMECOLUMNWIDTH = 25, ARRAYSIZECOLUMNWIDTH = 10, COMPARISONSCOLUMNWIDTH = 25, RUNTIMECOLUMNWIDTH = 25; // Column widths for the table

void swap(int* a, int* b);
void generateRandomArray(int* numberArray, int size);
void printResults(int size, long long comparisons, double runTime, int type);
void sortSelection(int* numberArray, int arraySize, int sortType);
void merge(int arr[], int l, int m, int r, long long& comparisons);
void printArray(int numberArray[], int size);
void insertionSort(int numberArray[], int size, double& runTime, long long& comparisons);
void selectionSort(int numberArray[], int size, double& runTime, long long& comparisons);
void mergeSort(int numberArray[], int l, int r, long long& comparisons);
void countingSort_R(int numberArray[], int size, double& runTime, long long& comparisons);
int partition(int numberArray[], int low, int high, long long& comparisons);
void quickSort(int numberArray[], int low, int high, long long& comparisons);
void printTableHeader();
void displaySubMenu();
void displayMainMenu();
bool inputValidator(char input, int lb, int ub);
bool arrayInputSizeValidator(int input);

void printArray(int numberArray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << numberArray[i] << " ";
	}
	cout << endl;
}

void printTableHeader() {
	
	// Print the table headers with vertical bars
	cout << '|' << left << setw(NAMECOLUMNWIDTH) << "Sorting Algorithm Name"<< '|' << setw(ARRAYSIZECOLUMNWIDTH) << "Array Size" << '|' << setw(COMPARISONSCOLUMNWIDTH) << "Number of Comparisons"<< '|' << setw(RUNTIMECOLUMNWIDTH) << "Run time (in ms)" << '|' << endl;

	// Print a line separator
	cout << '|' << string(NAMECOLUMNWIDTH, '-') << '+'<< string(ARRAYSIZECOLUMNWIDTH, '-') << '+'<< string(COMPARISONSCOLUMNWIDTH, '-') << '+'<< string(RUNTIMECOLUMNWIDTH, '-') << '|' << endl;
}

void printResults(int size, long long comparisons, double runTime, int type) {
	// Column widths
	int NAMECOLUMNWIDTH = 25, ARRAYSIZECOLUMNWIDTH = 10, COMPARISONSCOLUMNWIDTH = 25, RUNTIMECOLUMNWIDTH = 25;

	string algorithmName;

	switch (type) {
	case 1:
		algorithmName = "Selection Sort";
		break;
	case 2:
		algorithmName = "Insertion Sort";
		break;
	case 3:
		algorithmName = "Merge Sort";
		break;
	case 4:
		algorithmName = "Quick Sort";
		break;
	case 5:
		algorithmName = "Counting Sort";
		break;
	default:
		break;
	}

	cout << '|' << left << setw(NAMECOLUMNWIDTH) << algorithmName << '|' << setw(ARRAYSIZECOLUMNWIDTH) << size << '|' << setw(COMPARISONSCOLUMNWIDTH) << comparisons << '|' << setw(RUNTIMECOLUMNWIDTH-3) <<runTime << " ms" << '|' << endl;

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

void selectionSort(int numberArray[], int size, double& runTime, long long& comparisons) {

	auto start = high_resolution_clock::now();

	for (int i = 0; i < size - 1; i++) {
		for (int y = i + 1; y < size; y++) {
			comparisons++;
			if (numberArray[i] > numberArray[y]) swap(numberArray[i], numberArray[y]);
		}
	}

	auto end = high_resolution_clock::now();

	runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();

}

void insertionSort(int numberArray[], int size, double& runTime, long long& comparisons) {

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

}

void merge(int numberArray[], int l, int m, int r, long long& comparisons) {
	int i, j;
	int n1 = m - l + 1;
	int n2 = r - m;

	int* L = new int[n1];  // Dynamically allocate memory for L
	int* R = new int[n2];  // Dynamically allocate memory for R

	for (i = 0; i < n1; i++) {
		L[i] = numberArray[l + i];
		comparisons++;
	}

	for (j = 0; j < n2; j++) {
		R[j] = numberArray[m + 1 + j];
		comparisons++;
	}

	i = 0;
	j = 0;

	while (i < n1 && j < n2) {
		comparisons++;
		if (L[i] <= R[j]) {
			numberArray[l] = L[i];
			i++;
		}
		else {
			numberArray[l] = R[j];
			j++;
		}
		l++;
	}

	while (i < n1) {
		numberArray[l] = L[i];
		i++;
		l++;
		comparisons++;
	}

	while (j < n2) {
		numberArray[l] = R[j];
		j++;
		l++;
		comparisons++;
	}

	delete[] L;  // Deallocate memory for L
	delete[] R;  // Deallocate memory for R
}

void mergeSort(int numberArray[], int l, int r, long long& comparisons) {
	if (l < r) {
		comparisons++;
		int m = l + (r - l) / 2;

		mergeSort(numberArray, l, m, comparisons);
		mergeSort(numberArray, m + 1, r, comparisons);

		merge(numberArray, l, m, r, comparisons);
	}

}

int partition(int numberArray[], int low, int high, long long& comparisons) {

	int pivot = numberArray[high];

	int i = (low - 1);

	for (int j = low; j < high; j++) {
		comparisons++;
		if (numberArray[j] <= pivot) {

			i++;

			swap(&numberArray[i], &numberArray[j]);
		}
	}

	comparisons++;
	swap(&numberArray[i + 1], &numberArray[high]);

	return (i + 1);
}

void quickSort(int numberArray[], int low, int high, long long& comparisons) {
	if (low < high) {
		comparisons++;
		int pivot = partition(numberArray, low, high,comparisons);

		quickSort(numberArray, low, pivot - 1, comparisons);

		quickSort(numberArray, pivot + 1, high,comparisons);
	}
}

void countingSort_R(int numberArray[], int size, double& runTime, long long& comparisons) { // counting sorting for an array with repetitive elements
	auto start = high_resolution_clock::now();

	int* index_array = new int[size]();  // Initialize with zero
	int* sorted_array = new int[size];

	// Count elements less than the current element
	for (int i = 0; i < size; i++) {
		comparisons++;  // Counting the comparison of the loop condition
		int count = 0;
		for (int y = 0; y < size; y++) {
			comparisons++;  // Counting the comparison of the loop condition
			if (numberArray[y] < numberArray[i]) {
				count++;
			}
		}
		index_array[i] = count;
	}

	// Handle duplicates
	for (int i = 0; i < size; i++) {
		comparisons++;  // Counting the comparison of the loop condition
		for (int y = 0; y < i; y++) {
			comparisons++;  // Counting the comparison of the loop condition
			if (numberArray[y] == numberArray[i]) {
				index_array[i]++;
			}
		}
	}

	// Build the sorted array
	for (int i = 0; i < size; i++) {
		comparisons++;  // Counting the comparison of the loop condition
		sorted_array[index_array[i]] = numberArray[i];
	}

	// Copy sorted array back to original array
	for (int i = 0; i < size; i++) {
		comparisons++;  // Counting the comparison of the loop condition
		numberArray[i] = sorted_array[i];
	}

	auto end = high_resolution_clock::now();
	runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();

	delete[] index_array;
	delete[] sorted_array;
}

void sortSelection(int* numberArray, int arraySize, int sortType) {
	double runTime = 0;
	long long comparisons = 0;

	int* copyArray = new int[arraySize];

	copy(numberArray, numberArray + arraySize, copyArray);

	switch (sortType) {
	case 1:
		selectionSort(copyArray, arraySize, runTime, comparisons = 0);
		printResults(arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	case 2:
		insertionSort(copyArray, arraySize, runTime, comparisons = 0);
		printResults(arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	case 3: { //to ensure that the initialization of start and end variables occurs within the scope of each case that requires them. One way to achieve this is by wrapping the code for each case inside braces {}.
		auto start = high_resolution_clock::now();
		mergeSort(copyArray, 0, arraySize - 1, comparisons = 0);
		auto end = high_resolution_clock::now();
		runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();
		printResults( arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	}
	case 4:
	{
		auto start = high_resolution_clock::now();
		quickSort(copyArray, 0, arraySize - 1, comparisons = 0);
		auto end = high_resolution_clock::now();
		runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();
		printResults( arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	}
	case 5: {
		countingSort_R(copyArray, arraySize, runTime, comparisons = 0);
		printResults( arraySize, comparisons, runTime, sortType);
		cout << endl;
		break;
	}
	default:
		cout << "Invalid sort type selected!" << endl;
		break;

	}

	delete[] copyArray;
}

void displaySubMenu() {
	cout << "\n1. Selection Sort\n";
	cout << "2. Insertion Sort\n";
	cout << "3. Merge Sort\n";
	cout << "4. Quick Sort\n";
	cout << "5. Counting Sort\n";

}

void displayMainMenu() {
	cout << "\n1. Test an individual sorting algorithm\n";
	cout << "2. Test multiple sorting algorithms \n";
	cout << "3. Exit\n";
}

bool inputValidator(char input, int lb, int ub) {
	if (cin.fail() || input < lb + '0' || input > ub + '0') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please enter a valid choice." << endl;
		return false;
	}
	return true;
}

bool arrayInputSizeValidator(int input) {
	if (cin.fail() || input <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Enter a positive integer for the array size." << endl;
		return false;
	}
	return true;
}


int main() {
	int arraySize;

	while (true) {
		displayMainMenu();

		char mainMenuChoice;

		cout << "Enter your choice: ";
		cin >> mainMenuChoice;

		if (!inputValidator(mainMenuChoice, 1, 3)) continue;

		if (mainMenuChoice == '3') break;

		while (true) {
			cout << "Enter the size of the array: ";
			cin >> arraySize;

			if (!arrayInputSizeValidator(arraySize)) {
				continue;
			}
			else {
				break;
			}
		}
		
		switch (mainMenuChoice - '0') { // Convert char to int
		case 1: {
			int* numberArray = new int[arraySize];
			generateRandomArray(numberArray, arraySize);

			displaySubMenu();
			char subMenuChoice_;
			cout << "Enter the sorting type: ";
			cin >> subMenuChoice_;

			if (!inputValidator(subMenuChoice_, 1, 5)) {
				delete[] numberArray;
				break;
			}
			
			int subMenuChoice = subMenuChoice_ - '0'; // Convert char to int

			printTableHeader();
			sortSelection(numberArray, arraySize, subMenuChoice);

			delete[] numberArray;
			break;
			
		}
		case 2: {
			int* numberArray = new int[arraySize];
			generateRandomArray(numberArray, arraySize);

			printTableHeader();

			for (int i = 1; i <= 5; i++) {
				sortSelection(numberArray, arraySize, i);
			}

			delete[] numberArray;
			break;
		}
		default:
			break;
		}
	}

	return 0;
}
