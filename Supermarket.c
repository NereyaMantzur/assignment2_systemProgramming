#include <string.h>

#include "Supermarket.h"

int isSameSuprmarket(SuperMarket* super1Ptr, SuperMarket* super2Ptr)
{
	return 1;

}
int isSupermarketName(SuperMarket* superPtr, char* superStr)
{
	return 1;

}
int isSupermarketCode(SuperMarket* superPtr, int superCode)
{
	return 1;
}

// Check edit by Simon 

// Function Implementations
int isSameSupermarket(Supermarket* s1, Supermarket* s2) {
    return strcmp(s1->name, s2->name) == 0;
}

int isSupermarketName(Supermarket* s, const char* name) {
    return strcmp(s->name, name) == 0;
}

int isSupermarketCode(Supermarket* s, int code) {
    return s->code == code;
}
