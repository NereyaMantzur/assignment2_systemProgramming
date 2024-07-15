#ifndef _SUPPLIER_H
#define _SUPPLIER_H

#define MAX_NAME_LENGTH 255


typedef struct {
	char name[MAX_NAME_LENGTH];
	int code;
	Product** productsArr;
	int numOfProducts;
} Supplier;

typedef struct SupplierManager {
	Supplier** suppliers;
	int numOfSuppliers;
} SupplierManager;

void initSupplierManager(char* fName, SupplierManager* manager);

void addProductToSupplier(Product* add, SupplierManager* manager);

int addSupplier(SupplierManager* manager);
int removeSupplier(SupplierManager* manager, Supplier* delete);
int updateSupplier(SupplierManager* manager, Supplier* update);
Supplier* findSupplierByNameOrCode(SupplierManager* manager, char* str, int code);

int isProductFromSupplier(SupplierManager* managar, Product* product);
int isProductInSupplier(Product* add, SupplierManager* manager);
void deleteProdcutFromSupplier(Product* add, SupplierManager* manager);

int printSupplier(Supplier* supplier);
void printSupplierManager(SupplierManager* manager);
int writeSupplierToText(char* fName, int count, SupplierManager* manager);
Supplier** readSupplierfromText(char* fName, SupplierManager* manager);



#endif // !_SUPPLIER_H
