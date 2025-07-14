#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct pair Pair;
struct pair{
    int x,y;
};

double min(double a ,double b){
    return a > b ? b : a;
}

int compareX(const void *a, const void *b){
    Pair *p1 = (Pair *)a, *p2 = (Pair *)b;
    return p1->x - p2->x;
}

void print(Pair *arr ,int n){
    printf("pairs : ");
    for(int i=0 ; i < n ; i++){
        printf("(%d,%d),",arr[i].x,arr[i].y);
    }
    printf("\n");
}

double distance(Pair a , Pair b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double small(Pair *Px , int left, int right){
    double dis = 0.0;
    for(int i = 0 ; i < right-left+1 ;i++){
        for(int j = i+1 ; j < right-left+1 ; j++){
            double d = distance(Px[i],Px[j]);
            if(dis > d){
                dis = d;
            }
        }
    }
    return dis;
}

double closest(Pair *P,int left , int right){
    if(right-left+1 <= 3){
        return small(P,left ,right);
    }
    int median = (right-left+1) / 2;
    Pair med = P[median];
    double dl = closest(P ,left , median);
    double dr = closest(P,median+1 ,right);

    double d = min(dl ,dr);
    int j=0;
    Pair *strip = (Pair *) calloc (right-left+1 , sizeof(Pair));
    for(int i=0 ; i<right-left+1 ; i++){
        if(i <= median && d > (med.x-P[i].x) ){
            strip[j++] = P[i];
        }else if(i > median && d > (P[i].x-med.x)){
            strip[j++] = P[i];
        }
    }
    double minStrip = d;
    for(int i=0 ; i<j ; i++){
        for(int k=i+1 ; k<j ; k++){
            double dis = distance(strip[i],strip[k]);
            if(dis < minStrip){
                minStrip = dis;
            }
        }
    }
    return min(d ,minStrip);
}

int main(){
    int n;
    printf("Enter no of pair : ");
    scanf("%d",&n);
    Pair *arr = (Pair *) calloc (n , sizeof(Pair));
    int i;
    for(i=0 ; i<n ; i++){
        // printf("Enter %dth pair : ",i+1);
        scanf("%d",&arr[i].x);
        scanf("%d",&arr[i].y);
    }
    
    qsort(arr , n, sizeof(Pair) ,compareX);
    print(arr ,n);
    
    printf("closest distance : %lf",closest(arr,0 ,n-1));

    return 0;
}