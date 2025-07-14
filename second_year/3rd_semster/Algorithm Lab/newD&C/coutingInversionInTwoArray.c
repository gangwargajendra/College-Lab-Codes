#include<stdio.h>
#include<stdlib.h>

int mergeAndCount(int *a1, int *a2, int n1 , int n2){
    int inversion = 0;
    int j=0,k=0;
    // for(int i=0 ; i<n2 ; i++){
    //     while(j < n1){
    //         if(a2[i] < a1[j]){
    //             inversion += n1-j ;
    //             break;
    //         }else{
    //             j++;
    //         }
    //     }
    // }
    int *mergeArray = (int *) calloc(n1+n2 , sizeof(int));
    int t=0;
    while(k < n1 && j < n2){
        if(a1[k] > a2[j]){
            inversion += n1-k;
            mergeArray[t++] = a2[j];
            j++;
        }else{
            mergeArray[t++] = a1[k];
            k++;
        }
    }
    // left last elements

    return inversion;
}

int main(){
    int n1 , n2;
    printf("Enter the size of both array : ");
    scanf("%d %d",&n1,&n2);

    int a1[n1],a2[n2];
    for(int i=0 ; i<n1 ;i++){
        scanf("%d",&a1[i]);
    }
    for(int i=0 ; i<n2 ; i++){
        scanf("%d",&a2[i]);
    }

    int inve = mergeAndCount(a1 , a2 , n1 , n2);
    printf("no of inversion : %d",inve);
    return 0;
}