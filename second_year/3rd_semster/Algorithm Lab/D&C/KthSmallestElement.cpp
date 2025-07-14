#include <iostream>
#include <algorithm>
#include <climits>

int medianOfMedians(int arr[], int left, int right);

// Utility function to partition the array around a pivot
int partition(int arr[], int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[right]);  // 1 4 5 2 3
    int storeIndex = left;
    for (int i = left; i < right; ++i) {
        if (arr[i] < pivotValue) {
            std::swap(arr[i], arr[storeIndex]);
            ++storeIndex;
        }
    }
    std::swap(arr[storeIndex], arr[right]);
    return storeIndex;
}

// Recursive function to perform quickselect
int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = medianOfMedians(arr, left, right);
    int newPivotIndex = partition(arr, left, right, pivotIndex);   //  

    if (k == newPivotIndex) {
        return arr[k];
    } else if (k < newPivotIndex) {
        return quickSelect(arr, left, newPivotIndex - 1, k);
    } else {
        return quickSelect(arr, newPivotIndex + 1, right, k);
    }
}

// Function to find the median of medians
int medianOfMedians(int arr[], int left, int right) {
    int numElements = right - left + 1;
    int numMedians = (numElements + 4) / 5; // ceiling(numElements / 5)

    int* medians = new int[numMedians];
    for (int i = 0; i < numMedians; ++i) {
        int subLeft = left + i * 5;
        int subRight = std::min(subLeft + 4, right);
        std::sort(arr + subLeft, arr + subRight + 1);
        medians[i] = arr[(subLeft + subRight) / 2];
    }

    int medianOfMedian = (numMedians == 1) ? medians[0] : quickSelect(medians, 0, numMedians -1, numMedians/ 2);

    delete[] medians;
    return medianOfMedian;
}

// Function to find the k-th smallest element in an unsorted array
int findKthSmallest(int arr[], int size, int k) {
    if (k < 0 || k >= size) {
        throw std::out_of_range("Index out of range");
    }
    return quickSelect(arr, 0, size - 1, k);
}

int main() {
    int arr[] = {3, 6, 2, 8, 7, 5, 1}; // 1 2 3 5 6 7 8
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 5; // k-th smallest element (0-based index)

    try {
        int result = findKthSmallest(arr, size, k);
        std::cout << "The " << k + 1 << "-th smallest element is: " << result << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
