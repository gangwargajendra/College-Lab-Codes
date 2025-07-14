import java.util.*;

public class Bowler extends Cricketer {
	int wickets;
	double strikeRate;
	public void displayBowler(){
		this.displayCricketer();
		System.out.println("total wickets : "+wickets);
		System.out.println("strikeRate : "+strikeRate);
	}
	public void inputBowler(){
		this.inputCricketer();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the total wickets of cricketer : ");
		int wickets = sc.nextInt();
		this.wickets = wickets;
		System.out.print("Enter the StrikeRate of cricketer : ");
		double strikeRate = sc.nextDouble();
		this.strikeRate = strikeRate;
	}
}