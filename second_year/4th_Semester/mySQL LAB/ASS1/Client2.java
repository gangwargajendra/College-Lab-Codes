import java.net.*;
import java.util.*;
import java.io.*;

public class Client2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String host = "localhost";
        try{
            Socket socket = new Socket(host, 8008);
            System.out.println("Welcome to the client program!");

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

            System.out.println("Enter a string to change in uppercase : ");
            String str = sc.nextLine();

            out.println(str);
            out.flush();

            String serverResponse = in.readLine();
            System.out.println("Server response : ");
            System.out.println(str + " uppercase => " + serverResponse);

            in.close();
            out.close();
            socket.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}
