#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"


#define SUPPLIER_TEXT "suppliers.txt"

int main() {
	SupermarketManager supermarketManager;
	SupplierManager supplierManager;
	ProductManager productManager;

	initSupermarketManager(&supermarketManager);
	initSupplierManager(SUPPLIER_TEXT, &supplierManager);
	initProductManager(&productManager,&supplierManager);

	int choice;
	do {
		printf("\nMain Menu\n");
		printf("1.  Add a supermarket \n");
		printf("2.  Add a product to supplier or supermarket\n");
		printf("3.  print supermarket products\n");
		printf("4.  print all supermarkets \n");
		printf("5.  Print all products of a supplier\n");
		printf("6.  Print all products of a specific type in supermarkets\n");
		printf("7.  Print all products of a specific type in suppliers\n");
		printf("8.  Print products by type in a specific supermarket\n");
		/*        

		     ↓ assignment Number 3 ↓

		*/
		printf("9.  sort products by chosen rule\n");
		printf("10. print all products \n");
		printf("11. print all suppliers \n");
		printf("12. search product by (name/code)\n");
		printf("13. Exit\n");


		printf("Enter your choice: ");
		scanf(" %d", &choice);
		getchar();
		switch (choice) {
		case 1:
			q1(&supermarketManager);
			break;
		case 2:
			q2(&supermarketManager, &supplierManager, &productManager);
			break;
		case 3:
			q3(&supermarketManager);
			break;
		case 4:
			q4(&supermarketManager);
			break;
		case 5:
			q5(&supplierManager);
			break;
		case 6:
			q6(&supermarketManager);
			break;
		case 7:
			q7(&supplierManager);
			break;
		case 8:
			q8(&supermarketManager);
			break;
		case 9:
			q9(&productManager);
			break;
		case 10:
			q10(&productManager);
			break;
		case 11:
			q11(&supplierManager);
			break;
		case 12:
			q12(&productManager);
			break;
		case 13:
			printf("Exiting the program.\n");
			break;
		default:
			printf("Invalid choice. Please enter a number between 1 and 13.\n");
		}
		writeSupplierToText(SUPPLIER_TEXT, supplierManager.numOfSuppliers, &supplierManager);
	} while (choice != 13);

	return 0;
}