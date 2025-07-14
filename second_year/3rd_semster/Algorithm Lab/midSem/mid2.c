#include<stdio.h>
#include<stdlib.h>

int max(int a , int b){
    return a > b ? a : b;
}

int min(int a , int b){
    return a > b ? b : a;
}

int small(int *arr , int left , int right){
    int n = right-left+1;
    if(n == 2){
        if(arr[left] > 0 && arr[right] > 0){
            return arr[left] + arr[right];
        }else{
            return max(arr[left] , arr[right]);
        }
    }else if(n == 3){
        int t = left;
        if(arr[t] > arr[left+1]){
            t = left+1;
        }
        if(arr[t] > arr[right]){
            t = right;
        }
        int m = 0;
        int max = -99999;
        for(int i=left ; i<= right ; i++){
            int withlocal = 0;
            int withoutlocal = 0;
            m=0;
            for(int j=i ; j<=right ; j++){
                withlocal += arr[j];
                if(j != t || m == 0){
                    withoutlocal += arr[j];
                    m++;
                }
                if(max < withlocal){
                    max = withlocal;
                }
                if(max < withoutlocal){
                    max = withoutlocal;
                }
            }
        }
        return max;
    }
}

int meddle(int *arr , int left , int mid ,int right){
    if(left < right){
        int n = right-left+1;

        int i=mid;
        int j=mid+1;
        int maxWithLeftSum = -99999;
        int maxWithRightSum = -99999;
        int maxWithoutLeftSum = -99999;
        int maxWithoutRightSum = -99999;
        int withlocalLeft = 0;
        int withoutlocalLeft = 0;
        int minimum = arr[i];
        int f = 0;
        for(int k = mid-1 ; k>=0 ; k--){
            minimum = min(arr[k] , minimum);
        }
        for(int k = mid ; k >= 0 ; k--){
            withlocalLeft += arr[k];
            if(arr[k] != minimum){
                withoutlocalLeft +=arr[k];
            }else if(arr[k] == minimum && f > 0){ 
                withoutlocalLeft += arr[k];
                f++;
            }else if(arr[k] == minimum){
                f++;
            }
            if(maxWithLeftSum < withlocalLeft){
                maxWithLeftSum = withlocalLeft;
            }
            if(maxWithoutLeftSum < withoutlocalLeft){
                maxWithoutLeftSum = withoutlocalLeft;
            }
        }

        int withlocalRight = 0;
        int withoutlocalRight = 0;
        minimum = arr[j];
        f =0;
        for(int k = j+1 ; k <=right ; k++){
            minimum = min(arr[k] , minimum);
        }
        for(int k = j ; k <= right ; k++){
            withlocalRight += arr[k];
            if(arr[k] != minimum){
                withoutlocalRight +=arr[k];
            }else if(arr[k] == minimum && f > 0){
                withoutlocalRight += arr[k];
            }else if(arr[k] == minimum){
                j++;
            }
            if(maxWithRightSum < withlocalRight){
                maxWithRightSum = withlocalRight;
            }
            if(maxWithoutRightSum < withoutlocalRight){
                maxWithoutRightSum = withoutlocalRight;
            }
        }

        printf("%d %d %d %d",maxWithLeftSum,maxWithoutLeftSum,maxWithRightSum,maxWithoutRightSum);

        return max((maxWithLeftSum + maxWithoutRightSum),max((maxWithRightSum ,maxWithoutLeftSum) , (maxWithLeftSum+maxWithRightSum)));
    }
}

int maxSub(int *arr , int left , int right){
    if(left < right){
        int n = right-left+1;
        if(n == 2 || n == 3){
            return small(arr ,left , right);
        }
        int mid = (left + right)/2;

        int leftSum = maxSub(arr , left , mid);
        int rightSum = maxSub(arr , mid+1 , right);

        int mergeSum = meddle(arr , left , mid , right);

        return max(leftSum , max(rightSum,mergeSum));
    }
    return 0;
}

int main(){
    int n;
    printf("Enter size of array : ");
    scanf("%d",&n);

    int *arr = (int *) calloc (n , sizeof(int));
    printf("Enter elements : ");
    for(int i=0 ; i<n ; i++){
        scanf("%d",&arr[i]);
    }

    int sum = maxSub(arr , 0 , n-1);
    printf("maximum sum = %d",sum);
}