#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"

SupplierManager* suppliers;
SuperMarketManager* supres;

int main()
{
	suppliers = (SupplierManager*)malloc(sizeof(SupplierManager));
	supres = (SuperMarketManager*)malloc(sizeof(SuperMarketManager));
	initSuppliers(suppliers);
	initSupers(supres);
	return 1;
}




