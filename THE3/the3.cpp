#include "the3.h"
using namespace std;
/*
you are given an array of sticks with two end points where each end point can be any of the following 3 types:
 Inwards End, Outwards End and Straight End. An illustration for some possible stick instances are given in the figure below.

 Each stick has also "size" property. The size differs from 1 to 10.  The size of each stick is specified in a different input array. Your task is to build the longest path by combining the sticks end to end. The rules of combination are given as follows:
An Inwards end can be combined with an Outwards end only.
An Outwards end can be combined with an Inwards end only.
A Straight end can be combined with another Straight end only.
The path can be started with any type of end. Similarly, it can be finished with any type of end.
While building the path, you should preserve the ordering of the sticks given in the input array. That is; if stick A comes before stick B in the input array, then stick A can not come after stick B in the resulting path.
You do not have to use all the sticks given in the input array.
You should not reverse the sticks. That is, left and right ends of the stick should not be swapped.
In order to obtain the same results with the answer key, please obey the rules given in "Implementation" part.
Please examine the examples below. Note that, each stick is defined with its left and right end types .
 "I" represents Inwards end, "O" represents Outwards end and "S" represents Straight end.
  For instance, ['I', 'S'] represents a stick starting with Inwards end and ending with Straight end.

Example IO:
1) Given array arr = { {'I', 'S'}, {'O', 'I'}, {'S', 'O'} }  and len = {1, 1, 1}:


the longest path is {'I', 'S} + {'S', 'O'}.
return value (i.e. max length) is 2 for each of three functions.
number of  recursive calls is 3.




Implementation:
You will implement three different functions for three different solutions of that problem:
Direct recursive implementation in recursive_sln()
Recursion with memoization in memoization_sln()
Dynamic programming in dp_sln()
All three functions are expected to return the answer to the given problem which is the length of the longest path. Return only the max length value and nothing more.

The number of recursive calls that your recursive function makes should be counted. That number should be stored using the int &number_of_calls variable, which is the last parameter at the definition of the recursive_sln(). Basically, the value of that variable should be incremented by one at each execution of the recursive_sln() function. In order to accomplish that, the increment operation may be done at the first line of the function implementation, as already done in the function template given to you. So, do not change the first line of the recursive_sln() function and do not manipulate the number_of_calls variable at anywhere else.  Do not return that variable. Since it is passed by reference, its final value will be available for testing/grading without returning it. IMPORTANT: In order to obtain the same number_of_calls with the answer key, please use the following recurrence relation:

IF  N == size-1
    M(N) = max{ M(N-1), M(i)+len(N) IF start(N) MATCHES end(i) }
ELSE
    M(N) = max{ M(j) IF end(N) equals to end(j), M(i)+len(N) IF start(N) MATCHES end(i) }
where
    i <= N-1  &&  i > t FOR ALL t start(N) matches end(t)
    j <= N-1  &&  j > t FOR ALL end(N) matches end(t)
   start( x ) MATCHES end( y ) IFF {{start( x ) =='I' && end( y ) =='O} OR {start( x )=='O' && end( y )=='I'} OR {start( x )=='S' && end( y ) =='S'}}
   size is the length of the initial input array, not the length of the current partial array passed to the function.

CAUTION: Please read this recurrence relation carefully. Put break statement(s) into the necessary places of your code to satisfy the above relation exactly. Also, use recurrence upto the last step which is the stopping case to end the recursion, that is: IF  ... THEN return len[0].
*/


/* recurrence relation: IF  N == size-1
    M(N) = max{ M(N-1), M(i)+len(N) IF start(N) MATCHES end(i) }
ELSE
    M(N) = max{ M(j) IF end(N) equals to end(j), M(i)+len(N) IF start(N) MATCHES end(i) }
where
    i <= N-1  &&  i > t FOR ALL t start(N) matches end(t)
    j <= N-1  &&  j > t FOR ALL end(N) matches end(t)
   start( x ) MATCHES end( y ) IFF {{start( x ) =='I' && end( y ) =='O} OR {start( x )=='O' && end( y )=='I'} OR {start( x )=='S' && end( y ) =='S'}}
   size is the length of the initial input array, not the length of the current partial array passed to the function.
   CAUTION: Please read this recurrence relation carefully. Put break statement(s) into the necessary places of your code to satisfy the above relation exactly. Also, use recurrence upto the last step which is the stopping case to end the recursion, that is: IF  ... THEN return len[0].
*/
int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    
    
    number_of_calls+=1;
    
    if (i == 0) {
        return len[0];
    }

    int max= len[i];

    if(number_of_calls== 1){
        for(int t=i-1; t>=0; t--){
            int temp1 = recursive_sln(t,arr,len,number_of_calls);
            max = temp1 > max ? temp1 : max;
        }
        for(int t=i-1; t>=0; t--){
            if((arr[i][0] == 'I' && arr[t][1] == 'O') || 
                (arr[i][0] == 'O' && arr[t][1] == 'I') || 
                (arr[i][0] == 'S' && arr[t][1] == 'S')){
                    int temp2 = recursive_sln(t,arr,len,number_of_calls) + len[i];
                    max = temp2 > max ? temp2 : max;
                    break;
                }                
        }
        
        
    }
    
    else{
        int temp1;
        int temp2;
        for(int t=i-1; t>=0; t--){
            // M(j) IF end(N) equals to end(j)
            if((arr[i][1] ==  arr[t][1])){
                    temp1 = recursive_sln(t,arr,len,number_of_calls);
                    max = temp1 > max ? temp1 : max;
                    break;
                }
        }
        for(int t=i-1; t>=0; t--){
            //M(i)+len(N) IF start(N) MATCHES end(i) 
            if((arr[i][0] == 'I' && arr[t][1] == 'O') || 
                (arr[i][0] == 'O' && arr[t][1] == 'I') || 
                (arr[i][0] == 'S' && arr[t][1] == 'S')){
                    temp2 = recursive_sln(t,arr,len,number_of_calls) + len[i] ;
                    max = temp2 > max ? temp2 : max;
                    break;
                }
        }
    }   
    

    return max;

    
}

    




