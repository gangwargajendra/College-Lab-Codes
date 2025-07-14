import java.sql.*;
import java.util.Scanner;

public class DBApplication {

    public static void query1(Connection conn) {
    Scanner sc = new Scanner(System.in);
        System.out.println("1.Student, 2. Class, 3. Enrolled, 4. Faculty");
        System.out.println("Enter number :");
        int choice = sc.nextInt();
        sc.nextLine();

        String query = "";
        switch(choice) {
            case 1:
                query = "select * from student";
                break;
            case 2:
                query = "select * from class";
                break;
            case 3:
                query = "select * from enrolled";
                break;
            case 4:
                query = "select * from faculty";
                break;
            default:
                System.out.println("Invalid");
                return;
        }
        
        try {
            Statement stmt = conn.createStatement();
            ResultSet rlt = stmt.executeQuery(query);
            ResultSetMetaData rsmd = rlt.getMetaData();
            int noOfCol = rsmd.getColumnCount();

            for (int i = 1; i <= noOfCol; i++){
                System.out.printf("%s   ", rsmd.getColumnName(i));
            }
            System.out.println();
            while(rlt.next()){
                for (int i = 1; i <= noOfCol; i++){
                    System.out.printf("%s  ", rlt.getString(i));
                }
                System.out.println();
            }
            rlt.close();
            stmt.close();
        } catch(SQLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }


    public static void query2(Connection conn) {
        Scanner sc = new Scanner(System.in);
        System.out.print("\nEnter student age: ");
        int age = sc.nextInt();
        sc.nextLine();

        String query = "select sname from student where age = " + age;
        
        try {
            Statement stmt = conn.createStatement();
            ResultSet rlt = stmt.executeQuery(query);
            System.out.println("Student with age " + age + " : ");
            boolean flag = false;
            while(rlt.next()){
                System.out.println(rlt.getString("sname"));
                flag = true;
            }
            if (!flag) {
                System.out.println("Not present with age " + age);
            }
            rlt.close();
            stmt.close();
        } catch(SQLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }

    public static void query3(Connection conn) {
        Scanner sc = new Scanner(System.in);
        System.out.print("\nEnter department id: ");
        int deptid = sc.nextInt();
        sc.nextLine();

        String query = "select fid, fname from faculty where deptid = " + deptid;
        
        try {
            Statement stmt = conn.createStatement();
            ResultSet rlt = stmt.executeQuery(query);
            System.out.println("Faculty with deptID " + deptid + " :");
            boolean flag = false;
            while(rlt.next()){
                System.out.println(rlt.getString("fid") + " " + rlt.getString("fname"));
                flag = true;
            }
            if (!flag) {
                System.out.println("no faculty with deptID : " + deptid);
            }
            rlt.close();
            stmt.close();
        } catch(SQLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }

    public static void query4(Connection conn) {
        Scanner sc = new Scanner(System.in);
        System.out.print("\nEnter student name: ");
        String name = sc.nextLine();

        String query = "select e.cname from enrolled as e join student as s ON e.snum = s.snum where s.sname = " + name;
        try {
            Statement stmt = conn.createStatement();
            ResultSet rlt = stmt.executeQuery(query);
            System.out.println("Courses taken with name '" + name + " : ");
            boolean flag = false;
            while(rlt.next()){
                System.out.println(rlt.getString("cname"));
                flag = true;
            }
            if (!flag) {
                System.out.println("No courses found for student " + name);
            }
            rlt.close();
            stmt.close();
        } catch(SQLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
    
    public static void main(String[] args) {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/dbms_lab?useSSL=false",
                     "root", "Upnkdghl@854318554511335");

            query1(conn);
            query2(conn);
            query3(conn);
            query4(conn);
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
