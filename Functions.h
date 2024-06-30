#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Product.h"
#include "Supplier.h"
#include "Supermarket.h"

#define MAX_NAME_LENGTH 255

void replaceSpaces(char* str);
void initProductInfo(Product* product);
Date* initDate();
int isLeapYear(int year);
int isValidDate(Date* date);
char* getStr();

#endif // !_FUNCTIONS_H