import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class BReader {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		File f = new File("test.txt");	
		FileReader fr = null;
		BufferedReader br =null;
		String str; 
		
		try {
			fr = new FileReader(f);
			br = new BufferedReader(fr);
			 
			  while ((str = br.readLine()) != null) 
			    System.out.println(str); 
			  
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			try {
				fr.close();
				br.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

}
