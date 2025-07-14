import java.sql.*;

public class Query1 {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourdbname";
        String username = "yourusername";
        String password = "yourpassword";
        try {
            Connection conn = DriverManager.getConnection(url, username, password);
            Statement stmt = conn.createStatement();
            String query = "SELECT COUNT(*) FROM Student WHERE major = 'Computer Engineering'";
            ResultSet rs = stmt.executeQuery(query);
            if(rs.next()){
                int count = rs.getInt(1);
                System.out.println("Number of Computer Engineering students: " + count);
            }
            rs.close();
            stmt.close();
            conn.close();
        } catch(SQLException e){
            e.printStackTrace();
        }
    }
}
