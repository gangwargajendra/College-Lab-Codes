import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Scann {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		File f = new File("test.txt");	
		Scanner sc = null;
		String name = null;
		int id = -1,i=0;
		Employee[] empArray = new Employee[20];
		double salary = 0;
		try {
			sc = new Scanner(f);
			 while (sc.hasNextLine()) 
			 {
				 name = sc.next();
				 id = sc.nextInt();
				 salary = sc.nextDouble();
				 try{
				 if(id<1)
					 throw new InvalidIDException("Wrong id: " + id + " at row:" + i);
				     empArray[i] = new Employee(id,name,salary);
				     i++;
				 }catch (InvalidIDException e) {
						// TODO Auto-generated catch block
						System.out.println(e.getMessage());
					}
			 }
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{
			sc.close();
		}
		
		for(int j=0;j<i;j++){
			System.out.println(empArray[j]);
		}
	}

}
