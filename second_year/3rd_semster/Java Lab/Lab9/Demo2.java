import java.util.*;

interface Payment {
    boolean processPayment(double amount);
    void paymentDetails();
}

class CreditCard implements Payment {
    public String cardNumber;
    public String cardHolderName;
    public double balance;

    public CreditCard(String cardNumber, String cardHolderName, double balance) {
        this.cardNumber = cardNumber;
        this.cardHolderName = cardHolderName;
        this.balance = balance;
    }

    public boolean processPayment(double amount) {
        if (amount > 0 && amount <= balance) {
            balance = balance - amount;
            return true;
        }
        return false;
    }

    public void paymentDetails() {
        System.out.println("Card Number : " + cardNumber);
        System.out.println("Card Holder Name : " + cardHolderName);
        System.out.println("Balance : " + balance);
    }
}

class UPI implements Payment {
    public String upiId;
    public String bankName;
    public double balance;

    public UPI(String upiId, String bankName, double balance) {
        this.upiId = upiId;
        this.bankName = bankName;
        this.balance = balance;
    }

    public boolean processPayment(double amount) {
        if (amount > 0 && amount <= balance) {
            balance = balance - amount;
            return true;
        }
        return false;
    }

    public void paymentDetails() {
        System.out.println("UPI ID : " + upiId);
        System.out.println("Bank Name : " + bankName);
        System.out.println("Balance : " + balance);
    }
}

public class Demo2 {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Credit card detail : ");
        System.out.print("Enter card number : ");
        String cardNumber = sc.nextLine();
        System.out.print("Enter card holder name : ");
        String cardHolderName = sc.nextLine();
        System.out.print("Enter balance : ");
        double balancecre = sc.nextDouble();
        
        sc.nextLine();
        System.out.print("Enter UPI detail : ");
        System.out.print("Enter UPI ID : ");
        String upiId = sc.nextLine();
        System.out.print("Enter bank name : ");
        String bankName = sc.nextLine();
        System.out.print("Enter balance : ");
        double balanceupi = sc.nextDouble();


        CreditCard c1 = new CreditCard(cardNumber , cardHolderName ,balancecre);
        UPI u1 = new UPI(upiId,bankName,balanceupi);
        
        double deduction;
        System.out.print("Enter amount for deduction in credit card : ");
        deduction = sc.nextDouble();

        boolean reCre = c1.processPayment(deduction);
        System.out.println("Credit Card payment is : " + reCre);
        c1.paymentDetails();

        System.out.print("Enter amount for deduction in UPI : ");
        deduction = sc.nextDouble();

        boolean reU = u1.processPayment(deduction);
        System.out.println("UPI Payment is : " + reU);
        u1.paymentDetails();
    }
}
