import java.util.*;

public class Footballer extends SportsPerson {
	String type;
	int matchPlayed;
	int goals;
	int tackles;
	public void displayFootballer(){
		this.displaySportsPerson();
		System.out.println("Sports person type : "+type);
		System.out.println("match played : "+matchPlayed);
		System.out.println("goals : "+goals);
		System.out.println("tackles : "+tackles);
	}
	public void inputFootballer(){
		this.inputSportsPerson();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the type of Footballer : ");
		String type = sc.nextLine();
		this.type = type;
		System.out.print("Enter the match played by Footballer : ");
		int matchPlayed = sc.nextInt();
		this.matchPlayed = matchPlayed;
		System.out.print("Enter the goals done by Footballer : ");
		int goals = sc.nextInt();
		this.goals = goals;
		System.out.print("Enter the tackles done by Footballer : ");
		int tackles = sc.nextInt();
		this.tackles = tackles;
	}
}