#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"


void getDate()
{

}
void getSuperAdress()
{

}
void printSuper()
{

}
void printSuperArr()
{

}
void printSupplier()
{

}
void printSupplierArr()
{

}

void initSuppliers(SupplierManager* suppliers)
{
	suppliers = (SupplierManager*)malloc(sizeof(SupplierManager));
	char choice;
	do
	{
		suppliers->supplierArr = (Supplier*)realloc(suppliers->supplierArr, (suppliers->numOfSuppliers + 1) * sizeof(Supplier));
		if (!suppliers->supplierArr)
		{
			printf("Stop");
		}
		addSupplier(&suppliers->supplierArr[suppliers->numOfSuppliers]);
		suppliers->numOfSuppliers++;
	} while (choice != 'n' && choice != 'N');
}
void initSupers()
{

}