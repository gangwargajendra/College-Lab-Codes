import java.util.*;

public class Demo{
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter num of accounts : ");
        int n = sc.nextInt();
        Account []arr = new Account[n];
        for(int i = 0 ; i < n ; i++){
            System.out.println("Enter details for "+(i+1)+"th account : ");
            arr[i] = new Account();
            arr[i].setDetails();
        }
        int choice = 1;
        while(choice > 0){
            System.out.println("1.Update Details 2.Get Details 3.Deposit 4.Withdraw 5.Exit");
            System.out.println("Enter choice : ");
            choice  = sc.nextInt();
            switch(choice) {
                case 1 : System.out.println("Enter account number to update details : ");
                        int acc = sc.nextInt();
                        for(int i = 0 ; i < n ; i++){
                            if(arr[i].getAccountNumber() == acc){
                                arr[i].updateDetails(acc);
                                break;
                            }else if(i == n-1){
                                arr[i].updateDetails(acc);
                            }
                        }
                        break;
                case 2 : System.out.println("Enter account number to get details : ");
                        acc = sc.nextInt();
                        for(int i = 0 ; i < n ; i++){
                            if(arr[i].getAccountNumber() == acc){
                                arr[i].getDetails(acc);
                                break;
                            }else if(i == n-1){
                                arr[i].getDetails(acc);
                            }
                        }
                        break;
                case 3 : System.out.println("Enter account number to deposit ammount : ");
                        acc = sc.nextInt();
                        System.out.println("Enter ammount to deposit : ");
                        int ammount = sc.nextInt();
                        for(int i = 0 ; i < n ; i++){
                            if(arr[i].getAccountNumber() == acc){
                                arr[i].deposit(acc,ammount);
                                break;
                            }else if(i == n-1){
                                arr[i].deposit(acc,ammount);
                            }
                        }
                        break;
                case 4 : System.out.println("Enter account number to withdraw ammount : ");
                        acc = sc.nextInt();
                        System.out.println("Enter ammount to withdraw : ");
                        ammount = sc.nextInt();
                        for(int i = 0 ; i < n ; i++){
                            if(arr[i].getAccountNumber() == acc){
                                arr[i].withdraw(acc,ammount);
                                break;
                            }else if(i == n-1){
                                arr[i].withdraw(acc,ammount);
                            }
                        }
                        break;
                case 5 :
                        choice = 0;
                        break;
            }
        }
    }
}