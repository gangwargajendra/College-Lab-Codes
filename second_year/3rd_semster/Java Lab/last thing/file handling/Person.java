    import java.util.Scanner;
    import java.io.*;
     
    class Person{
        String name;
        int id,salary;
     
        Person(String name,int id,int salary)
        {
            this.name = name;
            this.id = id;
            this.salary = salary;
        }
     
        public static void main(String[] args) throws Exception
        {
            Person[] array = new Person[10];
            File file = new File("input.txt");
            Scanner fsc = new Scanner(file);
     
            String name;
            int id,salary,cnt=0;
            System.out.println("START");
            while(fsc.hasNextLine())
            {
                System.out.println("CNT : "+cnt);
                name = fsc.next();
                id = fsc.nextInt();
                salary = fsc.nextInt();
                array[cnt] = new Person(name,id,salary);
                cnt++;
            }
            System.out.println("Success");
            //File file2 = new File("output.txt","w");
       }
    }