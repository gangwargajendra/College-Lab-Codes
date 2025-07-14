import java.util.*;

public class Demo {
	public static void main(String []args){
		boolean n = true;
		while(n){
			System.out.println("1.SportsPerson 2.cricketer 3.Batsman 4.Bowler 5.Wicketkeeper 6.Footballer 7.Striker 8.Defender 9.GoalKeeper 10.exit");
			int choice;
			System.out.print("Enter choice : ");
			Scanner sc = new Scanner(System.in);
			choice = sc.nextInt();
			switch(choice){
				case 1:
					SportsPerson s1 = new SportsPerson();
					s1.inputSportsPerson();
					s1.displaySportsPerson();
					break;
				case 2:
					Cricketer c1 = new Cricketer();
					c1.inputCricketer();
					c1.displayCricketer();
					break;
				case 3:
					Batsman b1 = new Batsman();
					b1.inputBatsman();
					b1.displayBatsman();
					break;
				case 4:
					Bowler b2 = new Bowler();
					b2.inputBowler();
					b2.displayBowler();
					break;
				case 5:
					WicketKeeper w1 = new WicketKeeper();
					w1.inputWicketKeeper();
					w1.displayWicketKeeper();
					break;
				case 6:
					Footballer f1 = new Footballer();
					f1.inputFootballer();
					f1.displayFootballer();
					break;
				case 7:
					Striker s2 = new Striker();
					s2.inputStriker();
					s2.displayStriker();
					break;
				case 8:
					Defender d1 = new Defender();
					d1.inputDefender();
					d1.displayDefender();
					break;
				case 9:
					GoalKeeper g1 = new GoalKeeper();
					g1.inputGoalKeeper();
					g1.displayGoalKeeper();
					break;
				case 10:
					n = false;
					break;
			}
		}
	}
} 