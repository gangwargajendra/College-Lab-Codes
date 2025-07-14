import java.net.*;
import java.io.*;
import java.util.*;

public class Client1 {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 8008);

            System.out.println("Welcome to the client program!");

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

            System.out.println("Enter a number to find digit sum : ");
            String num = sc.nextLine();
            out.println(num);
            out.flush();

            String serverResponse = in.readLine();
            System.out.println(num + " digit sum : " + serverResponse);

            in.close();
            out.close();
            socket.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }
}
