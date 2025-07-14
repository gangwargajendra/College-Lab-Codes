class BankAccount {
    private double balance;

    public BankAccount(double initialBalance) {
        this.balance = initialBalance;
    }

    // Synchronized method to ensure thread safety during withdrawal
    public synchronized void withdraw(double amount) {
        if (balance >= amount) {
            System.out.println(Thread.currentThread().getName() + " is withdrawing " + amount);
            balance -= amount;
            System.out.println("New Balance: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " attempted to withdraw " + amount + " but insufficient balance.");
        }
    }

    public double getBalance() {
        return balance;
    }
}

// Custom thread class for performing withdrawals
class WithdrawalThread extends Thread {
    private BankAccount account;
    private double amount;

    public WithdrawalThread(BankAccount account, double amount) {
        this.account = account;
        this.amount = amount;
    }

    @Override
    public void run() {
        account.withdraw(amount);  // Withdraw the specified amount
    }
}

// Main class to initiate the threads
public class BankTransaction {
    public static void main(String[] args) {
        BankAccount account = new BankAccount(1000);  // Shared bank account with initial balance

        // Creating threads for multiple withdrawals
        WithdrawalThread t1 = new WithdrawalThread(account, 700);
        WithdrawalThread t2 = new WithdrawalThread(account, 500);
        WithdrawalThread t3 = new WithdrawalThread(account, 300);

        // Assigning names to threads for identification
        t1.setName("Thread 1");
        t2.setName("Thread 2");
        t3.setName("Thread 3");

        // Start the threads
        t1.start();
        t2.start();
        t3.start();
    }
}