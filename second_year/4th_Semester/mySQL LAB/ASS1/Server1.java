import java.io.*;
import java.net.*;

public class Server1 {
    static int digitSum(String num){
        int sum = 0;
        for(int i=0 ; i<num.length() ; i++){
            sum += num.charAt(i) - '0';
        }
        return sum;
    }
    public static void main(String[] args) {
        try{
            ServerSocket serverSocket = new ServerSocket(8008);
            System.out.println("Welcome to the server program!");

            Socket clientSocket = serverSocket.accept();

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

            String num = in.readLine();
            System.out.println("client message : " + num);

            int responseMessage = digitSum(num);

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
