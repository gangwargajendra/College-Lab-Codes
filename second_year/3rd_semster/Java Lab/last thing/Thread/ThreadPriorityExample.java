public class ThreadPriorityExample extends Thread {
    public void run() {
        System.out.println("Inside the run() method");
    }
	
    public static void main(String argvs[]) {
        ThreadPriorityExample th1 = new ThreadPriorityExample();
        ThreadPriorityExample th2 = new ThreadPriorityExample();

        System.out.println("Priority of the thread th1 is : " + th1.getPriority());
        System.out.println("Priority of the thread th2 is : " + th2.getPriority());

        th1.setPriority(6);
        th2.setPriority(3);

        System.out.println("Priority of the thread th1 is : " + th1.getPriority());
        System.out.println("Priority of the thread th2 is : " + th2.getPriority());


        Thread.currentThread().setPriority(10);

        System.out.println("Priority of the main thread is : " + Thread.currentThread().getPriority());
    
		System.out.println("Is main thread a daemon? " + Thread.currentThread().isDaemon());
	}
}