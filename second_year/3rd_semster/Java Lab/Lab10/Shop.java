import java.util.*;

class ItemNotFound extends Exception {
    public String toString(){
        return "Item doesn't exit.";
    }
}

class OverBudget extends Exception {
    public String toString(){
        return "Doesn't have enough money.";
    }
}

class ItemLimit extends Exception {
    public String toString(){
        return "desired item is more then limit.";
    }
}

class OutofStock extends Exception {
    public String toString(){
        return "item are less then desired.";
    }
}

class Items {
    int itemCode;
    String itemName;
    double unitPrice;
    int stockRemaining;
    int itemLimit;

    public Items(int itemCode, String itemName, double unitPrice,
     int stockRemaining, int itemLimit){
        this.itemCode = itemCode;
        this.itemName = itemName;
        this.unitPrice = unitPrice;
        this.stockRemaining = stockRemaining;
        this.itemLimit = itemLimit;
    }

    public String toString(){
        return "itemCode = " + itemCode + " itemName = " + itemName +
         " unitPrice = " + unitPrice + " stockRemaining : "
          + stockRemaining + " itemLimit = " + itemLimit;
    }
}

class User{
    String name;
    double budget;

    public User(String name , double budget){
        this.name = name;
        this.budget = budget;
    }
}

public class Shop {
    public static void buy(int x,int y, User user, Items []item) throws ItemNotFound,OverBudget,ItemLimit,OutofStock {
        if(x <= 0 || x > 4){
            throw new ItemNotFound();
        }

        if(user.budget < item[x-1].unitPrice * y){
            throw new OverBudget();
        }

        if(y > item[x-1].itemLimit){
            throw new ItemLimit();
        }

        if(y > item[x-1].stockRemaining){
            throw new OutofStock();
        }

        item[x-1].stockRemaining -= y;
        user.budget -= item[x-1].unitPrice * y; 
        System.out.println("User purchased "+ y + item[x-1].itemName);
    } 

    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);    

        Items[] items = new Items[4];

        items[0] = new Items(1, "TV" ,10000 , 3, 2);
        items[1] = new Items(2, "Mouse", 1000 ,7 , 3);
        items[2] = new Items(3, "HeadPhone" ,2000 ,1 ,6);
        items[3] = new Items(4, "Mobile" ,5000 ,5 ,1);

        System.out.print("Enter User name : ");
        String userName = sc.nextLine();
        System.out.print("Enter User budget : ");
        double userBudget = sc.nextDouble();

        User user = new User(userName , userBudget);

        boolean t = true;
        while(t){
            System.out.println("1.Display Items 2.Buy Item 3.Exit");
            System.out.print("Enter you choice : ");
            int choice = sc.nextInt();
            switch(choice) {
                case 1:
                    for(int i=0 ; i<4 ; i++){
                        System.out.println(items[i]);
                    }
                    break;
                case 2:
                    System.out.print("Enter which item you wnat to buy and how much : ");
                    int x = sc.nextInt();
                    int y = sc.nextInt();
                    try {
                        buy(x, y, user ,items);
                    }catch(Exception e){
                        System.out.println("Exception : " + e);
                    }
                    break;
                case 3:
                    System.out.println("Thank you.");
                    t = false;
                    break;
            }
        }
    }
}