int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

    /*
    For memoization and dynamic programming, you should use int**& mem variable (i.e. array), which is the last parameter at definitions of those functions, as the array of memoized values. For both memoization_sln() and dp_sln() functions, final values in the mem variable will be considered for grading. Note that it is a 2D array. Each inner array is structered as an array of size 3 representing the stick combination ending with an Inwards end, Outwards end and Straight end, respectively. While testing and grading, all the inner arrays of mem array will be initialized to all -1's. So, while implementing your functions, you can assume that mem is an array of array of -1's. Do not return that variable/array.
    */
   
    if(i == -1){
        return 0;
    } 
    int max = memoization_sln(i-1, arr, len, mem);
    int k;
    if(i == 0){
        if(arr[i][1] == 'I'){
                mem[i][0] = len[i];
                mem[i][1] = 0;
                mem[i][2] = 0;
            }
            else if( arr[i][1] == 'O'){
                mem[i][1] = len[i];
                mem[i][0] = 0;
                mem[i][2] = 0;
                
            }
            else if( arr[i][1] == 'S'){
                mem[i][2] = len[i];
                mem[i][0] = 0;
                mem[i][1] = 0;
            }
            return len[0];

    }
    k= i;
    if(arr[k][0] == 'I'){
            mem[k][0] = mem[k-1][0];
            mem[k][1] = mem[k-1][1];
            mem[k][2] = mem[k-1][2];
            if(arr[k][1] == 'I'){
                int temp;
                temp = mem[k-1][1] + len[k];
                if(mem[k-1][0] >= temp){
                    mem[k][0] = mem[k-1][0];
                }
                else{
                    mem[k][0] = temp;
                }
            }
            else if(arr[k][1]== 'O'){
                int temp;
                temp= mem[k-1][1] + len[k];
                if(mem[k-1][1] >= temp){
                    mem[k][1] = mem[k-1][1];
                }
                else{
                    mem[k][1] = temp;
                }
                
            }
            else if(arr[k][1] == 'S'){
                int temp;
                temp = mem[k-1][1] + len[k];
                if(mem[k-1][2] >= temp){
                    mem[k][2] = mem[k-1][2];
                }
                else{
                    mem[k][2] = temp;
                }
            }
        }
        else if(arr[k][0] == 'O'){
            mem[k][0] = mem[k-1][0];
            mem[k][1] = mem[k-1][1];
            mem[k][2] = mem[k-1][2];
             if(arr[k][1] == 'I'){
                // gereksiz comparison
                int temp;
                temp = mem[k-1][0] + len[k];
                if(mem[k-1][0] >= temp){
                    mem[k][0] = mem[k-1][0];
                }
                else{
                    mem[k][0] = temp;
                }
             }
             else if(arr[k][1]== 'O'){
                int temp;
                temp = mem[k-1][0] + len[k];
                if(mem[k-1][1] >= temp){
                    mem[k][1] = mem[k-1][1];
                }
                else{
                    mem[k][1] = temp;
                }

             }
             else if(arr[k][1] == 'S'){
                int temp;
                temp = mem[k-1][0] + len[k];
                if(mem[k-1][2] >= temp){
                    mem[k][2] = mem[k-1][2];
                }
                else{
                    mem[k][2] = temp;
                }
             }

        }
        else if(arr[k][0] == 'S'){
            mem[k][0] = mem[k-1][0];
            mem[k][1] = mem[k-1][1];
            mem[k][2] = mem[k-1][2];
            if(arr[k][1]== 'I'){
                int temp;
                temp = mem[k-1][2] + len[k];
                if(mem[k-1][0] >= temp){
                    mem[k][0] = mem[k-1][0];
                }
                else{
                    mem[k][0] = temp;
                }
            }
            else if(arr[k][1]== 'O'){
                int temp;
                temp = mem[k-1][2] + len[k];
                if(mem[k-1][1] >= temp){
                    mem[k][1] = mem[k-1][1];
                }
                else{
                    mem[k][1] = temp;
                }
            }
            else if(arr[k][1] == 'S'){
                int temp;
                temp = mem[k-1][2] + len[k];
                if(mem[k-1][2] >= temp){
                    mem[k][2] = mem[k-1][2];
                }
                else{
                    mem[k][2] = temp;
                }
            }
        }
        
        

        


    if(mem[k][0] > mem[k][1] && mem[k][0] > mem[k][2]){
        return mem[k][0];
    } 
    if(mem[k][1] > mem[k][2]){
        return mem[k][1];
    }
    return mem[k][2];   
    
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming
    int max = 0;

    for(int i=0; i<size; i++){
        // for the first case
        if(i==0){
            if(arr[i][1] == 'I'){
                mem[i][0] = len[i];
                mem[i][1] = 0;
                mem[i][2] = 0;
            }
            else if( arr[i][1] == 'O'){
                mem[i][1] = len[i];
                mem[i][0] = 0;
                mem[i][2] = 0;
                
            }
            else if( arr[i][1] == 'S'){
                mem[i][2] = len[i];
                mem[i][0] = 0;
                mem[i][1] = 0;
            }
        
        }
        else if(arr[i][0] == 'I'){
            mem[i][0] = mem[i-1][0];
            mem[i][1] = mem[i-1][1];
            mem[i][2] = mem[i-1][2];
            if(arr[i][1] == 'I'){
                int temp;
                temp = mem[i-1][1] + len[i];
                if(mem[i-1][0] >= temp){
                    mem[i][0] = mem[i-1][0];
                }
                else{
                    mem[i][0] = temp;
                }
            }
            else if(arr[i][1]== 'O'){
                int temp;
                temp= mem[i-1][1] + len[i];
                if(mem[i-1][1] >= temp){
                    mem[i][1] = mem[i-1][1];
                }
                else{
                    mem[i][1] = temp;
                }
                
            }
            else if(arr[i][1] == 'S'){
                int temp;
                temp = mem[i-1][1] + len[i];
                if(mem[i-1][2] >= temp){
                    mem[i][2] = mem[i-1][2];
                }
                else{
                    mem[i][2] = temp;
                }
            }
        }
        else if(arr[i][0] == 'O'){
            mem[i][0] = mem[i-1][0];
            mem[i][1] = mem[i-1][1];
            mem[i][2] = mem[i-1][2];
             if(arr[i][1] == 'I'){
                // gereksiz comparison
                int temp;
                temp = mem[i-1][0] + len[i];
                if(mem[i-1][0] >= temp){
                    mem[i][0] = mem[i-1][0];
                }
                else{
                    mem[i][0] = temp;
                }
             }
             else if(arr[i][1]== 'O'){
                int temp;
                temp = mem[i-1][0] + len[i];
                if(mem[i-1][1] >= temp){
                    mem[i][1] = mem[i-1][1];
                }
                else{
                    mem[i][1] = temp;
                }

             }
             else if(arr[i][1] == 'S'){
                int temp;
                temp = mem[i-1][0] + len[i];
                if(mem[i-1][2] >= temp){
                    mem[i][2] = mem[i-1][2];
                }
                else{
                    mem[i][2] = temp;
                }
             }

        }
        else if(arr[i][0] == 'S'){
            mem[i][0] = mem[i-1][0];
            mem[i][1] = mem[i-1][1];
            mem[i][2] = mem[i-1][2];
            if(arr[i][1]== 'I'){
                int temp;
                temp = mem[i-1][2] + len[i];
                if(mem[i-1][0] >= temp){
                    mem[i][0] = mem[i-1][0];
                }
                else{
                    mem[i][0] = temp;
                }
            }
            else if(arr[i][1]== 'O'){
                int temp;
                temp = mem[i-1][2] + len[i];
                if(mem[i-1][1] >= temp){
                    mem[i][1] = mem[i-1][1];
                }
                else{
                    mem[i][1] = temp;
                }
            }
            else if(arr[i][1] == 'S'){
                int temp;
                temp = mem[i-1][2] + len[i];
                if(mem[i-1][2] >= temp){
                    mem[i][2] = mem[i-1][2];
                }
                else{
                    mem[i][2] = temp;
                }
            }
        }
        
        
        
        
    }
 
   if (mem[size-1][0]>mem[size-1][1] && mem[size-1][0]>mem[size-1][2]) {
      max = mem[size-1][0];
   } else if (mem[size-1][1]>mem[size-1][2]) {
      max = mem[size-1][1];
   } else {
      max = mem[size-1][2];
   }
   
    return max;
}

