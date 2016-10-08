#include<stdio.h> //this is safe cuz stdio should also have a guard


//multi include guard
#ifndef _mylib_h
#define _mylib_h


//Forward declaration
int foo(int a);

#endif
