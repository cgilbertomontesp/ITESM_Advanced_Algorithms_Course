/* 

        Merge Sort Algorithm Implementation

        To test this implementation with different cases, 
        you can do so by running this file and entering the number of elements you want your array to have.
        After that, you will be prompted to enter each element of the array one by one as a double (e.g., 1.0), 
        pressing enter after each number. The program will then display the original array, 
        sort it using the Merge Sort algorithm, and finally, display the sorted array.

        Time Complexity: O(n log n)
        Space Complexity: O(n)

*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to merge two subarrays of array.
// left is the starting index of the left subarray, middle is the ending index of the left subarray (and middle point of the array), and right is the ending index of the right subarray.
void merge(vector<double>&array, int left, int middle, int right){
    // Variables to compare subarray elements
    int i, j, k;

    // Size of left and right subarrays
    int nLeft = middle - left + 1;
    int nRight = right - middle;

    // Initializes left and right subarrays to their size
    vector<double> leftElements(nLeft);
    vector<double> rightElements(nRight);

    // Copy elements from the first half of the array to the left subarray
    for (int i=0; i < nLeft; i++){
        leftElements[i] = array[left + i]; 
    }

    // Copy elements from the second half of the array to the right subarray
    for (int j=0; j < nRight; j++){
        rightElements[j] = array[middle + 1 + j];
    }

    // Indices to traverse the left (i), right (j), and original array (k)
    i = 0;
    j = 0;
    k = left;  

    // Merge the left and right subarrays back into the original array in sorted order
    while(i < nLeft && j < nRight){
        if(leftElements[i] <= rightElements[j]){ // If current element of left subarray is smaller, place it in the array and advance to the next position
            array[k] = leftElements[i]; 
            i++;
        }else{
            array[k] = rightElements[j]; // If current element of right subarray is smaller, place it in the array and advance to the next position
            j++;
        }
        k++; // Move to the next position in the original array
    }

    // Copy any remaining elements of the right subarray
    while (j < nRight){
        array[k] = rightElements[j];
        j++; 
        k++;
    }

    // Copy any remaining elements of the left subarray
    while (i < nLeft){
        array[k] = leftElements[i];
        i++; 
        k++;
    }    
}

// Function to perform merge sort on the array
// left is the starting index and right is the ending index of the array or subarray
void mergeSort(vector<double>&array, int left, int right){
    // Base condition: If the array has more than one element
    if (left < right){
        // Find the middle point to divide the array into two halves
        int middle = left + (right - left)/2;

        mergeSort(array, left, middle); // Recursively sort the first half
        mergeSort(array, middle + 1, right); // Recursively sort the second half

        merge(array, left, middle, right); // Merge the two sorted halves
    }
}

// Function to print the elements of the array
void printArray(const vector<double>& array) {
    cout << fixed << setprecision(1);
    for (double num : array) {
        cout << num << " ";
    }
    cout << endl;
}

int main(){
    // Ask user for the number of elements the array is going to have.
    int n;
    cout << "Enter the number of elements you want your array to have: ";
    cin >> n; 
    cout << "Enter each number individualy as a double (e.g. 1.0), press enter after each number to be able to enter the next number." << endl;

    //Create array of user-specified length.
    vector<double> userArray(n);
    
    //Populate array with user input.
    double value;
    for (int i = 0; i < n; i++) {
        cout << "#" << i + 1 << ": ";
        cin >> value;
        userArray[i] = value;
    }

    //Print original array.
    cout << "Original array:" << endl;
    printArray(userArray);

    //Sort array via Merge Sort
    mergeSort(userArray, 0, userArray.size()-1);

    //Print sorted array.
    cout << "Sorted array:" << endl;
    printArray(userArray);

    return 0;
}
