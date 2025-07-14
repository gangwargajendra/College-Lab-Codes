import java.util.*;

public class Account {
    int accountNumber;
    String accountType;
    String IFSC;
    float minBalance;
    float availableBalance;
    int customerID;
    String customerName;
    static int totalAccountCreated = 0;

    public Account(){
        this.accountNumber = 0;
        this.accountType = "";
        this.IFSC = "";
        this.minBalance =(float)0.0;
        this.availableBalance = (float)0.0;
        this.customerID = 0;
        this.customerName = "";
        totalAccountCreated++;
    }
    public void setDetails(){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter account Number : ");
        int accountNumber = sc.nextInt();
        this.accountNumber = accountNumber;
        System.out.print("Enter account Type : ");
        String accountType = sc.next();
        this.accountType = accountType;
        System.out.print("Enter IFSC : ");
        String IFSC = sc.next();
        this.IFSC = IFSC;
        System.out.print("Enter CustomerID : ");
        int customerID = sc.nextInt();
        this.customerID = customerID;
        System.out.print("Enter Customer Name : ");
        String customerName = sc.next();
        this.customerName = customerName;
        this.minBalance = 0;
        this.availableBalance = 0;
        this.totalAccountCreated += 1;
    }

    public void getDetails(int accountNumber){
        if(this.accountNumber == accountNumber){
        System.out.println("account Number : "+accountNumber);
        System.out.println("account Type : "+accountType);
        System.out.println("IFSC : "+IFSC);
        System.out.println("minimum Balance : "+minBalance);
        System.out.println("available Balance : "+availableBalance);
        System.out.println("Enter Customer ID : "+customerID);
        System.out.println("Enter Customer Name : "+customerName);
        this.totalAccountCreated += 1;
        }else{
            System.out.println("Account is not present");
        }
    }

    public int getAccountNumber(){
        return this.accountNumber;
    }

    public void updateDetails(int accountNumber){
        if(this.accountNumber == accountNumber){
            Scanner sc = new Scanner(System.in);
            System.out.println("1.Account Type 2.minimum Balance 3.avaible balance 4.customer name");
            System.out.println("Enter choice what you want to update : ");
            int choice = sc.nextInt();
            switch(choice) {
                case 1: System.out.print("Enter new account Type : ");
                        String accountType = sc.next();
                        this.accountType = accountType;
                        break;
                case 2: System.out.print("Enter new minimum balance : ");
                        int minBalance = sc.nextInt();
                        this.minBalance = minBalance;
                        break;
                case 3: System.out.print("Enter new available balance : ");
                        int availableBalance = sc.nextInt();
                        this.availableBalance = availableBalance;
                        break;
                case 4: System.out.print("Enter customer name : ");
                        String customerName = sc.next();
                        this.customerName = customerName;
                        break;
            }
        }else{
            System.out.println("Account not found");
        }
    } 

    public float getBalance(int accountNumber){
        if(this.accountNumber == accountNumber){
            return this.availableBalance;
        }else {
            System.out.println("Account is not present.");
            return (float)0.0;
        }
    }

    public void deposit(int accountNumber, float ammount){
        if(this.accountNumber == accountNumber){
            this.availableBalance += ammount;
        }else {
            System.out.println("Account is not present.");
        }
    }

    public void withdraw(int accountNumber ,float ammount){
        if(this.accountNumber == accountNumber){
            if(this.availableBalance >= ammount+this.minBalance){
                this.availableBalance -= ammount;
            }else{
                System.out.println("money is sufficient to withdraw.");
            }
        }else{
            System.out.println("Account is not present.");
        }
    }

    public static int totalAccount(){
        return totalAccountCreated;
    }

    public void compare(Account account1,Account account2){
        if(account1.availableBalance >= account2.availableBalance){
            account1.getDetails(account1.accountNumber);
        }else{
            account2.getDetails(account2.accountNumber);
        }
    }
}
