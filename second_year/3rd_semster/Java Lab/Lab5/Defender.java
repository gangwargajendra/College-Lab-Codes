import java.util.*;

public class Defender extends Footballer {
	int tackle;
	int headers;
	public void displayDefender(){
		this.displayFootballer();
		System.out.println("total tackle : "+tackle);
		System.out.println("total headers : "+headers);
	}
	public void inputDefender(){
		this.inputFootballer();
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the tackle of Footballer : ");
		int tackle = sc.nextInt();
		this.tackle = tackle;
		System.out.print("Enter the headers of Footballer : ");
		int headers = sc.nextInt();
		this.headers = headers;
	}
}