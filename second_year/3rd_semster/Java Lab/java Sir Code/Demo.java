public class Demo{
	public static void main(String[] args) {
    Example1 thread = new Example1();
    thread.start();
    
    // Update amount and print its value
    System.out.println("Amount: " + Example1.amount);
    Example1.amount++;
    System.out.println("Amount: " + Example1.amount);
	
	
	
	
	
	
	// Wait for the thread to finish
    /*while(thread.isAlive()) {
      System.out.println("Waiting...");
    }*/
  }
}