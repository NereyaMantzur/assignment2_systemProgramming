#include <string.h>
#include <string.h>
#include <ctype.h>

#include "Supermarket.h"

int isSameSuprmarket(SuperMarket* super1Ptr, SuperMarket* super2Ptr)
{
	return strcmp(super1Ptr->superName, super2Ptr->superName) == 0;;

}
int isSupermarketName(SuperMarket* superPtr, char* superStr)
{
	return strcmp(superPtr->superName , superPtr);

}
int isSupermarketCode(SuperMarket* superPtr, int superCode)
{
	return 1;
}


// Function Implementations

int isSameSuperMarket(SuperMarket* super1Ptr, SuperMarket* super2Ptr) {
    // Check if Input is Null
    if (super1Ptr == NULL || super2Ptr == NULL) {
        return 0; 
    }
    // compare names
    if (strcmp(super1Ptr->name, super2Ptr->name) == 0) {
        return 1; 
    } else {
        return 0; 
    }
}


int isSupermarketName(SuperMarket* superPtr, const char* superStr) {
    if (superPtr == NULL || superStr == NULL) {
        return 0; 
    }
    if (strcmp(superPtr->name, superStr) == 0) {
        return 1; 
    } else {
        return 0; 
    }
}


int isSupermarketCode(SuperMarket* superPtr, int superCode) {
    if (superPtr == NULL) {
        return 0; 
    }
    if (superPtr->code == superCode) {
        return 1; 
    } else {
        return 0; 
    }
}
