import java.util.Scanner;

abstract class Bank {
    double totalBalance = 0;

    public void display() {
        System.out.println("Total balance = " + totalBalance);
    }

    public abstract void addInterest();
}

class BOI extends Bank {
    double rateOfinterest = 5;
    double localBalance;

    public void display() {
        super.display();
        System.out.println("Rate of Interest: " + rateOfinterest + " & Local Balance: " + localBalance);
    }

    public void addInterest() {
        double interest = (rateOfinterest * localBalance) / 100;
        localBalance += interest;
        totalBalance += interest;
    }

    public BOI(double localBalance) {
        this.localBalance = localBalance;
        totalBalance += localBalance;
    }
}

class PNB extends Bank {
    double rateOfinterest = 4;
    double localBalance;

    public void display() {
        super.display();
        System.out.println("Rate of Interest: " + rateOfinterest + " & Local Balance: " + localBalance);
    }

    public void addInterest() {
        double interest = (rateOfinterest * localBalance) / 100;
        localBalance += interest;
        totalBalance += interest;
    }

    public PNB(double localBalance) {
        this.localBalance = localBalance;
        totalBalance += localBalance;
    }
}

class SBI extends Bank {
    double rateOfinterest = 3.5;
    double localBalance;

    public void display() {
        super.display();
        System.out.println("Rate of Interest: " + rateOfinterest + " & Local Balance: " + localBalance);
    }

    public void addInterest() {
        double interest = (rateOfinterest * localBalance) / 100;
        localBalance += interest;
        totalBalance += interest;
    }

    public SBI(double localBalance) {
        this.localBalance = localBalance;
        totalBalance += localBalance;
    }
}

public class Demo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Bank account = null;

        boolean t = true;
        while (t) {
            System.out.println("1. Create Account");
            System.out.println("2. Add Interest");
            System.out.println("3. Display");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            
            int choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1:
                    System.out.println("Enter type of Account to create (SBI, PNB, BOI): ");
                    String type = sc.nextLine();
                    System.out.print("Enter local balance of this account: ");
                    double balance = sc.nextDouble();

                    switch (type) {
                        case "SBI":
                            account = new SBI(balance);
                            break;
                        case "PNB":
                            account = new PNB(balance);
                            break;
                        case "BOI":
                            account = new BOI(balance);
                            break;
                    }
                    break;
                case 2:
                    if (account != null) {
                        account.addInterest();
                    }
                    break;
                case 3:
                    if (account != null) {
                        account.display();
                    }
                    break;
                case 4:
                    t = false;
                    break;
            }
        }
    }
}