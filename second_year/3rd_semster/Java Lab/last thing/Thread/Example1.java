public class Example1 extends Thread {
  public static int amount = 0;
  public void run() {
	for(int i = 0; i<100; i++)
		amount++;
  }
}