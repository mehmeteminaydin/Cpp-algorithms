#include "the1.h"
#include <climits>
#include <iostream>


//TO SAVE THE DATA OF THE NODES, CREATE STRUCTURE
struct node{
	int value;
	int partition;
	int index;
	int p_last;
};

//insertion sort algorithm and count the comparision and swap

void insertionSort(int* arr, int size, long& comparison, long& swap) {
	int i, j, key;
	for (i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			// not sure if it is correct check the test cases
			if(j != 0){
				comparison++;
			}
			swap++;
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		comparison++;

	}

}



//write a heapify algorithm and count the comparision and swap
void heapify(node arr[], int n, int i, long& comparison, long& swap) {
	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int temp;

	if (l < n && arr[l].value != INT_MAX && ++comparison && arr[l].value < arr[smallest].value) {
		smallest = l;
	}
	if (r < n && arr[r].value != INT_MAX && ++comparison &&  arr[r].value < arr[smallest].value) {
		smallest = r;
	}
	if (smallest != i) {
		swap++;
		// swap arr[i] and arr[smallest]
		temp = arr[i].value;
		arr[i].value = arr[smallest].value;
		arr[smallest].value = temp;

		temp = arr[i].partition;
		arr[i].partition = arr[smallest].partition;
		arr[smallest].partition = temp;

		temp = arr[i].index;
		arr[i].index = arr[smallest].index;
		arr[smallest].index = temp;

		temp = arr[i].p_last;
		arr[i].p_last = arr[smallest].p_last;
		arr[smallest].p_last = temp;


		heapify(arr, n, smallest, comparison, swap);
	}
}


int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
	//create copy of the arr
	int* arr_copy = new int[size];
	for (int i = 0; i < size; i++) {
		arr_copy[i] = arr[i];
	}

	//if the size of the array is less than K, then sort the array by using insertion sort
	if (size < K) {
		insertionSort(arr, size, comparison, swap);
		return 1;
	}
	//otherwise, split the array into K sub-arrays and do K recursive calls to sort the partitions
	int* subArray = new int[size / K];
	
	int k = 0;
	int number_of_calls = 1;
	for (int i = 0; i < size; i += size / K) {
		for (int j = 0; j < size / K; j++) {
			subArray[j] = arr[i + j];
			//print the subarray
			std::cout << subArray[j] << " ";
			
		}
		std::cout << "1. for"<< std::endl;		
		number_of_calls += kWayMergeSortWithHeap(subArray, K, size / K, comparison, swap);
		for (int j = 0; j < size / K; j++) {
			arr_copy[i + j] = subArray[j];
			std::cout << arr_copy[i + j] << " ";
		}
		std::cout << "2. for" << std::endl;
		k++;
	}
	//then, merge K sorted arrays
	//when merging K sorted-arrays, you should use a Binary Min Heap to select the minimum element between the minimum elements of K partition arrays
	//when creating the array of the heap, firstly, generate a linear array whose elements are the minimum elements of K partition arrays
	//at the beginning, the position of the each element is determined by the belonging partition
	//for example, the element coming from partition 0 is placed to heap_array[0] and the element coming from partition 1 is placed to heap_array[1] etc
	//then, heapify the initial array
	// create heapArray node
	node* heapArray = new node[K];
	
	for (int i = 0; i < K; i++) {
		heapArray[i].index = i * (size / K);
		heapArray[i].value = arr_copy[i * (size / K)];
		heapArray[i].partition = i;
		heapArray[i].p_last = 0;
		std::cout << " partition : " << heapArray[i].partition << " :"<< heapArray[i].value << " index: " << heapArray[i].index<< std::endl;
	}
	std::cout <<"3. for" << std::endl;


	for (int i = K / 2 - 1; i >= 0; i--){
        heapify(heapArray, K, i, comparison, swap);
	}
	
	std::cout << "arr_copied: {";
    for(int o=0; o<size; o++){
        std::cout << arr_copy[o];
        if(o != size-1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;

	std::cout << "Heapified: {";
    for(int o=0; o<K; o++){
        std::cout << heapArray[o].value;
        if(o != K-1) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
	//after finding the minimum element, you should insert a new element from the related partition to the Min Heap
	//read the minimum element in the heap and record it
	//then, replace the minimum element with a new element from the partition that has the last minimum element
	//new element insertion is not a swap operation
	//swap has to be counted only inside the heap or insertion sort
	//then, heapify the current array
	//in case of equality during heapify and insertion sort, do not swap the elements
	//count the comparison and swap between any 2 elements of the array H in both insertion sort and heapify, such as H[i]>H[j]
	//return the total number of kWayMergeSortWithHeap() calls
	int* sortedArray = new int[size];
	int index = 0;
	int min = 0;
	int next_general_index = 0;

	

	while (index < size) {

		min = heapArray[0].value;
		sortedArray[index] = min;
		index++;
		if(heapArray[0].index < size && (heapArray[0].p_last < (size/K)-1)){
			std::cout << "girdi : p_last" << heapArray[0].p_last <<std::endl;
			heapArray[0].p_last = heapArray[0].p_last + 1;
			std::cout << "index: " << heapArray[0].index << std::endl;
			heapArray[0].index = heapArray[0].index + 1;
			next_general_index = heapArray[0].index;
			heapArray[0].value = arr_copy[next_general_index];
		}
		//en sondaki partition bittiğinde
		else{
			heapArray[0].value = INT_MAX;


		}
		std::cout << "HeapArray before Heapified: {";
    	for(int o=0; o<K; o++){
    	    std::cout << heapArray[o].value;
    	    if(o != K-1) std::cout << ", ";
    	}
    	std::cout << "}" << std::endl;
		/*
		for (int i = K / 2 - 1; i >= 0; i--){
		}
		*/
		
		heapify(heapArray, K, 0, comparison, swap);


		std::cout << "HeapArray after Heapified: {";
    	for(int o=0; o<K; o++){
    	    std::cout << heapArray[o].value;
    	    if(o != K-1) std::cout << ", ";
    	}
    	std::cout << "}" << std::endl;
		

		/*
		for (int i = 0; i < size; i++) {

			if ((arr[i] == min)) {

				if(i == (size -1)){
					heapArray[0].value = INT_MAX;
					break;
				}
				else{
					for(int j = 1; j < K; j++){
					if (heapArray[j].value == arr[i+1]) {
						heapArray[0].value = INT_MAX;
						flag = true;
						break;
					}
				}
				if(flag == false){
					iter = i+1;
					while (iter < size){
						if(arr[iter] >= min){
							heapArray[0].value = arr[iter];
							break;
						}
						else{
							iter++;
						}
					}

				}

				}
				
			}

		}
		heapify(heapArray, K, 0, comparison, swap);
		*/
	}

	for (int i = 0; i < size; i++) {
		arr[i] = sortedArray[i];
	}
	return number_of_calls;
}

