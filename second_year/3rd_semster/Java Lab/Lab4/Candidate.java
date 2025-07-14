import java.util.*;

public class Candidate {
	int rollNo;
	String name;
	float score;
	String remarks;
	
	public void assignRem(){
		if(score < 0 || score > 100){
			System.out.println("invalid marks..");
			score = 0;
			remarks = "none";
		}else if(score >= 50){
			remarks = "Selected";
		}else{
			remarks = "Not selected";
		}
	}

	public void enterDetails(){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter name : ");
		String name = sc.next();
		this.name = name;
		System.out.println("Enter rollNo : ");
		int rollNo = sc.nextInt();
		this.rollNo = rollNo;
		System.out.println("Enter score : ");
		float score = sc.nextFloat();
		this.score = score;
		
		this.assignRem();
	}
	
	public void displayRecord(){
		System.out.println("Student name : "+name);
		System.out.println("Student rollNo : "+rollNo);
		System.out.println("Student score : "+score);
		System.out.println("Student remarks : "+remarks);
	} 
}