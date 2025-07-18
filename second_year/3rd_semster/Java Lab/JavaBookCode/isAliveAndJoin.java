// using join() to wait for threads to finish
class NewThread implements Runnable {
    String name;  // name of thread
    Thread t;

    NewThread(String threadName){
        name = threadName;
        t = new Thread(this , name);
        System.out.println("New Thread : " + t);
    }

    // This is the entry point for thread
    public void run(){
        try{
            for(int i=5 ; i>0 ; i--) {
                System.out.println(name + " : " + i);
                Thread.sleep(1000);
            }
        }catch(InterruptedException e){
            System.out.println(name + " interrupted.");
        }

        System.out.println(name + " exiting.");
    }
}

public class isAliveAndJoin {
    public static void main(String[] args) {
        NewThread nt1 = new NewThread("one");
        NewThread nt2 = new NewThread("Two");
        NewThread nt3 = new NewThread("Three");
        

        // start the threads
        nt1.t.start();
        nt2.t.start();
        nt3.t.start();

        System.out.println("Thread one is alive : " + nt1.t.isAlive());
        System.out.println("thread two is alive : " + nt2.t.isAlive());
        System.out.println("Thread three is alive : " + nt3.t.isAlive());

        // Wait for threads to finish
        try {
            System.out.println("Waiting for threads to finish .");
            nt1.t.join();
            nt2.t.join();
            nt3.t.join();
        }catch(InterruptedException e){
            System.out.println("Main thread Interrupted.");
        }

        System.out.println("Thread one is alive : " + nt1.t.isAlive());
        System.out.println("thread two is alive : " + nt2.t.isAlive());
        System.out.println("Thread three is alive : " + nt3.t.isAlive());

        System.out.println("Main thread exiting.");

    }
}
