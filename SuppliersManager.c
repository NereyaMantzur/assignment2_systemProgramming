#include <stdio.h>
#include <stdlib.h>

#include "SuppliersManager.h"

void addSupplier(Supplier* supplier)
{
    fputs("please enter supplier name\n", stdout);
    fgets(supplier->supplierName, 255, stdin);

}
void removeSupplier(Supplier* supplier)
{

}
void updateSupplier(Supplier* supplier)
{

}
Supplier* findSupplierByNameOrCode()
{
    Supplier* s = (Supplier*)malloc(sizeof(Supplier));
    if (s == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }	
	return s;
}