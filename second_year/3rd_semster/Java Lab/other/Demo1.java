import java.util.*;

public class Demo {
    public static void main(String ... args){
        int maxStu = 5;
        int maxFac = 2;

        Faculty []facArr = new Faculty[maxFac];
        Student []StuArr = new Student[maxStu];
        boolean n = true;
        int istu = 0;
        int ifac = 0;

        while(n){
            System.out.println("1.Add student 2.Delete Student 3.Add Faculty 4.Delete Faculty 5.Update student Record 6.Get Student details 7.Get Advisor details 8.exit");
            System.out.print("Enter your choice : ");
            Scanner sc = new Scanner(System.in);
            int choice = sc.nextInt();
            switch(choice) {
                case 1:
                    if(ifac == 0){
                        System.out.println("Faculty is not registered yet!");
                        break;
                    }else if(istu == maxStu ){
                        System.out.println("Student is full..");
                    }else if(istu < maxStu){
                        Faculty ad;
                        for(int i = 0 ; i < ifac ; i++){
                            System.out.print(i+1 + " => ");
                            facArr[i].toString();
                        }
                        System.out.print("choose one faculty to add : ");
                        int ch = sc.nextInt();
                        ad = facArr[ch-1];
                        StuArr[istu++] = new Student(ad);
                        break;
                    }
                case 2:
                    if(istu == 0){
                        System.out.println("student is not registered yet!");
                        break;
                    }else{
                        for(int i = 0 ; i < istu ; i++){
                            System.out.print(i+1 + " => ");
                            StuArr[i].getStudentDetails();
                        }
                        System.out.print("choose one student to delete : ");
                        int ch = sc.nextInt();
                        for(int i = ch-1 ; i < istu-1 ; i++){
                            StuArr[i] = StuArr[i+1];
                        }
                        istu--;
                        break;
                    }
                case 3:
                    if(ifac < maxFac){
                        facArr[ifac++] = new Faculty();
                    }else {
                        System.out.println("faculty is full..");
                    }
                    break;
                case 4:
                    if(ifac == 0){
                        System.out.println("faculty is not registered yet!");
                        break;
                    }else{
                        for(int i = 0 ; i < ifac ; i++){
                            System.out.print(i+1 + " => ");
                            facArr[i].toString();
                        }
                        System.out.print("choose one facluty to delete : ");
                        int ch = sc.nextInt();
                        for(int i = ch-1 ; i < ifac-1 ; i++){
                            facArr[i] = facArr[i+1];
                        }
                        ifac--;
                        break;
                    }
                case 5:
                    for(int i = 0 ; i < istu ; i++){
                        System.out.print(i+1 + " => ");
                        StuArr[i].getStudentDetails();
                    }
                    System.out.print("choose one student to update : ");
                    int ch = sc.nextInt();
                    System.out.println("1.update Advisor 2.other updation");
                    System.out.print("choose one way to update : ");
                    int mn = sc.nextInt();
                    if(mn == 1){
                        for(int i = 0 ; i < ifac ; i++){
                            System.out.print(i+1 + " => ");
                            facArr[i].toString();
                        }
                        System.out.print("choose one facluty to be advisor : ");
                        int ad = sc.nextInt();
                        StuArr[ch-1].FacultyAdvisor = facArr[ad-1]; 
                    }else if(mn == 2){
                        StuArr[ch-1].updateStudentRecord();
                    }
                    break;
                case 6:
                    for(int i = 0 ; i < istu ; i++){
                        System.out.print(i+1 + " => ");
                        StuArr[i].getStudentDetails();
                    }
                    break;
                case 7:
                    for(int i = 0 ; i < ifac ; i++){
                        System.out.print(i+1 + " => ");
                        facArr[i].toString();
                    }
                    break;
                case 8:
                    n = false;
                    break;
            }
        }
    }
}