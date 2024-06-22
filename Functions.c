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
			fputs("please enter supplier name\n", stdout);
			fgets(suppliers->supplierArr[suppliers->numOfSuppliers]->supplierName, 255, stdin);
			fputs("please enter supplier code\n", stdout);
			scanf_s(" %d", suppliers->supplierArr[suppliers->numOfSuppliers]->supplierCode);
			addSupplier(suppliers->supplierArr[suppliers->numOfSuppliers]);
			suppliers->numOfSuppliers++;
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
void initSupers()
{

}