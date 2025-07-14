import java.util.*;

class Shape {
    double getArea(){
        return 0.0;
    }
}

class Rectangle extends Shape {
    double width;
    double height;

    public Rectangle(double width, double height){
        this.width = width;
        this.height = height;
    }

    double getArea(){
        return width * height;
    }
}

public class Demo1{
    public static void main(String []args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter width : ");
        double width = sc.nextDouble();
        System.out.print("Enter height : ");
        double height = sc.nextDouble();
        Rectangle a1 = new Rectangle(width, height);
        
        System.out.println("The area of the rectangle is : " + a1.getArea());
    }
}
