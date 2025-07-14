import java.util.*;

public class StudentRecord {
	private int rollNo;
	private String name;
	private String department;

	public StudentRecord(){
		this.rollNo = -1;
		this.name = "000";
		this.department = "000";
	}
	public StudentRecord(int rollNo){
		this.rollNo = rollNo;
		this.name = "000";
		this.department = "000";
	}
	public StudentRecord(int rollNo, String name){
		this.rollNo = rollNo;
		this.name = name;
		this.department = "000";
	}
	public StudentRecord(int rollNo, String name ,String department){
		this.rollNo = rollNo;
		this.name = name;
		this.department = department;
	}
	public void displayRecord(){
		System.out.println("roll No : " + rollNo);
		System.out.println("name : " + name);
		System.out.println("department : " + department);
	}
}