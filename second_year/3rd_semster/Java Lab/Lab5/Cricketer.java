import java.util.*;

public class Cricketer extends SportsPerson {
	String type;
	int matchPlayed;
	int catches;
	public void displayCricketer(){
		this.displaySportsPerson();
		System.out.println("Sports person type : "+type);
		System.out.println("match played : "+matchPlayed);
		System.out.println("catches : "+catches);
	}
	public void inputCricketer(){
		this.inputSportsPerson();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the type of cricketer : ");
		String type = sc.nextLine();
		this.type = type;
		System.out.print("Enter the match played by cricketer : ");
		int matchPlayed = sc.nextInt();
		this.matchPlayed = matchPlayed;
		System.out.print("Enter the catch taken by cricketer : ");
		int catches = sc.nextInt();
		this.catches = catches;
	}
}