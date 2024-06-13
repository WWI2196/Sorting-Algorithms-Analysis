#include <iostream>
#include <chrono> // For time measurement
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono; // For time measurement

const int NAMECOLUMNWIDTH = 25, ARRAYSIZECOLUMNWIDTH = 10, COMPARISONSCOLUMNWIDTH = 25, RUNTIMECOLUMNWIDTH = 25; // Column widths for the table
const string SORTINGNAMES[] = { "Selection Sort","Insertion Sort","Merge Sort","Quick Sort","Counting Sort" }; // Sorting algorithm names

void swap(int* a, int* b);
void generateRandomArray(int* numberArray, int size);
void printResults(int size, long long comparisons, double runTime, int type);
void sortSelection(int* numberArray, int arraySize, int sortType);
void merge(int arr[], int l, int m, int r, long long& comparisons);
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

void printTableHeader() { // funtion for the printing table header
	
	cout << endl;
	// table headers
	cout << '|' << left << setw(NAMECOLUMNWIDTH) << "Sorting Algorithm Name"<< '|' << setw(ARRAYSIZECOLUMNWIDTH) << "Array Size" << '|' << setw(COMPARISONSCOLUMNWIDTH) << "Number of Comparisons"<< '|' << setw(RUNTIMECOLUMNWIDTH) << "Run time (in ms)" << '|' << endl;

	// to print the line seperating the table header from the data table
	cout << '|' << string(NAMECOLUMNWIDTH, '-') << '+'<< string(ARRAYSIZECOLUMNWIDTH, '-') << '+'<< string(COMPARISONSCOLUMNWIDTH, '-') << '+'<< string(RUNTIMECOLUMNWIDTH, '-') << '|' << endl;
}

void printResults(int size, long long comparisons, double runTime, int type) { // function for printing the results in the table

	cout << '|' << left << setw(NAMECOLUMNWIDTH) << SORTINGNAMES[type - 1] << '|' << setw(ARRAYSIZECOLUMNWIDTH) << size << '|' << setw(COMPARISONSCOLUMNWIDTH) << comparisons << '|' << setw(RUNTIMECOLUMNWIDTH - 3) << runTime << " ms" << '|' << endl;
	// print the results seperated by | with a fixed column width
}

void swap(int* a, int* b) { // function to swap two elements
	int temp = *a;
	*a = *b;
	*b = temp;
}

void generateRandomArray(int* numberArray, int size) {
	srand(time(0)); // Seed for random number generator to avoid getting the same random numbers every time the program is run

	for (int i = 0; i < size; i++) {
		numberArray[i] = (rand() % (size * 10)) + 1; // generate random number between 1 and 10*size and add to the array
	}
}

void selectionSort(int numberArray[], int size, double& runTime, long long& comparisons) { // function for selection sort

	auto start = high_resolution_clock::now(); // start the clock 

	for (int i = 0; i < size - 1; i++) {
		for (int y = i + 1; y < size; y++) {
			comparisons++; // count the number of steps following the sorting process
			if (numberArray[i] > numberArray[y]) swap(numberArray[i], numberArray[y]);
		}
	}

	auto end = high_resolution_clock::now(); // end the clock

	runTime = duration_cast<chrono::duration<double, milli>>(end - start).count(); // calculate the runtime by subtracting the start time from the end time and convert it to milliseconds
	

}

