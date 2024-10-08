// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// Initial code for testing the times of linear search vs binary search

#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

#define PRECISION 6 // precision shown on time prints

using namespace std;

// ---------------------------------------------------------------------
// Search 'key' in vector 'v' and return its position index it it exists
// or -1 if it does not exist
// ---------------------------------------------------------------------
int search(const vector<int> & v, int key) {
  // Iterate through each element of the vector 'v'
  /*for (int i = 0; i < v.size(); i++) {
    if (v[i] == key) {  // If the key is found
      return i;  // Return the index of the key
    }
  }*/

  int low = 0;
  int high = (int)v.size() - 1;
  
  while (low <= high) {
    int middle = low + (high - low) / 2;  // Calculate middle index

    if (key < v[middle]) {  
      high = middle - 1;  // Key is smaller, search in the left half
    }
    else if (key > v[middle]) {  
      low = middle + 1;  // Key is larger, search in the right half
    }
    else {
      return middle;  // Key found, return the index
    }
  }
  
  return -1;
}


// ---------------------------------------------------------------------
// Auxiliary function: read integers to a vector from an input stream
// First read an integer n (the amount of numbers) and then n integers
// ---------------------------------------------------------------------
vector<int> readIntVector(ifstream & f) {
  int n;
  f >> n;
  vector<int> v(n);
  for (int i=0; i<n; i++) f >> v[i];
  return v;
}


// ---------------------------------------------------------------------
// Test the search function reading input from 'inputFile' and the
// expected output from outputFile
// ---------------------------------------------------------------------
void testSearch(const string & inputFile, const string & outputFile) {

  // Open input file and store vector and keys to search
  ifstream input(inputFile);
  if (!input) {
    cerr << inputFile << " not found!" << endl;
    exit(1);
  }
  vector<int> seq   = readIntVector(input);
  vector<int> query = readIntVector(input);
  input.close();

  // Open output file and store expected answers
  ifstream output(outputFile);
  if (!output) {
    cerr << outputFile << " not found!" << endl;
    exit(1);
  }
  vector<int> correct = readIntVector(output);
  output.close();
    
  int n = seq.size();
  int q = query.size();
  vector<int> answer(q);
  cout << ". Case with n = " << n << " and " << q << " queries";

  // Call 'search' function for each query and save the given answers
  clock_t cstart = clock();
  for (int i=0; i<q; i++) answer[i] = search(seq, query[i]);
  clock_t cend = clock();

  // Check to see if all given answers are equal to the expected ones
  int incorrect = 0;
  for (int i=0; i<q; i++)
    if (answer[i] != correct[i])
      incorrect++;
  if (incorrect == 0) cout << " [OK]" << endl;
  else cout << " [INCORRECT]" << endl;
        
  double elapsed = (double)(cend - cstart) / CLOCKS_PER_SEC;
  cout << fixed << setprecision(PRECISION) << "  Time: " << elapsed << " s" << endl;
  cout << endl;
}  



// ---------------------------------------------------------------------
// Main function: test all 5 input examples
// ---------------------------------------------------------------------
int main() {

  testSearch("search_input01.txt", "search_output01.txt");
  testSearch("search_input02.txt", "search_output02.txt");
  testSearch("search_input03.txt", "search_output03.txt");
  testSearch("search_input04.txt", "search_output04.txt");
  testSearch("search_input05.txt", "search_output05.txt");
  
  return 0;
}
