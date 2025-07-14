import java.io.*;
import java.net.*;

public class Server3 {
    public static void main(String[] args) {
        try{
            ServerSocket serverSocket = new ServerSocket(8008);
            System.out.println("Welcome to the server program!");

            Socket clientSocket = serverSocket.accept();

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

            String clientStr = in.readLine();
            String clientWord = in.readLine();
            System.out.println("client string : " + clientStr);
            System.out.println("client Word : " + clientWord);

            boolean flag = clientStr.contains(clientWord);
            String serverResponse = "";
            if(flag) {
                serverResponse = clientStr + " contains " + clientWord + ". returned value : 1";
            }else{
                serverResponse = clientStr + " does not contain " + clientWord + ". returned value : 0";
            }
            
            out.println(serverResponse);
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
