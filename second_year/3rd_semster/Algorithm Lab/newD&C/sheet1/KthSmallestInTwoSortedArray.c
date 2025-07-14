#include<stdio.h>
#include<stdlib.h>

int min(int a , int b){
    return a > b ? b : a;
}

int Kthsmallest(int *a , int *b , int n1, int n2 ,int k){
    if(n1 == 0){
        return b[k-1];
    }
    if(n2 == 0){
        return a[k-1];
    }
    if(k == 1){
        return min(a[0] , b[0]);
    }

    int i = min(n1 , k/2);
    int j = min(n2 , k/2);

    if(a[i-1] > b[j-1]){
        return Kthsmallest(a , b+j , n1 , n2-j ,k-j);
    }else{
        return Kthsmallest(a+i , b , n1-i , n2 , k-i);
    }
}

int main(){
    int n1 , n2 , k;
    printf("Enter the size of both array and k: ");
    scanf("%d %d %d",&n1,&n2,&k);

    int a1[n1],a2[n2];
    for(int i=0 ; i<n1 ;i++){
        scanf("%d",&a1[i]);
    }
    for(int i=0 ; i<n2 ; i++){
        scanf("%d",&a2[i]);
    }
    int inve = Kthsmallest(a1 , a2 , n1 , n2 , k);
    printf("%dth smallest : %d\n",k,inve);
    return 0;
}