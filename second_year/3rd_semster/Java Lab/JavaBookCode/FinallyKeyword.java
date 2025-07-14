import java.util.Random;

public class FinallyKeyword{
	static void proA() throws RuntimeException{
		try{
			System.out.println("inside ProA");
			throw new RuntimeException("demo");
		}
		// catch(IllegalAccessException e){
		// 	System.out.println("inside proa's catch");
		// }
		finally{
			System.out.println("ProA's finally");
		}
	}

	static void proB(){
		try{
			System.out.println("inside proB");
			return;
		}finally{
			System.out.println("proB's finally");
		}
	}

	static void proC(){
		try{
			System.out.println("inside proC");
		}finally{
			System.out.println("proc'S finally");
		}
	}

	public static void main(String []args){
		try{
			proA();
		}catch(Exception e){
			System.out.println("Exception caught");
		}
		
		proB();
		proC();
	}
}