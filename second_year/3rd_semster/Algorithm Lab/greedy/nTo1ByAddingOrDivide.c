#include<stdio.h>

// when only devision by 2 and incrementation is allowed
int findMinStep(int n){
    int minStep = 0;
    while(n > 1){
        if(n % 2 == 0){
            n /= 2;
            minStep++;
        }else{
            n -= 1;
            minStep++;
        }
    }
    return minStep;
}

// when 

// int min(int a, int b){
//     return a > b ? b : a;
// }

// int findMinStep(int N) 
// 	{ 
// 	    if(N==1)
// 	    return 0;
// 	    int a=99999,b=99999, c=99999;
// 	    if(N%2==0)
// 	    a=1+findMinStep(N/2);
// 	    if(N%3==0)
// 	    b=1+findMinStep(N/3);
// 	    c=1+findMinStep(N-1);
// 	    return min(a,min(b,c));
	    
// 	} 

int main(){
    int n;
    printf("Enter the number : ");
    scanf("%d",&n);

    int minStep = findMinStep(n);

    printf("minimum steps to reach from %d to 1 : %d",n,minStep);
}