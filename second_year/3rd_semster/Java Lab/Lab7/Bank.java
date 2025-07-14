import java.util.*;

abstract class Bank{
    static double totalBalance = 0;
    
    public void display(){
        System.out.println("Total balance = "+ totalBalance);
    }

   	public abstract void addInterest();
}