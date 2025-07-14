import java.util.*;
public class StudentRecord1{
	public static void main(String args[]){
		StudentRecord s1 = new StudentRecord();
		s1.displayRecord();
		System.out.print("\n");
		StudentRecord s2 = new StudentRecord(2301081);
		s2.displayRecord();
		System.out.print("\n");
		StudentRecord s3 = new StudentRecord(2301081 ,"Gajendra");
		s3.displayRecord();
		System.out.print("\n");
		StudentRecord s4 = new StudentRecord(2301081 , "Gajendra" , "CSE");
		s4.displayRecord();
		System.out.print("\n");
	}
}