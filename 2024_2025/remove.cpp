#include <iostream>

using namespace std;

int remove (int v, int x [], int n) {
	int i = 0;
    int t = 0;
	for(int p = 0; p < n; p++) {
		if (x[p] <= v) {
			x[t] = x[p];
			t++;
		}
	}
	return t;
}



void displayArray(int x[], int n) {
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}


int main() {
    int x[] = {5, 2, 8, 6, 3, 10, 4};  // Test array
    int n = sizeof(x) / sizeof(x[0]);   // Get the size of the array

    int v;  // The threshold value
    cout << "Enter the threshold value v: ";
    cin >> v;

    cout << "Original array: ";
    displayArray(x, n);

    // Call the REMOVE function
    int newSize = remove(v, x, n);

    // Display the result
    cout << "Array after removing elements greater than " << v << ": ";
    displayArray(x, newSize);

    cout << "Number of elements <= " << v << ": " << newSize << endl;

    return 0;
}
