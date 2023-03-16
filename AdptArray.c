
#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>

struct AdptArray_ {
    PElement* elements;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray arr = (PAdptArray)malloc(sizeof(struct AdptArray_));
    arr->elements = NULL;
    arr->size = 0;
    arr->copyFunc = copyFunc;
    arr->delFunc = delFunc;
    arr->printFunc = printFunc;
    return arr;
}

void DeleteAdptArray(PAdptArray arr) {
    if (!arr) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        if (arr->elements[i]!=NULL) {
            arr->delFunc(arr->elements[i]);
        }
    }
    free(arr->elements);

        free(arr);
    
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement element) {
    if (!arr) {
        return FAIL;
    }
    if (index < 0) {
        return FAIL;
    }

    if (index >= arr->size) {
        // Need to resize the array
        int newSize = index + 1;
        
        PElement* newElements = (PElement*)realloc(arr->elements, newSize * sizeof(PElement));
        if (!newElements) {
            return FAIL;
        }
    // Need to initialize any empty slots
        for (int i = arr->size; i < newSize; i++) {
            newElements[i] = NULL;
        }
        arr->elements = newElements;
        arr->size = newSize;

    }
        
    // Need to delete the old element

    if (arr->elements[index] != NULL) {
        arr->delFunc(arr->elements[index]);
    }
    
    // Copy the element into the array

    arr->elements[index] = arr->copyFunc(element);

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int index) {

    if (!arr) {
        return NULL;
    }
    if (index < 0 || index >= arr->size) {
        return NULL;
    }
    if (arr->elements[index]==NULL) {
        return NULL;
    }
    
    return arr->copyFunc(arr->elements[index]);

}

int GetAdptArraySize(PAdptArray arr) {
    if (!arr) {
        return 0;
    }
    return arr->size;
}

void PrintDB(PAdptArray arr) {
    if (!arr) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        if (arr->elements[i]) {
            arr->printFunc(arr->elements[i]);
 
    }
}
}
