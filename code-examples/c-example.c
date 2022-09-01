/* Examples of C, for CSE4290/6290 */

/* Comments start with / followed immmediately by *, 
 * and end with * followed immediately by /
 * Comments can consist of mutltiple lines.
 * This is the fourth line in the comment.
 * The following line end the comment.
 */

// This is a single line comment. 
// Everything after double /'s is ignored by the compiler.

/* define variables of different types. 
 * varibale names are case sensitive. a is different from A.
 * The size of each type of data type depends on compiler/platform.
 * In CSE4290/6290, we assume the following sizes:
 *  32 bits, words:
 *      int, unsigned, unsigned
 *      long, unsigned long 
 *  16 bits, halfwords:
 *      short, unsigned short 
 *  8 bits, bytes:
 *      char, unsigned char
 * */
long long var_dw;       // a 64-bit signed integer
long	var_longi;	// a 32-bit signed integer
int     var_i;          // a 32-bit signed integer
short   var_i16;        // a 16-bit signed ineger
char    var_i8;         // an 8-bit signed integer (byte)
                        // can represent an ASCII character

unsigned int    var_ui;     // unsigned 32-bit integer 
unsigned short  var_ui16;   // unsigned 16-bit integr 
unsigned char   var_ui8;    // unsigned  8-bit integer 

unsigned int    var_aui[128];   // an array of 128 unsigned words
unsigned char   var_aui8[128];  // an array of 128 bytes 

// function definition
// This function takes two arguments of int, and returns an int
// Note that everything in C has a type
// By RISC-V calling convention, a is in register a0, and b is in register a1.
// In Python, the definition looks like
//  def     my_max(a: int, b: int) -> int:
int     my_max(int a, int b)
{
    /* variables defined in a function
     * are called local variables, or auto variables.
     * They are stored on stack. */
    int     c;

    // if statement, similar to Python
    // Python code would be
    //      if a > b:
    //          c = a
    //      else:
    //          c = b
    if (a > b) {
        c = a;
    } else {
        c = b;
    }

    // return from a function
    return c;
}

/* the function takes an array A and an integer as paramenters and returns an integer 

   Actually, what is passed to the function is not an array, only the starting
   address of an array. It does not matter how many words are in array A. Only
   a word (the address) is passed to the function. 
 
   By RISC-V calling convention, A (the starting address of an array) is in
   register a0, n is in register a1. 

   To read A[0] into register t0, we use the following instruction 

   	lw	t0, 0(a0)

*/
int loops(int A[], int n) {
    
    // define local variables, which will be stored on stack.
    // How many bytes does each of them need? 
    int     arr[128];   // integer array. 128 (32-bit) integers
    int     i;          // integer 
    int     max, sum;  // define multiple variables of the same type

    // for loop
    // initialize i to 0, 
    // while i is less than 10 (this is the condition),  
    // the loop body is executed.
    // After all statements in the loop body are exectued, i is incremented by 1.
    // Then, the condition is checked again.
    for (i = 0; i < 10; i += 1) {
        // arr[i] means element i in the array
	// index starts from 0, like in Python
        arr[i] = i;
    }
    /* In Python, the above code looks like
        for  i in range (10):
            arr[i] = i
    */

    // Similarly, we can access A 
    // In assembly, A's address is in a register and arr's address is
    // also in a register. In this example, A's address is already
    // in a register (passed to the function in a register).
    // Since arr is allocated on the stack, its address can be
    // calculated from sp. 
    for (i = 0; i < 10; i += 1) {
	A[i] = arr[i];
    }

    // while loop
    // similar to Python
    i = 0;
    while (i < 10) {
        arr[i] = arr[i] + 1;
        i ++;  // i ++ means i = i + 1. Similar to i += 1
    }

    max = -1;
    sum = 0;
    // go through first 10 elements in arr.
    // This is a typical loop in C. Again, i ++ means i += 1
    for (i = 0; i < 10; i ++) {
        // calling a function. 
        // Recall my_max takes two arguments of int and returns an int
        max = my_max(t, arr[i]);
        sum += arr[i];
    }

    return 0;
}

/* define a function that takes three paramenters and returns an integer.
   
   Examples of passing arrays to a function.

   a, b, and c are the same, essentially.

   The function gets:
  	the adddress of array a, which is the address of a[0]
	the address of an integer, 
	the address of array c, which is the address of c[0]

   By RISC-V calling convention, 
   	a is in a0
   	b is in a1
   	c is in a2
*/
int     pointers(int a[], int *b, int c[10])
{
    /* define an array of integers.
     
        If arr is located at 0x1000, the adresses of the elements in arr are:
         0x1024: arr[9]
         0x1020: arr[8]
         0x101c: arr[7]
         0x1018: arr[6]
         0x1014: arr[5]
         0x1010: arr[4]
         0x100c: arr[3]
         0x1008: arr[2]
         0x1004: arr[1]
         0x1000: arr[0]
    */
    int arr[10];

    int i;      // if i is located right after arr, i's address is 0x1028

    /* Define a pointer to int.
    A pointer to int === an address of an int
    q is a pointer to an int, or q is the address of an int
    Since we assume 32-bit processors, an address takes 32 bits (or 4 bytes).
    In assembly, q is just a word (4 bytes) . We can use it as the base register
    in load/store instructions. 

    We can keep q in a register, or on stack.
    If it is on the stack, we need to load it into a register before using it.

    */
    int * q;    // let us assume q is kept in register s2

    /* Define another point p. Let us assume p is in register s3.
     * p is not in memory so it does not have an address.
    */
    int * p;

    // save i's address in q 
    q = &i;
    // register s2 should be 0x1028
    // In C, *q, q[0], and i refer to the same word in memory (address 0x1028)

    // save arr[0]'s address in p
    // arr[0] is the first element in the array while &arr[0] is the address of the element
    p = &arr[0];
    // register s3 should be 0x1000
    // In C, *p, p[0], and arr[0] refer to the same word in memory (address 0x1000)

    // Let p point to the next word in the array
    // After the following statement, p is the address of arr[1].
    // In C, the index is scaled
    p = p + 1;      // or p += 1;  or p ++
    // In assembly, we need to scale it ourselves
    //      addi    s3, s3, 4
    //      register s3 should be 0x1004

    // Let p point to arr[3], i.e., let p have the address of arr[3]
    // Note that p is the address of arr[1] currently, we add size of 2 more
    // words to p.
    // Again, the index is scaled in C.
    p += 2;
    // In assembly, we need to scale the offset 2 * 4
    //      addi    s3, s3, 8
    //      register s3 should be 0x100C

    return 0;
}

// define a structure where we can put relevant data together.
// consider it as an object in Python.
struct {
    int     hour;    // Define fields in the structure.
    int     minute; 
    int     second;
}   var_time;

/* 
Once we know the address of a structure, we can calculate its fiels by 

    starting address of the structure + offset of the filed

For example, if the address of var_time is 1000, the address of the 
fields is:

    hour:   1000 + 0  = 1000
    minute: 1000 + 4  = 1004
    second: 1000 + 8  = 1008

In RISC-V, if the address of var_time is in register s0, 
address of fields can be specified as the following:
    hour:      (s0)
    minute:   4(s0)
    second:   8(s0)

One caveat is that we have to consider address alignment when 
calculating the offset of a field.
*/

