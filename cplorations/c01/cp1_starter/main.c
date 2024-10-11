/****************************************
 * C-ploration 1 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Function: add
 * -------------
 * calculates the sum from 0..N. 
 *   e.g., add(5) => 15
 *  
 * n:   number we're adding up to
 *
 * returns: sum of values 1 to N
 */
int add(int n)
{
    // accumulator variable -> 0
    int sum = 0;

    // loop from 0 to n
    for (int i = 0; i <= n; i++){
        
        sum += i;
    }
    // return the sum
    return sum;
     
}   


/* Function: fib
 * -------------
 * calculates the Nth Fibonacci number using recursion. 
 *   e.g., fib(10) => 55
 *
 * n: the Fibonacci number to calculate
 *
 * returns: Nth Fibonacci number
 */
int fib(int n)
{
    // fib equation: f(n) = f(n-1) + f(n-2)

    // variables that store fib(n-1), fib(n), fib(n+1)
    int fib0 = 0;
    int fib1 = 1;
    int fibCurrent;

    // base case for n = 0, 1
    if (n <= 1){

        return n;
    }

    // for loop 
    for (int i = 2; i <= n; i++)
    {
        fibCurrent = fib0 + fib1;
        fib0 = fib1;
        fib1 = fibCurrent;
    }

    // returns fib(n)
    return fibCurrent;
}
 
 
/* Function: max
 * -------------
 * find the largest value in an array. 
 *   e.g., max([1,3,2,5,4], 5) => 5
 *
 * arr: array of integers 
 * n:   size of arr
 *
 * returns: largest value in arr
 */
int max(int arr[], int n)
{
    // variable to store highest number, store size of array, store current value
    int current;

    int max = 0;


    // loop and if statement checking current value of the array against the 
    // variable max (holds the current highest value of the array)
    for (int i = 0; i < n; i++)
    {
        current = arr[i];

        if (max < current)
        {
            max = current;
        }
    }
    // return variable
    return max;
    
}

/* Function: sum
 * -------------
 * calculates the sum of values in an array. 
 *   e.g., sum([1,3,2,5,4], 5) => 15
 *
 * arr: array of integers
 * n:   size of arr
 *
 * returns: sum of values in arr
 */
int sum(int arr[], int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + arr[i]; 
    }

    return sum;
}


/* Function: pie
 * -------------
 * estimate PI using Leibniz formula.
 *   e.g. pie(5) => 3.339683
 *
 * Leibniz formula
 *     π/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...
 *  
 * n: number of terms to use in Leibniz formula
 *
 */
double pie(long int n){
    //initialize a variable that will be returned
    double sum = 0;


    //loop that adds next term of Leibniz's formula to sum
    for (int i = 0; i < n; i++)
    {
        sum += pow(-1, i)/((2*i)+1);
    }

    //return the sum of the formula multiplied by 4 to get PI
    return 4*sum;
} 


/* Function: main
 * -------------
 * parses command line arguments and executes appropriate function.
 *
 * =========================
 * DO NOT EDIT MAIN FUNCTION
 * =========================
 *
 * usage:
 *  -add N            : sum 0..N
 *  -fib N            : find Nth Fibonacci
 *  -max X1 X2 ... XN : largest value in array [X1, X2, ..., XN]
 *  -sum X1 X2 ... XN : add values in array [X1, X2, ..., XN] 
 *  -pie N            : estimate PI using N terms
 * 
 * argc: number of arguments
 * argv: array of arguments (array of array of chars)
 *
 * returns: 0 if no errors, 1 otherwise.
 */
int main(int argc, char** argv)
{
    // note: argv[0] is always the function name; in this case "main"
    //   thus, the first argument will be argv[1]
    if (argc < 3){
        // generate error: we require at least two arguments
        fprintf(stderr, "[error] Insufficient arguments.\n");
        return -1;
    }
    
    if (argv[1][0] != '-'){
        // generate error: we require a command that starts with hyphen
        fprintf(stderr, "[error] Unknown command %s. Did you forget '-'?\n", argv[1]);
        return -1;
    }
    
    // put remaining args into int array
    int offset = 2;
    int n = argc - offset;
    int* arr = malloc((n)*sizeof(int)); 
    for(int j=offset; j<argc; j++)
        arr[j-offset] = atoi(argv[j]);
        
    if (!strcmp(argv[1], "-add")){ 
        // find the sum of 1..N 
        int result = add(arr[0]);
        printf("Sum of 1 to %d is %d.\n", arr[0], result);
    }else if (!strcmp(argv[1], "-fib")){ 
        // find the Nth Fibonacci number
        int result = fib(arr[0]);
        printf("Fibonacci of %d is %d.\n", arr[0], result);
    }else if (!strcmp(argv[1], "-sum")){ 
        // find the sum of the arguments
        int total = sum(arr, n);
        printf("Sum of the numbers is %d.\n", total);
    }else if (!strcmp(argv[1], "-max")){
        // find the largest number of the arguments
        int biggest = max(arr, n);
        printf("Largest number is %d.\n", biggest);
    }else if (!strcmp(argv[1], "-pie")){ 
        // approximate PI with Leibniz
        double pie_result = pie(arr[0]);
        printf("PI(e) is %.6f.\n", pie_result);
    }else{
        // incorrect command, exit with error
        fprintf(stderr, "[error] Unknown command %s.\n", argv[1]);
        return 1;
    }
    return 0;
}