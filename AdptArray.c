#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "AdptArray.h" 
typedef struct AdptArray_ 
{
int ArrSize ; 
PElement* PAdptArray; 
DEL_FUNC delfunc; 
COPY_FUNC copyfunc; 
PRINT_FUNC printfunc; 
} AdptArray; 

PAdptArray CreateAdptArray(COPY_FUNC copyfunc , DEL_FUNC delfunc , PRINT_FUNC  printfunc){
    PAdptArray newArray = (PAdptArray)malloc(sizeof( AdptArray)); 
    if(newArray == NULL)
        return NULL; 
    newArray->ArrSize = 0 ; 
    newArray->copyfunc = copyfunc; 
    newArray->delfunc = delfunc; 
    newArray->printfunc = printfunc;
    newArray->PAdptArray=NULL;  

    return newArray; 
}


Result SetAdptArrayAt(PAdptArray Array, int i, PElement NElement){
    PElement *NElemArr;
    if( Array== NULL){
        return FAIL; 
    } 
    if( i >= Array->ArrSize){
        if( (NElemArr = (PElement* )calloc((i+1), sizeof(PElement)))==NULL)
        return FAIL; 
        
        memcpy(NElemArr, Array->PAdptArray, (Array->ArrSize) * sizeof(PElement)); 
        free(Array->PAdptArray); 
        
        Array->PAdptArray= NElemArr; 
    }
    if(Array->PAdptArray[i]!=NULL){
        Array->delfunc((Array->PAdptArray)[i]); 
    }
    (Array->PAdptArray)[i]= Array->copyfunc(NElement); 
    Array->ArrSize =(i >=Array->ArrSize) ? (i +1) : Array->ArrSize;  
    return SUCCESS; 

}
void DeleteAdptArray(PAdptArray pArray){
    for ( int i=0; i< pArray->ArrSize; i++){
        if(pArray->PAdptArray[i]!=NULL)
        pArray->delfunc(pArray->PAdptArray[i]); 
    }
    free(pArray->PAdptArray); 
    free( pArray); 
}
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if(  idx >= pArr->ArrSize || idx<0 )
        return NULL; 
    
    if( pArr->PAdptArray[idx]==NULL)
        return NULL; 
    
        return (pArr->copyfunc(pArr->PAdptArray[idx])); 
    
}
int GetAdptArraySize(PAdptArray Parr){
    if( Parr==NULL){
        return -1;  
    }
    return Parr->ArrSize;

}
void PrintDB(PAdptArray Adptaraay){
    if(Adptaraay== NULL)
        return; 
    for(int i=0; i<Adptaraay->ArrSize; i++){
        if(Adptaraay->PAdptArray[i]!=NULL)
        Adptaraay->printfunc(Adptaraay->PAdptArray[i]);
        
    }
}



