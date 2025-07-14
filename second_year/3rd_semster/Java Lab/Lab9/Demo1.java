import java.util.*;

abstract class Employee {
    String name;
    float salary;

    public abstract double calculateBonus();

    public String toString(){
        return ("name : "+name+" & slalary : "+salary);
    }

    public Employee(String name ,float salary){
        this.name = name;
        this.salary = salary;
    }
}

class Manager extends Employee {
    public Manager(String name , float salary){
        super(name ,salary);
    } 

    public double calculateBonus(){
        salary += salary * .20; 
        return salary;
    }

    public String toString(){
        return super.toString();
    }
}

class Developer extends Employee {
    public Developer(String name , float salary){
        super(name ,salary);
    }

    public double calculateBonus(){
        salary += salary * .10;
        return salary;
    }

    public String toString(){
        return super.toString();
    }
}

public class Demo1{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);

        String name ;
        double salary;
        System.out.print("Enter manager name : ");
        name = sc.nextLine();
        System.out.print("Enter manager salary : ");
        salary = sc.nextDouble();
        Manager m1 = new Manager(name , (float)salary);
        m1.calculateBonus(); 

        System.out.println(m1);
        
        System.out.print("Enter developer name : ");
        sc.nextLine();
        name = sc.nextLine();
        System.out.print("Enter developer salary : ");
        salary = sc.nextDouble();
        Developer d1 = new Developer(name , (float)salary);
        d1.calculateBonus();
        System.out.print(d1);
    }
}