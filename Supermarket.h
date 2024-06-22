#ifndef SUPERMARKET_H
#define SUPERMARKET_H

typedef struct
{
	char name[50];
	const char* superName;
	const char* superAdress;
	const int superCode;

}SuperMarket;

int isSameSuprmarket(SuperMarket *super1Ptr, SuperMarket *super2Ptr);
int isSupermarketName(SuperMarket *superPtr , char * superStr);
int isSupermarketCode(SuperMarket *superPtr , int superCode);


#endif // !SUPERMARKET_H
