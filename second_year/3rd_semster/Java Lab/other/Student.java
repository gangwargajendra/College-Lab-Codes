import java.util.*;

public class Student {
    String name;
    int rollNo;
    double cgpa;
    Faculty FacultyAdvisor;
    String branch;
    static String collegeId = "abcd1001";

    public Student(){
        this.name="";
        this.rollNo=0;
        this.cgpa=0.0;
        this.branch="";
    }

    public Student(Faculty FacultyAdvisor){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter name of student : ");
        String name = sc.nextLine();
        this.name = name;
        System.out.print("Enter rollNo of student : ");
        int rollNo = sc.nextInt();
        this.rollNo = rollNo;
        System.out.print("Enter cgpa of student : ");
        double cgpa = sc.nextDouble();
        this.cgpa = cgpa;
        sc.nextLine();
        this.FacultyAdvisor=FacultyAdvisor;
        System.out.print("Enter branch of student : ");
        String branch = sc.nextLine();
        this.branch = branch;
        this.FacultyAdvisor=FacultyAdvisor;
    }

    public void updateStudentRecord(){
        System.out.println("1.name 2.rollNo 3.cgpa 4.branch 5.delete faculty");
        System.out.print("Enter shoice what you want to upadate : ");
        int choice;
        Scanner sc = new Scanner(System.in);
        choice = sc.nextInt();
        if(choice == 1){
                System.out.print("Enter new name of student : ");
                sc.nextLine();
                String name = sc.nextLine();
                this.name = name;
        }else if(choice == 2){
                System.out.print("Enter new rollNo of student : ");
                int rollNo = sc.nextInt();
                this.rollNo = rollNo;
        }else if(choice == 3){
                System.out.print("Enter new cgpa of student : ");
                double cgpa = sc.nextDouble();
                this.cgpa = cgpa;
        }else if(choice == 4){
                System.out.print("Enter new branch of student : ");
                sc.nextLine();
                String branch = sc.nextLine();
                this.branch = branch;
        }else if(choice == 5){
            FacultyAdvisor = null;
        }
    }

    public void getStudentDetails() {
        System.out.println("Name: " + name);
        System.out.println("Roll No: " + rollNo);
        System.out.println("CGPA: " + cgpa);
        System.out.println("Branch: " + branch);
        if(FacultyAdvisor != null){
            System.out.println("Advisor'name : " + FacultyAdvisor.name);
            System.out.println("Advisor's emplD : " + FacultyAdvisor.emplD);
        }else{
            System.out.println("Advisor == Nothing");
        }
    }

    public Faculty getAdvisor() {
        return FacultyAdvisor;
    }


}