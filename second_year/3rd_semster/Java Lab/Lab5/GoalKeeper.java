import java.util.*;

public class GoalKeeper extends Striker {
	int saves;
	int cleanSheets;
	public void displayGoalKeeper(){
		this.displayStriker();
		System.out.println("total saves : "+saves);
		System.out.println("total clean Sheets : "+cleanSheets);
	}
	public void inputGoalKeeper(){
		this.inputStriker();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the saves of Footballer : ");
		int saves = sc.nextInt();
		this.saves = saves;
		System.out.print("Enter the total clean Sheets of Footballer : ");
		int cleanSheets = sc.nextInt();
		this.cleanSheets = cleanSheets;
	}
}