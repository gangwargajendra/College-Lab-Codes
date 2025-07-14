import java.util.*;

public class Faculty {
    String name;
    int emplD;

    public Faculty() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the name of faculty : ");
        String name = sc.nextLine();
        this.name = name;
        System.out.print("Enter the empID of faculty : ");
        int emplD = sc.nextInt();
        this.emplD = emplD;
    }
    
    public String toString() {
        System.out.println("Faculty's name : " + name);
        System.out.println("Faculty's empID " + emplD);
        return "Faculty Name: " + name + ", Employee ID: " + emplD;
    }
}