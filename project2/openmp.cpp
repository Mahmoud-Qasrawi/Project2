#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <omp.h>
using namespace std;

const int SIZE = 1000000; // You can change this to 1000, 10000, etc.
const int MAX_DEPTH = 2;  // Controls how much to parallelize

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right, int depth) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (depth < MAX_DEPTH) {
        #pragma omp task shared(arr)
        mergeSort(arr, left, mid, depth + 1);

        #pragma omp task shared(arr)
        mergeSort(arr, mid + 1, right, depth + 1);

        #pragma omp taskwait
    } else {
        mergeSort(arr, left, mid, depth + 1);
        mergeSort(arr, mid + 1, right, depth + 1);
    }

    merge(arr, left, mid, right);
}

void generateRandomArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i)
        arr[i] = rand() % 100000;
}

int main() {
    vector<int> arr(SIZE);
    generateRandomArray(arr);

    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, arr.size() - 1, 0);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}

