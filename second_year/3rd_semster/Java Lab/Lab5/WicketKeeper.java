import java.util.*;

public class WicketKeeper extends Batsman {
	int stumping;
	public void displayWicketKeeper(){
		this.displayBatsman();
		System.out.println("total stumping : "+stumping);
	}
	public void inputWicketKeeper(){
		this.inputBatsman();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter total stumping of cricketer : ");
		int stumping = sc.nextInt();
		this.stumping = stumping;
	}
}