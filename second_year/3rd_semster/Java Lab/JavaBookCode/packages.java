package mypack.hello;

import javax.swing.plaf.basic.BasicLabelUI;

class Balance {
    String name;
    double bal;
    Balance(String n , double b){
        name = n;
        bal = b;
    }

    void show(){
        if(bal < 0) {
            System.out.println("---->");
        }
        System.out.println(name + " : $ " + bal);
    }
}

public class packages {
    public static void main(String[] args) {
        Balance current[] =  new Balance[3];

        current[0] = new Balance("k j ", 123.230);
        current[1] = new Balance("will", 157.020);
        current[2] = new Balance("Tom", -12.330);

        for(int i=0 ; i<3 ; i++) current[i].show();
    }
}
