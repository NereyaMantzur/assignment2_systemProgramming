#ifndef PRODUCT_H
#define PRODUCT_H

typedef enum
{
	FOOD, CLEANING, GENERAL
}ProductType;

typedef struct
{
	char* day;
	char* month;
	char* year;

}Date;

typedef struct
{
	char* superMarketNames;
	char* supplierNames;
	const ProductType type;
	const char* productName;
	const int porductCode;
	const Date mfg;
	const Date exp;
}Product;

void addProdcutToSupermarket(const char* pName ,const char* superName);
void deleteProdcutFromSupermarket(const char* pName);
int isProductInSupermarket(const char* pName,const char* pCode,const char* superName);
void doPrintSupermarketWithProductCode();
void doPrintSupermarketWithProductName();
void doPrintSuppliersWithProductCode();
void doPrintSupplierWithProductName();
void doPrintSupplierWithProductCode();
void doPrintProductsWithProductType();
char* isProductType(const int pCode ,const char* pName);
int isProductCode(const char* pName);


#endif // !PRODUCT_H
