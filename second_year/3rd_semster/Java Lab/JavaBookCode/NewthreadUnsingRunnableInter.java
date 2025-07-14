class NewThread implements Runnable {
    Thread t;

    NewThread(){
        // create a new, second thread
        t = new Thread(this, "Demo Thread");
        System.out.println("child thread : " + t);
    }

    // entry point for the second thread
    public void run() {
        try {
            for(int i=5 ; i>0 ; i--){
                System.out.println("child thread : " + i);
                Thread.sleep(500);
            }
        } catch (InterruptedException e){
            System.out.println("child interrupt.");
        }
        System.out.println("Exiting child thread");
    }
}

public class NewthreadUnsingRunnableInter {
    public static void main(String args[]){
        NewThread nt = new NewThread(); // create a new thread

        nt.t.start();

        try{
            for(int i=5 ; i>0 ; i--){
                System.out.println("Main thread : " + i);
                Thread.sleep(1000);
            }
        }catch(InterruptedException e){
            System.out.println("Main thread interrupted.");
        }
        System.out.println("main thread exiting");
    }
}
