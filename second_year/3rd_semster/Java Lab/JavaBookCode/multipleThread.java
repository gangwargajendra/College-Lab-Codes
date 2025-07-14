class NewThread implements Runnable {
    String name;   // name of the thread
    Thread t;

    NewThread(String threadName){
        name = threadName;
        t = new Thread(this,name);
        System.out.println("New Thread : " + t);
    }

    public void run(){
        try{
            for(int i=5 ; i>0 ; i--){
                System.out.println(name + " : " + i);
                Thread.sleep(1000);
            }
        } catch(InterruptedException e){
            System.out.println(name + " interrupted.");
        }
        System.out.println(name + " Exiting.");
    }
}

public class multipleThread {
    public static void main(String[] args) {
        NewThread nt1 = new NewThread("one");
        NewThread nt2 = new NewThread("Two");
        NewThread nt3 = new NewThread("Three");

        nt1.t.start();
        nt2.t.start();
        nt3.t.start();

        try{
            // wait for other thread to end
            Thread.sleep(10000);
        } catch(InterruptedException e){
            System.out.println("main thread interrupted.");
        }
        System.out.println("main thread Exiting.");
    }
}
