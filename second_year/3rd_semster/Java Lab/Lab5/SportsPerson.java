import java.util.*;

public class SportsPerson{
	String name;
	String address;
	public void displaySportsPerson(){
		System.out.println("name : "+name);
		System.out.println("address : "+address);
	}
	public void inputSportsPerson(){
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the name of sportsperson : ");
		String name = sc.nextLine();
		this.name = name;
		System.out.print("Enter the address of sportsperson : ");
		String address = sc.nextLine();
		this.address = address;
	}
}
