/*
    Data Types Size:
    int - 4 bytes
    char - 1 byte
    float - 4 bytes

A pointer is a variable that stores the address of another variable
*/
#include<stdio.h>

int main(){

    // First block. Pointer basic usage
    int a;
    int *p;
    p = &a; // Where &a means "Address of a"
    printf("p as type int = %d \n", p); // Trying to show an address as an integer
    printf("p as type p = %p \n", p); // Showing an address as its corresponding data type
    printf("*p as type int = %d \n", *p); // *p - Value at the address pointed by p


    //Second block. Proper variable initialization
    int b = 10;
    p = &b; // Where &b means "Address of b"
    printf("p as type p = %p \n", p); // Showing an address as its corresponding data type
    printf("*p as type int = %d \n", *p); // *p - Value at the address pointed by p
    printf("p as type int = %d \n", p);
    printf("&b as type int = %d \n", &b);


    //Third block. Dereferencing
    *p = 16;
    printf("*p = %d \n", *p); // *p - Value at the address pointed by p
    printf("b = %d \n", b);


    // Fourth block. Pointer logic
    printf("Value stored in p = %d \n", *p); // *p - Value at the address pointed by p
    printf("Address of p = %p \n", p); 

    int c = 20;
    *p = c; // Question: Will the address stored in *p now point to where c is stored?

    printf("Value stored in p = %d \n", *p); // *p - Value at the address pointed by p
    printf("Address of p = %p \n", p); 


    // Fifth block. Syntax hijinks
    int *q = &c;
    int* r = &c; //Question: Which of these will work? Neither? Both?

    printf("Value stored in address pointed at by q = %d \n", *q);
    printf("Value stored in address pointed at by r = %d \n", *r);

    printf("Address stored in q = %p \n", q);
    printf("Address stored in r = %p \n", r);


    // Sixth block. Pointer arithmetic
    int d = 14;
    int *w = &d;

    printf("Value stored in the address pointed at by w = %d \n", *w);
    printf("Arithmetic through the pointer: Adding 1 = %d \n", *w + 1); //What will this be?
    printf("%d \n", w );
    printf("%d \n", w + 1); //What will this be and why?

    printf("%p \n", w );
    printf("%p \n", w + 1); //What will this be and why?

    printf ("Size of integer is %d bytes \n", (int)sizeof(int));

    printf ("Value at address w + 1: %d \n", *(w+1));
    return 0;

    // Seventh block. Pointer types

    /*
        Pointers are strongly typed. Which means a pointer to a variable has to be
        the same data type of the variable it is pointing to.
        int* -> int
        char* -> char

        Why would this matter if the pointer always stores an address?
        Why not have one generic type?
        Discuss.

        The answer is something already showcased: Dereferencing!
        Dereference allows us to access and modify the data saved in the address to which the pointer points.
        Each data type differs on how they store information.

        For example int a = 1025
        
        byte3   byte2  byte1    byte0 (Least significat byte)
        00000000 00000000 00000100 00000001
        Memory blocks:
        0x...203    0x...202    0x...201    0x200
        Leftmost byte is sign byte (to indicate negative or positive integer)
        So...
        Printing p -> 0x...200
        Dereferencing (Printing *p, the value) -> Compiler looks at 4 bytes starting at 0x...200

        What would happen if p was a char*?
    */



}
