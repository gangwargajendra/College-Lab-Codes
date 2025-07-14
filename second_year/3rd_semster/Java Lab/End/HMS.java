import java.util.*;

class OutOfStockException extends Exception {
    public String toString(){
        return "Medicion is out of stock.";
    }
}

class Person {
    int personID;
    String name;

    public Person(int personID , String name){
        this.personID = personID;
        this.name = name;
    }

    void prescribeMedicine(String medicineName , int quantity, ArrayList<Medicine> medicine){
        System.out.println("perscibed medicine;");
    }

    void calculateCharges(int daysAdmitted){
        System.out.println("Days admitted.");
    }

    void calculateSalary(int t){
        System.out.println("salary.");
    }
}

class Patient extends Person {
    String ailmentType;
    boolean isInsured;
    String medicineName;
    int quantity;

    public Patient (int personID ,String name, String ailmentType,boolean isInsured,String medicineName,int quantity){
        super(personID, name);
        this.ailmentType = ailmentType;
        this.isInsured = isInsured;
        this.medicineName = medicineName;
        this.quantity = quantity;
    }

    void prescribeMedicine(String medicineName , int quantity, ArrayList<Medicine> medicine){
        Medicine crnt = null;
        for(Medicine medicines : medicine){
            if(medicines.medicineName.equals(medicineName)){
                crnt = medicines;
                break;
            }
        }

        if(crnt == null){
            System.out.println("medicine is not present in stock.");
        }

        
        this.medicineName = medicineName;

        try{
            if(this.quantity < quantity){
                throw new OutOfStockException();
            }else{
                crnt.stockQuantity -= quantity; 
                this.quantity = quantity;
            }
        }catch (OutOfStockException e){
            System.out.println("Exception : " + e);
        }
    }

    
    public void calculateCharges(int daysAdmitted){
        int baseCharge = 500 * daysAdmitted;
        if(isInsured){
            baseCharge -= (int)(baseCharge * .1); 
        }
        System.out.println("charges : " + baseCharge);
    }
}

class Doctor extends Person {
    String specialization;
    int patientsAssigned;

    public Doctor(int personID,String name,String specialization ,int patientsAssigned){
        super(personID, name);
        this.patientsAssigned = patientsAssigned;
        this.specialization = specialization;
    }

    public void calculateSalary(int daysWorked){
        int baseSalary = 1000 * daysWorked;

        if(patientsAssigned > 3){
            baseSalary += 2000;
        }
        System.out.println("Doctor's Salary : " + baseSalary);
    }
}

class Medicine {
    String medicineName;
    String category;
    int stockQuantity;

    public Medicine(String medicineName, String category, int stockQuantity){
        this.medicineName = medicineName;
        this.category = category;
        this.stockQuantity = stockQuantity;
    }
}

public class HMS {
    ArrayList<Medicine> medicines = new ArrayList<>();
    ArrayList<Person> persons = new ArrayList<>();

    public void StoreDataInStart(){
        
        medicines.add(new Medicine("paracetamol" , "Analgesic" , 10));
        medicines.add(new Medicine("Amoxicillin", "Antibiotic", 5));
        medicines.add(new Medicine("Asprin", "Analgesic", 0));
        medicines.add(new Medicine("Ibuprofin", "Anti-inflammatory", 8));
        medicines.add(new Medicine("Metformin", "Antidiabetic", 12));

        persons.add(new Patient(2, "John Doe", "Fever", true, "paracetamol", 2));
        persons.add(new Patient(4, "Alice Smith", "Infection", false, "Amoxicillin", 1));
        persons.add(new Patient(6, "Bob Johnson", "Diabetes", true, "Metformin", 3));
        persons.add(new Patient(8, "Carol White", "Arthritis", false, "Ibuprofin", 4));
        persons.add(new Patient(10, "Eve Brown", "Hypertension", true, "Asprin", 1));

        
        persons.add(new Doctor(1, "Dr. Brown", "Cardiology", 4));
        persons.add(new Doctor(3, "Dr. Green", "Neurology", 2));
        persons.add(new Doctor(5, "Dr. Black", "Orthopedics", 6));
        persons.add(new Doctor(7, "Dr. Grey", "Dermatology", 1));
        persons.add(new Doctor(9, "Dr. White", "General Medicine", 3));
    }

    public void displayAll(){
        System.out.println("Medicine : ");
        for(Medicine it : medicines){
            System.out.println("MedicineName, category, StockQuantity : " + it.medicineName + " , " + it.category + " , " + it.stockQuantity);
        }

        System.out.println("person : ");
        for(Person it : persons){
            System.out.println("Name, PersonId : " + it.name + " , " + it.personID);
        }
    }

    public static void main(String[] args) {
        HMS hms = new HMS();
        hms.StoreDataInStart();
        hms.displayAll();

        // for adding a person
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter person name : ");
        String name = sc.nextLine();
        System.out.print("Enter PersonID: ");
        int personID = sc.nextInt();
        if(personID % 2 == 0){
            System.out.print("Enter Ailment type : ");
            sc.nextLine();
            String ailmentType = sc.nextLine();
            System.out.print(ailmentType+"Enter Medicine : ");
            String medicine = sc.nextLine();
            System.out.print(medicine + "Enter quantity : ");
            int quantity = sc.nextInt();
            System.out.print("Enter insured or not : ");
            boolean insured = sc.nextBoolean();

            hms.persons.add(new Patient(personID, name, ailmentType, insured, medicine, quantity));
        }else {
            System.out.print("Enter specialization : ");
            String specialization = sc.nextLine();
            System.out.print("Enter patient Assigned : ");
            int patientsAssigned = sc.nextInt();

            hms.persons.add(new Doctor(personID, name, specialization, patientsAssigned));
        }

        hms.displayAll();

        //
        System.out.print("Enter personId for patient : ");
        int newPersonID = sc.nextInt();
        if(newPersonID % 2 == 0){
            System.out.print("Enter medicine name : ");
            sc.nextLine();
            String newMedecineName = sc.nextLine();
            System.out.print("Enter quantity : ");
            int newQuantity = sc.nextInt();

            Person x = null;
            for(Person it : hms.persons){
                if(it.personID == newPersonID){
                    x = it;
                    break;
                }
            }

            if(x == null){
                System.out.println("person is not presnt.");
            }else{
                x.prescribeMedicine(newMedecineName, newQuantity, hms.medicines);
            }
        }

        hms.displayAll();

        //

        System.out.println("Enter patient daysAdmitted : ");
        int daysAdmitted = sc.nextInt();
        Person p1 = hms.persons.getFirst();
        p1.calculateCharges(daysAdmitted);

        System.out.println("Enter Doctor DaysWorked : ");
        int daysWorked = sc.nextInt();
        int t= 0;
        Person q = p1;
        for(Person p : hms.persons){
            if(t == 7){
                q = p;
                break;
            }
            t++;
        }

        q.calculateSalary(daysWorked);

    }
}