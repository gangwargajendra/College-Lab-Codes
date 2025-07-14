import java.sql.*;

public class createDB {
    public static void query1(Connection conn) {
        String query = "SELECT count(*) AS Count FROM student WHERE major='Computer Engineering'";
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery(query);
            if (rset.next()){
                System.err.println("question 1 : ");
                System.out.println("Number of students having \'Computer Engineering\' as major: "
                                + rset.getString("Count"));
            }
            
            rset.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }

    public static void query2(Connection conn) {
        String query = "SELECT max(age) AS max_age, min(age) AS min_age FROM student";
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery(query);
            if (rset.next()){
                System.err.println("question 2 : ");
                int max_age = rset.getInt("max_age");
                int min_age = rset.getInt("min_age");
                System.out.println("Difference of maximum and minimum age of students: "
                                + (max_age - min_age));
            }
            
            rset.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }

    public static void query3(Connection conn) {
        String query = "SELECT sname, standing FROM student WHERE age=18 AND major IN ('Psychology', 'Computer Science')";
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery(query);
            System.out.println("Students with age 18 and major in Psychology or Computer Science:");
            System.err.println("question 3 : ");
            while (rset.next()){
                String sname = rset.getString("sname");
                String level = rset.getString("standing");
                System.out.println("Name: " + sname + ", Level: " + level);
            }
            rset.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }
    
    public static void query4(Connection conn) {
        String query = "SELECT e.cname FROM Enrolled e JOIN Student s ON e.snum = s.snum WHERE s.sname = 'Lisa Walker'";
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery(query);
            System.out.println("Courses that Lisa Walker has enrolled in:");
            System.err.println("question 4 : ");
            while (rset.next()){
                String cname = rset.getString("cname");
                System.out.println(cname);
            }
            rset.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }

    public static void query5(Connection conn) {
        String query = "SELECT DISTINCT s.sname FROM Student s JOIN Enrolled e ON s.snum = e.snum";
        try {
            Statement stmt = conn.createStatement();
            ResultSet rset = stmt.executeQuery(query);
            System.out.println("Names of students who have taken at least one course:");
            System.err.println("question 5 : ");
            while (rset.next()){
                String sname = rset.getString("sname");
                System.out.println(sname);
            }
            rset.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }
    
    

    public static void JDBCexample() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/dbms_lab?useSSL=false",
                    "root", "");

            
            query1(conn);
            query2(conn);
            query3(conn);
            query4(conn);
            query5(conn);
            conn.close();
        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }

    public static void main(String[] args) {
        JDBCexample();
    }
}