#ifndef _PRODUCT_H
#define _PRODUCT_H


#define MAX_NAME 255
typedef enum
{
	FOOD = 1, CLEANING, GENERAL
}Type;

typedef enum Sortion
{
	NOT_SORTED, BY_NAME, BY_CODE, BY_TYPE
}Sortion;

typedef struct
{
	Type* type;
	char productName[MAX_NAME];
	int productCode;
}productInfo;

typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct {
	char** nameOfSupers;
	int numOfSupers;
	char* supplier;
	productInfo* specs;
	Date* mfg;
	Date* exp;
} Product;

typedef struct {
	Product** productArr;
	int numOfProducts;
	Sortion isSorted;
} ProductManager;

void initProductManager(ProductManager* manager);
Product* addProduct(ProductManager* manager);
void deleteProdcutFromSupermarket(Product* product, char* delete);
void doPrintSupermarketWithProductCode(ProductManager* manager);
void doPrintSupermarketWithProductName(ProductManager* manager);
void doPrintSupplierWithProductCode(ProductManager* manager);
void doPrintSupplierWithProductName(ProductManager* manager);
void doPrintProductsWithProductType(ProductManager* manager);
Product* findProductByIndex(ProductManager* manager, int index);

int isProductType(ProductManager* manager);
int isProductCode(ProductManager* manager);

void printProduct(Product* product);
void printProductManager(ProductManager* manager);
void sortProductArr(ProductManager* manager);

#endif // !_PRODUCT_H