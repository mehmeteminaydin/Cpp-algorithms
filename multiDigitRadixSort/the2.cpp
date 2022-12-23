#include "the2.h"
#include <cmath>



// helper function to find the maximum element in an array
int findMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max){
            max = arr[i];
        }
    return max;
}
 
// helper function for counting sort implementation
void countingSort(int* arr, int n, int exp, int groupSize, bool ascending, long& numberOfIterations)
{

    int output[n]; // output array
    int i;
    long my_exp = pow(10,groupSize);
    int *count{ new int[my_exp]{} };

    // initilize the count array with zero
    for (i = 0; i < my_exp; i++){
        count[i] = 0;
    }
 
    // store the number of counts
    for (i = 0; i < n; i++){
        numberOfIterations++;
        count[(arr[i] / exp) % my_exp]++;
    }
    
    // kümülatif olarak arrayi doldur
    if(ascending){
        for (int i = 1; i < my_exp; i++){
            numberOfIterations++;
            count[i] += count[i - 1];
        }
    }
    else{
        for (int i = my_exp-1; i > 0; i--){
            numberOfIterations++;
            count[i-1] += count[i];
        }
            
    }
    
 
    // building the array
    for (i = n - 1; i >= 0; i--) {
        numberOfIterations++;
        output[count[(arr[i] / exp) % my_exp] - 1] = arr[i];
        count[(arr[i] / exp) % my_exp]--;
    }

    // copying the output array
    for (i = 0; i < n; i++){
        numberOfIterations++;
        arr[i] = output[i];
    }

    
    //delete count array
    delete[] count;
    
}
 

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){

    long numberOfIterations = 0;
    int m = findMax(arr, arraySize);
    int kalan = maxDigitLength%groupSize;

    for (int exp = 1; m / exp > 0; exp *= pow(10, groupSize))
    
        // if last iteration, use kalan
        if(m / exp < pow(10, groupSize)){
            countingSort(arr, arraySize, exp, kalan, ascending, numberOfIterations);

        }
        else{
            countingSort(arr, arraySize, exp, groupSize, ascending, numberOfIterations);
        }

    return numberOfIterations;
}