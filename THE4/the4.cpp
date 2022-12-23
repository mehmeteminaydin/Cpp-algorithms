#include "the4.h"


int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming

    int i, j;

    //for the clearity, I used name row as iterator
    int row;
    int sum = 0;
    for(i=0; i<=ncol1; i++){
        for(j = 0; j <= ncol2; j++){
            // m[0][0] must be 0
            if(i == 0 && j == 0){
                mem[i][j] = 0;
            }
            // construct the the first row of the mem
            else if(i == 0){
                sum = 0;
                for(row=0; row<nrow; row++){
                    //since we can only insert, to create box2
                    //  find the sum of the columns of box2
                    if(arr2[row][j-1] != '-'){
                        sum++;
                    }
                }

                mem[i][j] = mem[i][j-1] +sum;
            }
            // construct the first column of the mem
            else if(j == 0){
                sum = 0;
                for(row = 0; row < nrow; row++){
                    if(arr1[row][i-1] != '-'){
                        sum++;
                    }
                }

                mem[i][j] = mem[i-1][j]+sum;
            }
            else{
                /*
                Motivation: we want to find the minimum cost of transforming box1 to box2
                 we can either insert, delete, or replace or reorder
                it is clear to see that the flow of the dp system is from left to right and top to bottom
                 so we will use the previous values (left, upper left, top) to find the current value 
                while coming from left -> insertion
                from top -> deletion
                from upper left -> replacement or reordering
                */
                sum = 0;

                int insertions = 0, deletions = 0, replacements = 0, orderings= 10000000;
                
                // count the number of insertions
                for(row = 0; row < nrow; row++){

                    if(arr2[row][j-1] != '-'){
                        insertions++;
                    }
                }
                // count the number of deletions
                for(row = 0; row < nrow; row++){
                    if(arr1[row][i-1] != '-'){
                        deletions++;
                    }
                }
                
            
                // in order to determine whether we can reorder or not
                // we need to check if the columns have the same elements

                // motivation: first sort the columns and then compare them
                // if they are equal, then we can reorder
                
                char temp1[nrow];
                char temp2[nrow];
                //deep copy of arr1 and arr2
                for (row= 0; row<nrow; row++)
                    temp1[row] = arr1[row][i-1];

                for (row= 0; row<nrow; row++)
                    temp2[row] = arr2[row][j-1];

                // sort temp1 which is arr1
                for (int step = 0; step < nrow - 1; step++) {
                    int min_idx = step;
                    for (int k = step + 1; k < nrow; k++) {

                    if (temp1[k] < temp1[min_idx])
                        min_idx = k;
                    }

                    int temp = temp1[min_idx];
                    temp1[min_idx] = temp1[step];
                    temp1[step] = temp;

                }
                // sort temp2 which is arr2

                for (int step = 0; step < nrow - 1; step++) {
                    int min_idx = step;
                    for (int k = step + 1; k < nrow; k++) {

                    if (temp2[k] < temp2[min_idx])
                        min_idx = k;
                    }
                    // swap
                    int temp = temp2[min_idx];
                    temp2[min_idx] = temp2[step];
                    temp2[step] = temp;
                }
                // now we have sorted temp1 and temp2
                // we can compare them
                int flag = true;
                for(row = 0; row < nrow; row++){
                    if(temp1[row] != temp2[row]){
                        flag = false;
                        break;
                    }
                }

                // if they have same elements, then we can reorder
                if(flag){
                    orderings = 0;
                    for(row = 0; row < nrow; row++){
                        if(arr1[row][i-1] != arr2[row][j-1]){
                            orderings++;
                        }
                    }
                }
                
                
                // count the number of replacements
                for(row = 0; row < nrow; row++){
                    if(arr1[row][i-1] != arr2[row][j-1]){
                        if(arr1[row][i-1] == '-' || arr2[row][j-1] == '-'){
                            replacements = replacements + 2;
                        }
                        else{
                            replacements++;
                        }
                    }
                }
                
                sum = replacements;

                if(flag)
                    sum = std::min(sum, orderings);
                
                int myMin = std::min(mem[i-1][j-1] + sum, mem[i-1][j] + deletions);
                myMin = std::min(myMin, mem[i][j-1] + insertions);
    
                mem[i][j] = myMin;
            }
        }
    }

    return mem[i-1][j-1];
}

