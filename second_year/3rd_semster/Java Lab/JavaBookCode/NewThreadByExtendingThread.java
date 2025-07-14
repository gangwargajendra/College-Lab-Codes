// create a second thread by excending Thread

class NewThread extends Thread {

    NewThread(){
        // create a new , second thread
        super("Demo Thread");
        System.out.println("Child thread " +  this);
    }
    
    // This is the entry point for the second thread
    public void run(){
        try{
            for(int i=5 ; i>0 ; i--){
                System.out.println("child Thread : " + i);
                Thread.sleep(500);
            }
        } catch(InterruptedException e){
            System.out.println("child interrupted.");
        }
        System.out.println("Exiting child thread.");
    }
}

public class NewThreadByExtendingThread{
    public static void main(String[] args) {
        NewThread nt = new NewThread();

        nt.start();

        try{
            for(int i=5 ; i>0 ; i--){
                System.out.println("Main Thread : " + i);
                Thread.sleep(1000);
            }
        } catch(InterruptedException e){
            System.out.println("Main interrupted.");
        }
        System.out.println("Exiting main thread.");
    }
}