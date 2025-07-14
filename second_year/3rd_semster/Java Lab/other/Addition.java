import java.util.Scanner;

public class Addition {

    public int add() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the first number: ");
        int a = sc.nextInt();
        System.out.print("Enter the second number: ");
        int b = sc.nextInt();
        return a + b;
    }

    public int add(int a, int b) {
        return a + b;
    }

    public int add(int a, int b, int c) {
        return a + b + c;
    }

    public static void main(String []args) {
        System.out.println("with no argument : ");
        Addition  a1 = new Addition();
        System.out.println("Addition : " + a1.add());
        
        System.out.println("with two argument : ");
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the first number: ");
        int a = sc.nextInt();
        System.out.print("Enter the second number: ");
        int b = sc.nextInt();
        System.out.println("Addition : " + a1.add(a, b));

        System.out.println("with three argument : ");
        System.out.print("Enter the first number: ");
        a = sc.nextInt();
        System.out.print("Enter the second number: ");
        b = sc.nextInt();
        System.out.print("Enter the third number: ");
        int c = sc.nextInt();
        System.out.println("Addition : " + a1.add(a, b, c));
    }
}
