// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here  
    for(int i = 1; i < data.size(); i++){
        int key = data[i];
        int j = (i-1);
        while(key < data[j]){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(high > low){
        int mid = Partition(data, low, high);
        QuickSortSubVector(data, low, mid);
        QuickSortSubVector(data, mid+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    
    // Use Hoare Partition 
    // // Compare data[low] data[mid] data[high]
    // // Then exchange the second largest one with data[low]
    
    // int x = data[low];
    // int mid = int((low+high)/2);
    // int y = data[mid];
    // int z = data[high];
    // char choice= 'x';
    // if(x >= y && y >= z)        choice = 'y';
    // else if(z >= y && y >= x)   choice = 'y';
    // else if(z >= x && x >= y)   choice = 'x';
    // else if(y >= x && x >= z)   choice = 'x';
    // else if(y >= z && z >= x)   choice = 'z';
    // else if(x >= z && z >= y)   choice = 'z';
    // int tmp = data[low];
    // switch(choice){
    //     case 'x':
    //         x = data[low];
    //         break;
    //     case 'y':
    //         x = data[mid];
    //         data[low] = data[mid];
    //         data[mid] = tmp;
    //         break;
    //     case 'z':
    //         x = data[high];
    //         data[low] = data[high];
    //         data[high] = tmp;
    //         break;
    // }

    // Use randomized partition
    int p = rand() % (high - low + 1) + low;
    int x = data[p];
    data[p] = data[low];
    data[low] = x;
    
    
    // Use x to breakup the array into two
    int i = low;
    int j = high;
    while(true){
        while(data[j] > x){
            j--;
        }
        while(data[i] < x){
            i++;
        }
        if(i < j){
            if(data[j] == data[i]){
                j--;
                i++;
                continue;
            }
            int temp = data[j];
            data[j] = data[i];
            data[i] = temp;
        }
        else return j;
    } 
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(high > low){
        int mid = (high + low);
        if((mid % 2) == 0) mid = mid/2;
        else mid = (mid-1)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int len1 = middle1 - low + 1;
    int len2 = high - middle2 +1;
    vector<int> L, R;
    for(int i = 0; i < len1 ; i++){
        L.push_back(data[i+low]);
    }
    for(int i = 0; i < len2 ; i++){
        R.push_back(data[i+middle2]);
    }
    int i = 0; 
    int j = 0;
    for(int k = 0; k < high - low +1; k++){
        if(i == len1){
            data[low+k] = R[j];
            j++;
        }
        else if(L[i] < R[j] || j == len2){
            data[low+k] = L[i];
            i++;
        }
        else{
            data[low+k] = R[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int L = (2 * root) + 1;
    int R = (2 * root) + 2;
    if(L >= heapSize && R >= heapSize) 
        return;
    int largest;
    if(L < heapSize && data[L] > data[root]){
        largest = L;
    }
    else largest = root;
    if(R < heapSize && data[R] > data[largest]){
        largest = R;
    }
    if(largest != root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = ((data.size()/2) - (data.size()%2) - 1); i >= 0; i--){
        MaxHeapify(data, i);
    }
}

