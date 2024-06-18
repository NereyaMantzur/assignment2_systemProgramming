#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "Product.h"

typedef struct
{
	char* supplierName;
	int supplierCode;

}Supplier;

void addProdcutToSupplier(Product *productPtr , char* supplierStr);
void deleteProdcutFromSupplier(Product* productPtr);
int isProductInSupplier(char* productStr , int productCode);
int isProductFromSupplier(char* productStr, int productCode , char* supplierStr);


#endif // !SUPPLIER_H