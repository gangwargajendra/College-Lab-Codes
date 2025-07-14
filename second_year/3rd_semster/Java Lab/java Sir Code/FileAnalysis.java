import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

// Thread class for counting words
class WordCountThread extends Thread {
    private String fileName;

    public WordCountThread(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void run() {
        int wordCount = 0;
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] words = line.split("\\s+"); // Splits line into words
                wordCount += words.length;
            }
            System.out.println("Total number of words: " + wordCount);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}

// Thread class for counting vowels
class VowelCountThread extends Thread {
    private String fileName;

    public VowelCountThread(String fileName) {
        this.fileName = fileName;
    }

    
    @Override
    public void run() {
        int vowelCount = 0;
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                for (char c : line.toLowerCase().toCharArray()) {
                    if ("aeiou".indexOf(c) != -1) {
                        vowelCount++;
                    }
                }
            }
            System.out.println("Total number of vowels: " + vowelCount);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}

// Main class to run both threads
public class FileAnalysis {
    public static void main(String[] args) {
        String fileName = "poem.txt";
        
        // Creating and starting WordCountThread
        WordCountThread wordCountThread = new WordCountThread(fileName);
        wordCountThread.start();
        
        // Creating and starting VowelCountThread
        VowelCountThread vowelCountThread = new VowelCountThread(fileName);
        vowelCountThread.start();
        
        try {
            // Waiting for both threads to finish
            wordCountThread.join();
            vowelCountThread.join();
        } catch (InterruptedException e) {
            System.out.println("Thread interrupted: " + e.getMessage());
        }
    }
}