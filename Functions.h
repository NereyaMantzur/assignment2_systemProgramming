#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Product.h"
#include "Supplier.h"
#include "Supermarket.h"

#define MAX_NAME_LENGTH 255

void replaceSpaces(char* str);
void initProductInfo(Product* product);
void initProductCode(productInfo* newInfo);
Date* initDate();
int isLeapYear(int year);
int isValidDate(Date* date);
char* getStr();
void generalArrayFunction(void** arr, int count, int size, int (*func)(void* element));


#endif // !_FUNCTIONS_H