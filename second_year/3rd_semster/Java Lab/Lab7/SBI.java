import java.util.*;

public class SBI extends Bank{
    static double rateOfInterest = 3.5;
    double localBalance;

    public void display(){
        super.display();
        System.out.println("rate of Interest : "+rateOfInterest + " & local Balnace : "+localBalance);
    }

    public void Addinterest(){
        double Interest =  (rateOfInterest * this.localBalance) / 100;
        localBalance += Interest;
        totalBalance += Interest; 
    }

    public SBI(double localBalance){
        this.localBalance = localBalance;
        totalBalance += localBalance;
    }
}