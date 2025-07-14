import java.util.ArrayList;
import java.util.Scanner;

class InvalidEmailIdException extends Exception {

    String msg;

    InvalidEmailIdException(String mssg) {
        this.msg = mssg;
    }

    public String toString() {
        return msg;
    }
}

class InvalidPINCodeEception extends Exception {

    public String toString() {
        return "Invalid PIN code. Please Enter valid PIN.";
    }
}

class InvalidRollNoException extends Exception {

    public String toString() {
        return "Invalid roll number. Please enter valid rollNo. Should be conatin stud before start.";
    }
}

class InvalidEmployeeIdException extends Exception {

    public String toString() {
        return "Invalid empID. Please enter valid empID. Should be conatin emp before start.";
    }
}

class Person {
    String fName;
    String lName;
    String pan;
    String addressPin;

    void validPIN() throws InvalidPINCodeEception {
        if (addressPin.length() < 6)
            throw new InvalidPINCodeEception();
    }

    void validEmail(String email) throws InvalidEmailIdException {
        int atIndex = email.lastIdexOf('@');
        if (atIndex == -1)
            throw new InvalidEmailIdException("Email must conatin @ symbol.");

        String beforeAt = email.substring(0, atIndex);
        String afterAt = email.substring(atIndex + 1);

        boolean spChar = false;
        char[] specialChar = { '@', '!', '#', '$', '&', '*' };

        for (char spcial : specialChar) {
            if (beforeAt.contains(String.valueOf(spcial))) {
                spChar = true;
                break;
            }
        }

        if (!spChar) {
            throw new InvalidEmailIdException(
                    "Email must contain at least one special character (@, #, !, $, &, *) before @.");
        }

        if (!afterAt.contains(".")) {
            throw new InvalidEmailIdException("Invalid domain format. Domain must contain '.'");
        }
    }
}

class Student extends Person {
    String email;
    String rollNo;

    void validRoll() throws InvalidRollNoException {
        if (!rollNo.contains("stud"))
            throw new InvalidRollNoException();
    }
}

class Employee extends Person {
    String email;
    String empID;

    void validEmpID() throws InvalidEmployeeIdException {
        if (!empID.contains("emp"))
            throw new InvalidEmployeeIdException();
    }
}

public class Assignment11 {

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {

        ArrayList<Person> p = new ArrayList<>();
        ArrayList<Student> st = new ArrayList<>();
        ArrayList<Employee> ep = new ArrayList<>();

        int number = 0;
        while (number != 4) {
            System.out.println(1 + ". Create person");
            System.out.println(2 + ". Create Student");
            System.out.println(3 + ". Create Employee");
            System.out.println(4 + ". Exit.");

            number = scanner.nextInt();
            scanner.nextLine();

            if (number == 1) {
                p.add(new Person());
                Person p1 = p.get(p.size() - 1);

                System.out.println("Enter first name: ");
                p1.fName = scanner.nextLine();

                System.out.println("Enter last name: ");
                p1.lName = scanner.nextLine();

                System.out.println("Enter PAN number: ");
                p1.pan = scanner.nextLine();

                boolean flag = true;
                while (flag) {
                    try {
                        System.out.println("Enter PIN address: ");
                        p1.addressPin = scanner.nextLine();

                        p1.validPIN();
                        flag = false;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                        flag = true;
                    }
                }
            }

            if (number == 2) {
                st.add(new Student());
                Student s1 = st.get(st.size() - 1);

                System.out.println("Enter first name of student: ");
                s1.fName = scanner.nextLine();

                System.out.println("Enter last name of stundet: ");
                s1.lName = scanner.nextLine();

                System.out.println("Enter PAN number of student: ");
                s1.pan = scanner.nextLine();

                while (true) {
                    try {
                        System.out.println("Enter PIN address of student: ");
                        s1.addressPin = scanner.nextLine();

                        s1.validPIN();
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }

                while (true) {
                    try {
                        System.out.println("Enter email id of student: ");
                        s1.email = scanner.nextLine();

                        s1.validEmail(s1.email);
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }

                while (true) {
                    try {
                        System.out.println("Enter rol number of studnet: ");
                        s1.rollNo = scanner.nextLine();

                        s1.validRoll();
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }
            }

            if (number == 3) {
                ep.add(new Employee());
                Employee e1 = ep.get(ep.size() - 1);

                System.out.println("Enter first name of employee: ");
                e1.fName = scanner.nextLine();

                System.out.println("Enter last name of employee: ");
                e1.lName = scanner.nextLine();

                System.out.println("Enter PAN number of employee: ");
                e1.pan = scanner.nextLine();

                while (true) {
                    try {
                        System.out.println("Enter PIN address of employee: ");
                        e1.addressPin = scanner.nextLine();

                        e1.validPIN();
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }

                while (true) {
                    try {
                        System.out.println("Enter email id of employee: ");
                        e1.email = scanner.nextLine();

                        e1.validEmail(e1.email);
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }

                while (true) {
                    try {
                        System.out.println("Enter empID of employee: ");
                        e1.empID = scanner.nextLine();

                        e1.validEmpID();
                        break;
                    } catch (Exception e) {
                        System.out.println("Exception: " + e);
                    }
                }
            }
        }
    }
}
