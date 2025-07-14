import java.util.Scanner;

public class Ques2{
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		System.out.println("Enter Size of array : ");
		int size = sc.nextInt();
		int []arr = new int[size];
		int i , j = 0;
		System.out.println("Enter the element of array : ");
		for(i = 0 ; i < size ; i++){
			arr[i] = sc.nextInt();
		}
		int fre = 0;
		int k = 0;
		int []dup = new int[size];
		System.out.print("repeated element : ");
		for(i = 0 ; i < size ; i++){
			fre = 0;
			for(j = 0 ; j < size ; j++){
				if(arr[i] == arr[j]){
					fre++;
				}
			}
			int m , y = 0;
			for(m = 0 ; m < k ; m++){
				if(arr[i] == dup[m]){
					y = 1;
				}
			}
			if(fre > 1 && y == 0){
				dup[k++] = arr[i];
				j = 1;
				System.out.print(" " + arr[i]);
			}
		}
		if(k == 0){
			System.out.println("None");
		}
		
		System.out.println("\nSorted array : ");
		
		int flag = 0;

    		for(i = 0 ; i < size-1 ; i++){
        		for(j = 0 ; j < size-i-1 ; j++){
           			 if(arr[j] > arr[j+1]){
               			 int t = arr[j];
				 arr[j] = arr[j+1];
				 arr[j+1] = t;
                		 flag = 1;
          		  	}
        		}
       			 if(flag == 0){
           		 break;
       			 }
   		 }
		for(i = 0; i < size ; i++){
			System.out.print(" " + arr[i]);
		}
	}
}
