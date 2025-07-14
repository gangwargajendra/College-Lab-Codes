#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct pair Pair;
struct pair{
    int x;
    int y;
};
double min(double a ,double b){
    return a > b ? b : a;
}

void print(Pair *arr ,int n){
    printf("pairs : ");
    for(int i=0 ; i < n ; i++){
        printf("(%d,%d),",arr[i].x,arr[i].y);
    }
    printf("\n");
}


void sorting(Pair *arr , int n,int k){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n - i -1 ; j++){
            if(k == 0){
                if(arr[j].x > arr[j+1].x){
                    int x1 = arr[j].x;
                    int y1 = arr[j].y;
                    arr[j].x = arr[j+1].x;
                    arr[j].y = arr[j+1].y;
                    arr[j+1].x = x1;
                    arr[j+1].y = y1;
                }
            }else if(k == 1){
                if(arr[j].y > arr[j+1].y){
                    int x1 = arr[j].x;
                    int y1 = arr[j].y;
                    arr[j].x = arr[j+1].x;
                    arr[j].y = arr[j+1].y;
                    arr[j+1].x = x1;
                    arr[j+1].y = y1;
            }
            }
        }
    }
}



float distance(Pair a , Pair b){
    int m = (a.x-b.x)*(a.x-b.x);
    int n = (a.y-b.y)*(a.y-b.y);
    float d = sqrt(m+n);
    return d;
}

float small(Pair *Px , int left, int right){
    int size = right-left+1;
    float minDis = 9999.99;
    for(int i = 0 ; i < size-1 ;i++){
        for(int j = i+1 ; j < size ; j++){
            float d = distance(Px[i],Px[j]);
            if(minDis > d){
                minDis = d;
            }
        }
    }
    return minDis;
}

float closestPair(Pair *Px , Pair *Py,int left ,int right){
    int size = right-left+1;
    if(size <= 3){
        return small(Px , left , right);
    }
    int median = size / 2 ;
    int m = 0;
    Pair *Qx = (Pair *) calloc (median+1 , sizeof(Pair));
    for(int i = left ; i <= median ; i++){
        Qx[m++] = Px[i];
    }
    m = 0;
    Pair *Rx = (Pair *) calloc (size-median-1 ,sizeof(Pair));
    for(int i=median+1 ; i <= right ;i++){
        Rx[m++] = Px[i];
    }
    Pair *Qy = (Pair *) calloc(median+1 ,sizeof(Pair));
    Pair *Ry = (Pair *) calloc(size-median-1 , sizeof(Pair));
    int n = 0;
    m = 0;
    for(int i = left ; i <= right ; i++){
        if(Py[i].x <= Px[median].x){
            Qy[m++] = Py[i];
        }else{
            Ry[n++] = Py[i];
        }
    }
    float dq = closestPair(Qx ,Qy,0 , median);
    float dr = closestPair(Rx ,Ry,0,size-median-2);
    float d = min(dq,dr);
    Pair *Sy = (Pair *) calloc (size , sizeof(Pair));
    m = 0 ,n =0;
    int j=0;
    while(m < size){
        int dis = (Px[median].x - Py[m].x);
        if(dis < 0){
            if(d > (-1 * dis)){
                Sy[j++] = Py[m];
            }
        }else{
            if(d > dis){
                Sy[j++] = Py[m];
            }
        }
        m++;
    }
    float minDis = 9999;
    for(int i = 0 ; i < j-1 ; i++){
        for(int k = i+1 ; k < i+7 ; k++){
            if((Sy[k].y - Sy[i].y) > d){
                break;
            }
            float dis = distance(Sy[k] , Sy[i]);
            if(dis < minDis){
                minDis = dis;
            }
        }
    }
    return min(minDis , d);
}

int main(){
    int n;
    printf("Enter no of pair : "); // 2 3  10 30 40 50 5 1 12 10 3 4
    scanf("%d",&n);
    Pair *arr1 = (Pair *) calloc (n , sizeof(Pair));
    Pair *arr2 = (Pair *) calloc (n , sizeof(Pair));
    int i;
    for(i=0 ; i<n ; i++){
        // printf("Enter %dth pair : ",i+1);
        scanf("%d",&arr1[i].x);
        scanf("%d",&arr1[i].y);
        arr2[i].x = arr1[i].x;
        arr2[i].y = arr1[i].y;    
    }
    sorting(arr1,n,0);
    print(arr1,n);
    sorting(arr2,n,1);
    print(arr2, n);
    printf("distance = %f",closestPair(arr1,arr2,0,n-1));
    return 0;
}