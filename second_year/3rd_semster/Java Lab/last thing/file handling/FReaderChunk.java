import java.io.FileReader;
import java.io.IOException;

public class FReaderChunk {
    public static void main(String[] args) {
        try (FileReader reader = new FileReader("test.txt")) {
            char[] buffer = new char[100]; // Buffer to hold characters
            int numCharsRead;

            // Read characters in chunks
            while ((numCharsRead = reader.read(buffer)) != -1) {
                System.out.print(new String(buffer, 0, numCharsRead));
            }

        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
