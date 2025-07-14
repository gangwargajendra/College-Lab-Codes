import java.util.*;

public class BOI extends Bank{
    static double rateOfInterest = 5;
    double localBalance;

    public void display(){
        super.display();
        System.out.println("rate of Interest : "+rateOfInterest + " & local Balnace : "+localBalance);
    }

    public void Addinterest(){
        double Interest =  (rateOfInterest * localBalance) / 100;
        localBalance += Interest;
        totalBalance += Interest; 
    }

    public BOI(double localBalance){
        this.localBalance = localBalance;
        totalBalance += localBalance;
    }
}