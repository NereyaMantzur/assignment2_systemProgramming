#ifndef _SUPPLIER_H
#define _SUPPLIER_H

#define MAX_NAME_LENGTH 255

struct Product;

typedef struct {
	char name[MAX_NAME_LENGTH];
	int code;
	Product** productsArr;
	int numOfProducts;
} Supplier;

typedef struct {
	Supplier** suppliers;
	int numOfSuppliers;
} SupplierManager;

void initSupplierManager(SupplierManager* manager);

void addProdcutToSupplier(Product* add, SupplierManager* manager);

int addSupplier(SupplierManager* manager);
int removeSupplier(SupplierManager* manager, Supplier* delete);
int updateSupplier(SupplierManager* manager, Supplier* update);
Supplier* findSupplierByNameOrCode(SupplierManager* manager, char* str, int code);

int isProductFromSupplier(ProductManager* managar, Supplier* supplier);
int isProductInSupplier(Product* add, SupplierManager* manager);
void deleteProdcutFromSupplier(Product* add, SupplierManager* manager);

void printSupplier(Supplier* supplier);
void printSupplierManager(SupplierManager* manager);

#endif // !_SUPPLIER_H
