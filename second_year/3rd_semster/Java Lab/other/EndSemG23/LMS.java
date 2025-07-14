import java.util.ArrayList;
import java.util.Scanner;

import javax.sound.midi.SysexMessage;


class InvalidUserIDException extends Exception {
    public String  toString(){
        return "Entered wrong userID.";
    }
}

// User Class (abstract)
class User {
    int userId;
    String name;
    String borrowedBook = null;
    String bookType = null;
    int issueMonthNum = 0;

    // Constructor
    public User(int userId, String name) {
        this.userId = userId;
        this.name = name;
    }

    void calculateFine(int returnMonthNum){
        System.out.println("for calculating fines.");
    }

    // Method to issue a book
    public void issueBook(String title, int issueMonthNum) {
        this.borrowedBook = title;
        this.issueMonthNum = issueMonthNum;
    }

    // Method to return a book
    public void returnBook(String title, int returnMonthNum) {
        this.borrowedBook = null;
        this.bookType = null;
        calculateFine(returnMonthNum);
        this.issueMonthNum = 0;
    }
}


class StudentUser extends User {
    String studentRoll;

    public StudentUser(int userId, String name, String studentRoll) {
        super(userId, name);
        this.studentRoll = studentRoll;
    }

    void calculateFine(int returnMonthNum) {
        int gap = returnMonthNum - issueMonthNum;
        if (gap > 3) {
            int ammountOfFine = 2000 * (gap);
            System.out.println("Fine for student " + name + " is: " + ammountOfFine);
        }else{
            System.out.println("Fine for student " + name + " is: Zero.");
        }
    }
}

class FacultyUser extends User {
    String empId;

    public FacultyUser(int userId, String name, String empId) {
        super(userId, name);
        this.empId = empId;
    }

    void calculateFine(int returnMonthNum) {
        int gap = returnMonthNum - issueMonthNum;
        if (gap > 5) {
            int ammountOfFine = 5000 * gap;
            System.out.println("Fine for faculty " + name + " is: " + ammountOfFine);
        }
    }
}


class Book {
    String title;
    String type;
    int availableCopies;

    public Book(String title, String type, int availableCopies) {
        this.title = title;
        this.type = type;
        this.availableCopies = availableCopies;
    }

    public void issueBook() {
        if (availableCopies > 0) {
            availableCopies--;
        } else {
            System.out.println("No copies available for " + title);
        }
    }

    public void returnBook() {
        availableCopies++;
    }
}


public class LMS {
    ArrayList<User> users = new ArrayList<>();
    ArrayList<Book> books = new ArrayList<>();

    // Method to initialize the library with default data
    public void StartingRecord() {
        // Initialize books
        books.add(new Book("Computer Organization", "Text", 5));
        books.add(new Book("Gemba Kaizen", "Non-text", 5));
        books.add(new Book("Let us C", "Text", 5));
        books.add(new Book("Operating Systems", "Text", 5));
        books.add(new Book("The Alchemist", "Non-text", 5));

        // Initialize users
        try {
            // first Student data
            int UserId = 0;
            StudentUser s1;
            if(UserId % 2 == 0){
                s1 = new StudentUser(UserId, "raj", "2301169");
                users.add(s1);
            }else{
                throw new InvalidUserIDException();
            }
            
            // second Student data
            UserId = 2;
            if(UserId % 2 == 0){
                s1 = new StudentUser(UserId, "gautam", "2301081");
                users.add(s1);
            }else{
                throw new InvalidUserIDException();
            }

            // Third Student data
            UserId = 4;
            if(UserId % 2 == 0){
                s1 = new StudentUser(UserId, "sumit", "2301220");
                users.add(s1);
            }else{
                throw new InvalidUserIDException();
            }

            // Forth Student data 
            UserId = 6;
            if(UserId % 2 == 0){
                s1 = new StudentUser(UserId, "dhruv", "2301143");
                users.add(s1);
            }else{
                throw new InvalidUserIDException();
            }

            // Fifth Student Data
            UserId = 8;
            if(UserId % 2 == 0){
                s1 = new StudentUser(UserId, "piyush", "2301145");
                users.add(s1);
            }else{
                throw new InvalidUserIDException();
            }
            
            // for faculty data
            // first faculty data
            UserId = 1;
            FacultyUser f1;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "Arijit Sir", "ar100");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }
            
            // second faculty data
            UserId = 3;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "Mustfa Sir", "mu101");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }

            // Third faculty data
            UserId = 5;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "Paras Sir", "pa102");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }

            // Forth faculty data 
            UserId = 7;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "Sanjay Sir", "sa103");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }

            // Fifth faculty Data
            UserId = 9;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "Rakesh Sir", "ra104");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }

            // invalid Faculty user
            UserId = 10;
            if(UserId % 2 != 0){
                f1 = new FacultyUser(UserId, "bijit Sir", "ra104");
                users.add(f1);
            }else{
                throw new InvalidUserIDException();
            }

        } catch (Exception e) {
            System.out.println("Exception while storing data : " + e);
        }
    }

    // Method to display all users and books
    public void PrintAll() {
        System.out.println("Users : ");
        for (User user : users) {
            System.out.println("name : " + user.name + " && UserID : " + user.userId);
        }
        System.out.println("\nBooks : ");
        for (Book book : books) {
            System.out.println("Book Title , Type , Available Copies : " + book.title + " , '" + book.type + "' , " + book.availableCopies);
        }
        System.out.println("\n");
    }

    // Method to issue a book
    public void issueBook(int UserId, String bookTitle, int issueMonthNum) {
        User user = null;
        for(User it : users){
            if(it.userId == UserId){
                user = it;
                break;
            }
        }

        if(user != null) {
            Book book = null;
            for(Book it : books){
                if(it.title.equals(bookTitle)){
                    book = it;
                    break;
                }
            }

            if (book != null && book.availableCopies > 0) {
                user.issueBook(bookTitle, issueMonthNum);
                book.issueBook();
                System.out.println(user.name + " has issued the book: " + book.title);
            } else {
                System.out.println("Book is not present in Record");
            }
        }else {
            System.out.println("User is not present in record.");
        }
    }

    public void returnBook(int UserId, String bookTitle, int returnMonthNum) {
        User user = null;
        for(User it : users){
            if(it.userId == UserId){
                user = it;
                break;
            }
        }

        if (user != null) {
            Book book = null;
            for(Book it : books){
                if(it.title.equals(bookTitle)){
                    book = it;
                    break;
                }
            }

            if (book != null) {
                user.returnBook(bookTitle, returnMonthNum);
                book.returnBook();
                System.out.println(user.name + " has returned the book: " + book.title);
            }else{
                System.out.println("incorrect Book Title");
            }
        } else {
            System.out.println("User is not present in Record");
        }
    }

    public static void main(String[] args) {
        LMS lms = new LMS();
        lms.StartingRecord();
        Scanner sc = new Scanner(System.in);

        lms.PrintAll();

        // Simulate issuing and returning books
        System.out.print("Enter bookTitle for issue : ");
        String bookTitle = sc.nextLine(); 
        System.out.print("Enter userID : ");
        int UserID = sc.nextInt();
        System.out.println("enter IssueMonthNum : ");
        int issueMonthNum = sc.nextInt();

        lms.issueBook(UserID, bookTitle, issueMonthNum);
        lms.PrintAll();

        System.out.print("\nEnter ReturnMonthNum for returing the book : ");
        int returnMonthNum = sc.nextInt();
        lms.returnBook(UserID, bookTitle, returnMonthNum);

        lms.PrintAll();
    }
}
