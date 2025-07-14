import java.util.*;

public class Demo{
    public static void main(String ...args){
        Boolean b = true;
        Bank Ba = null;
        while(b){
            System.out.println("1.for Account creation.");
            System.out.println("2.add Interest.");
            System.out.println("3.display.");
            System.out.println("4.Exit.");
            System.out.print("Enter your choice : ");
            int choice;
            Scanner sc = new Scanner(System.in);
            choice = sc.nextInt();
            switch(choice){
                case 1:
                    System.out.println("Enter type of Account te create(SBI, PNB or BOI) : ");
		    sc.nextLine();
                    String ty = sc.nextLine();
                    System.out.print("Enter local balance of this account : ");
                    double balance = sc.nextDouble();
                    if(ty.equals("SBI")){
                        Ba = new SBI(balance);
                    }else if(ty.equals("PNB")){
                        Ba = new PNB(balance);
                    }else if(ty.equals("BOI")){
                        Ba = new BOI(balance);
                    }
                    break;
                case 2:
		    Ba.addInterest();
                    break;
                case 3:
		    if(Ba != null){
                    	Ba.display();
		    }
                    break;
                case 4:
                    b = false;
                    break;
            }
        }
    }
}
    
