import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class FReader {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		File f = new File("test.txt");
		FileReader fr = null;
		try {
			fr = new FileReader(f);
			int i; 
		    while ((i=fr.read()) != -1) 
		      System.out.print((char) i); 
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		finally{
			try {
				fr.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
