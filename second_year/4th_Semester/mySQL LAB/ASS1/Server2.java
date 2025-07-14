import java.io.*;
import java.net.*;

public class Server2 {
    public static void main(String[] args) {
        try{
            ServerSocket serverSocket = new ServerSocket(8008);
            System.out.println("Welcome to the server program!");

            Socket clientSocket = serverSocket.accept();

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

            String clientStr = in.readLine();
            System.out.println("client message : " + clientStr);

            String responseMessage = clientStr.toUpperCase();

            out.println(responseMessage);
            out.flush();

            in.close();
            out.close();
            clientSocket.close();
            serverSocket.close();
        }catch(Exception e){
            System.out.println(e);
        }
    }    
}
