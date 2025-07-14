class Task extends Thread {
    private String taskName;

    public Task(String taskName) {
        this.taskName = taskName;
    }

    @Override
    public void run() {
        System.out.println(taskName + " is starting.");
        try {
            // Simulating task completion time with sleep
            Thread.sleep(1000);  // Sleep for 1 second
        } catch (InterruptedException e) {
            System.out.println(taskName + " was interrupted.");
        }
        System.out.println(taskName + " has completed.");
    }
}

public class JoinExample {
    public static void main(String[] args) {
        // Creating threads for each task
        Task task1 = new Task("Task 1");
        Task task2 = new Task("Task 2");
        Task task3 = new Task("Task 3");

        // Start the first thread
        task1.start();

        try {
            // Wait for task1 to complete before starting task2
            task1.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        // Start the second thread
        task2.start();

        try {
            // Wait for task2 to complete before starting task3
            task2.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        // Start the third thread
        task3.start();

        try {
            // Wait for task3 to complete before finishing main thread
            task3.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("All tasks have completed.");
    }
}
