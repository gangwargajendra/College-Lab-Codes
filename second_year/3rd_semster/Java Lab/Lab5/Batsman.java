import java.util.*;

public class Batsman extends Cricketer {
	int runs;
	double highest;
	public void displayBatsman(){
		this.displayCricketer();
		System.out.println("total runs : "+runs);
		System.out.println("highest runs : "+highest);
	}
	public void inputBatsman(){
		this.inputCricketer();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the runs of cricketer : ");
		int runs = sc.nextInt();
		this.runs = runs;
		System.out.print("Enter the highest runs of cricketer : ");
		double highest = sc.nextDouble();
		this.highest = highest;
	}
}