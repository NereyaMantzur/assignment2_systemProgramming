#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"

SupplierManager* suppliers;
SupermarketManager* supres;

int main()
{
	supres = (SupermarketManager*)malloc(sizeof(SupermarketManager));
	initSuppliers(suppliers);
	initSupers(supres);
	return 1;
}




