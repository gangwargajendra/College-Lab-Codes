import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class ScannerExample {

    public static void main(String args[])  {
 
        //creating File instance to reference text file in Java
        File fileRead = new File("test.txt");
        File fileWrite = new File("copied.txt");
        FileWriter writer = null;
     
        //Creating Scanner instance to read File in Java
        Scanner scnr = null;
		try {
			scnr = new Scanner(fileRead);
			fileWrite.createNewFile();
	        writer = new FileWriter(fileWrite); 
	     
	        while(scnr.hasNextLine()){
				String word = scnr.next();
	            int roll = scnr.nextInt();
	            double sal = scnr.nextDouble();
	            
				writer.write(word + "\t" + roll + "\t" + sal + "\n"); 
		        //writer.write("\n"); 
		        writer.flush();
	        }   
	        writer.close();
	        scnr.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }  
}


