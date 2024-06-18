#ifndef SUPPLIERMANAGER_H
#define SUPPLIERMANAGER_H

#include "Supplier.h"

typedef struct
{
	Supplier* supplierArr[1];
	int numOfSuppliers;

}SupplierManager;

void addSupplier(Supplier* supplier);
void removeSupplier(Supplier* supplier);
void updateSupplier(Supplier* supplier);
Supplier* findSupplierByNameOrCode(char* supplierStr,int supplierCode);


#endif // !SUPPLIERMANAGER_H