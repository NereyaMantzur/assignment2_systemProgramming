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

void initSuppliers(SupplierManager *suppliers)
{
		char choice;
	do
	{
		fputs("Do you want to add a supplier? y/n \n", stdout);
		choice = getchar();
		getchar();
		switch (choice)
		{
		case 'Y':
		case 'y':
			suppliers->supplierArr = (Supplier*)realloc(suppliers->supplierArr, suppliers->numOfSuppliers + 1);
			Supplier* newSupplier = (Supplier*)malloc(sizeof(Supplier));
			fputs("please enter supplier name\n", stdout);
			fgets(newSupplier->supplierName, 255, stdin);
			fputs("please enter supplier code\n", stdout);
			scanf_s(" %d", &newSupplier->supplierName);
			addSupplier(newSupplier);
			break;
		case 'N':
		case 'n':
			fputs("ok bye!\n", stdout);
			break;
		default:
			puts("oy lo\n");
			break;
		}
	} while (choice != 'n' && choice != 'N');
}
void initSupers(SuperMarketManager *supers)
{

}