void insertionSort(int numberArray[], int size, double& runTime, long long& comparisons) { // function for insertion sort

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

void merge(int numberArray[], int l, int m, int r, long long& comparisons) { // function for merging two arrays
	int i, j;
	int n1 = m - l + 1;
	int n2 = r - m;

	int* L = new int[n1];  // dynamically allocate memory for L
	int* R = new int[n2];  // dynamically allocate memory for R

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

	delete[] L;  
	delete[] R;  
}

void mergeSort(int numberArray[], int l, int r, long long& comparisons) { // function for merge sort
	if (l < r) {
		comparisons++;
		int m = l + (r - l) / 2;

		mergeSort(numberArray, l, m, comparisons);
		mergeSort(numberArray, m + 1, r, comparisons);

		merge(numberArray, l, m, r, comparisons);
	}

}

int partition(int numberArray[], int low, int high, long long& comparisons) { // function for partitioning the array

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

void quickSort(int numberArray[], int low, int high, long long& comparisons) { // function for quick sort
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

void sortSelection(int* numberArray, int arraySize, int sortType) { // function to select the sorting algorithm based on the user's choice
	double runTime = 0; // variable to store the runtime of the sorting process
	long long comparisons = 0; // variable to store the number of steps in the sorting process

	int* copyArray = new int[arraySize]; // array to store the copy of the original array

	copy(numberArray, numberArray + arraySize, copyArray); // copy the original number array to the copy array

	switch (sortType) { 
	case 1:
		selectionSort(copyArray, arraySize, runTime, comparisons = 0); // call the selection sort function
		printResults(arraySize, comparisons, runTime, sortType); // print the results in the table
		break;
	case 2:
		insertionSort(copyArray, arraySize, runTime, comparisons = 0); // call the insertion sort function
		printResults(arraySize, comparisons, runTime, sortType);
		break;
	case 3: 
	{ // {} to ensure that the initialization of start and end variables occurs within the scop
		auto start = high_resolution_clock::now();
		mergeSort(copyArray, 0, arraySize - 1, comparisons = 0); // call the merge sort function
		auto end = high_resolution_clock::now();

		runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();
		printResults( arraySize, comparisons, runTime, sortType);
		break;
	}
	case 4:
	{
		auto start = high_resolution_clock::now();
		quickSort(copyArray, 0, arraySize - 1, comparisons = 0); // call the quick sort function
		auto end = high_resolution_clock::now();

		runTime = duration_cast<chrono::duration<double, milli>>(end - start).count();
		printResults( arraySize, comparisons, runTime, sortType);
		break;
	}
	case 5: {
		countingSort_R(copyArray, arraySize, runTime, comparisons = 0); // call the counting sort function
		printResults( arraySize, comparisons, runTime, sortType);
		break;
	}
	default:
		break;
	}

	delete[] copyArray;
}

void displaySubMenu() { // function to display the sub menu
	cout << "\n1. Selection Sort\n";
	cout << "2. Insertion Sort\n";
	cout << "3. Merge Sort\n";
	cout << "4. Quick Sort\n";
	cout << "5. Counting Sort\n";

}

void displayMainMenu() { // function to display the main menu
	cout << "\n1. Test an individual sorting algorithm\n";
	cout << "2. Test multiple sorting algorithms \n";
	cout << "3. Exit\n";
}

bool inputValidator(char input, int lb, int ub) { // function to validate the user input for the selecting option in the menues
	if (cin.fail() || input < lb + '0' || input > ub + '0') { // check if the input is not of assigned type or not within the range
		cin.clear(); // clear the input buffer
		cin.ignore(1000, '\n'); // ignore the input
		cout << "Invalid input. Please enter a valid choice." << endl;
		return false;
	}
	return true;
}

bool arrayInputSizeValidator(int input) { // function to validate the user input for the array size
	if (cin.fail() || input <= 0) { // check if the input is not of assigned type or a zero or a negative number
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Enter a positive integer for the array size." << endl;
		return false;
	}
	return true;
}

int main() {
	int arraySize; // variable to store the size of the array

	while (true) {
		displayMainMenu(); // display the main menu

		char mainMenuChoice; // variable to store the user's choice in the main menu

		cout << "Enter your choice: ";
		cin >> mainMenuChoice;

		if (!inputValidator(mainMenuChoice, 1, 3)) continue; // validate the user's input

		if (mainMenuChoice == '3') break; // exit the program if the user chooses 3

		while (true) {
			cout << "Enter the size of the array: ";
			cin >> arraySize;

			if (!arrayInputSizeValidator(arraySize)){ // validate the user's input for array size
				continue;
			}
			else {
				break;
			}
		}
		
		switch (mainMenuChoice - '0') { // Convert char to int 
		case 1: {
			int* numberArray = new int[arraySize]; 
			generateRandomArray(numberArray, arraySize); // generate random array

			displaySubMenu(); // display the sub menu
			char subMenuChoice_; 
			cout << "Enter the sorting type: ";
			cin >> subMenuChoice_;

			if (!inputValidator(subMenuChoice_, 1, 5)) { // validate the user's input for the sorting type
				delete[] numberArray;
				break;
			}
			
			int subMenuChoice = subMenuChoice_ - '0'; // Convert char to int

			printTableHeader(); // print the table header
			sortSelection(numberArray, arraySize, subMenuChoice); // call the sortSelection function to sort the array based on the user's choice

			delete[] numberArray;
			break;
			
		}
		case 2: {
			int* numberArray = new int[arraySize];
			generateRandomArray(numberArray, arraySize);

			printTableHeader();

			for (int i = 1; i <= 5; i++) { // loop through each soting type
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
