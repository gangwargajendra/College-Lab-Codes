import java.util.*;

public class Striker extends Footballer {
	int goalsScored;
	int assist;
	public void displayStriker(){
		this.displayFootballer();
		System.out.println("total goals Scored : "+goalsScored);
		System.out.println("total assist : "+assist);
	}
	public void inputStriker(){
		this.inputFootballer();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the goal scored by Footballer : ");
		int goalsScored = sc.nextInt();
		this.goalsScored = goalsScored;
		System.out.print("Enter the assist by Footballer : ");
		int assist = sc.nextInt();
		this.assist = assist;
	}
}