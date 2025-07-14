import java.util.*;

abstract class Shape{
    String name;
    int noSides;

    public abstract double getArea();

    public abstract double getPerimeter();

    public String toString(){
        return "name = " + name + ", noSides = "+noSides; 
    }
}

class Circle extends Shape{
    int radius;

    public Circle(int r){
        this.radius = r;
        this.noSides = 0;
        this.name ="Circle";
    }

    public double getArea(){
        double area = 3.14 * radius * radius;
        return area;
    }

    public double getPerimeter(){
        double peri = 2 * 3.14 * radius;
        return peri;
    }
}

class Rectangle extends Shape{
    int length;
    int breadth;

    public Rectangle(int l , int b){
        this.length = l;
        this.breadth = b;
        this.noSides = 4;
        this.name = "Rectangle";
    }

    public double getArea(){
        double area = length * breadth;
        return area;
    }

    public double getPerimeter(){
        double peri = 2 * (length + breadth);
        return peri;
    }
}

public class Demo {
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the radius of circle : ");
        int ra = sc.nextInt();

        Circle c1 = new Circle(ra);
        String s2 = c1.toString();
        System.out.println(s2);
	System.out.print(" Area = " + c1.getArea());	
	System.out.println(" paremeter =  "+c1.getPerimeter());

        System.out.print("Enter length : ");
        int l = sc.nextInt();
        System.out.print("Enter breadth : ");
        int b = sc.nextInt();

        Rectangle r1 = new Rectangle(l,b);
        String s4 = r1.toString();
        System.out.println(s4);
	System.out.print("Area = " + r1.getArea());	
	System.out.print(" paremeter =  "+r1.getPerimeter());

    }
}