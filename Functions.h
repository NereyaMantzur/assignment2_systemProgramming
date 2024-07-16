#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Product.h"
#include "Supplier.h"
#include "Supermarket.h"

#define MAX_NAME_LENGTH 255


void q1(SupermarketManager* supermarketManager);
void q2(SupermarketManager* supermarketManager, SupplierManager* supplierManager, ProductManager* productManager);
void q3(SupermarketManager* manager);
void q4(SupermarketManager* manager);
void q5(SupplierManager* manager);
void q6(SupermarketManager* manager);
void q7(SupplierManager* manager);
void q8(SupermarketManager* manager);
void q9(ProductManager* manager);
void q10(ProductManager* manager);
void q11(SupplierManager* manager);
void q12(ProductManager* manager);
void q13(SupplierManager* manager);

void replaceSpaces(char* str);
char* getStr();
void generalArrayFunction(void** arr, int count, int size, int (*func)(void* element));


#endif // !_FUNCTIONS_H