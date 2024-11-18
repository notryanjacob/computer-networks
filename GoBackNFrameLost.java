import java.util.Scanner;
import java.util.Random;

public class GoBackNFrameLost {
    private static Random random = new Random();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input parameters
        System.out.print("Enter sender window size: ");
        int windowSize = scanner.nextInt();
        System.out.print("Enter max sequence number: ");
        int maxSeqNum = scanner.nextInt();
        System.out.print("Enter total number of frames to be sent: ");
        int totalFrames = scanner.nextInt();
        System.out.print("Enter frame loss probability (0-1): ");
        double frameLossProbability = scanner.nextDouble();

        int base = 0;
        int nextSeqNum = 0;

        while (base < totalFrames) {
            // Send frames within the window
            while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) {
                System.out.println("Sender: Sending Frame " + (nextSeqNum % maxSeqNum));
                System.out.println("-----------------------------");
                nextSeqNum++;
            }

            // Simulate frame transmission and acknowledgment
            for (int i = base; i < nextSeqNum; i++) {
                if (random.nextDouble() > frameLossProbability) {
                    System.out.println("Receiver: Received Frame " + (i % maxSeqNum));
                    System.out.println("Receiver: Sending ACK " + (i % maxSeqNum));
                    base = i + 1; // Move base forward after successful acknowledgment
                } else {
                    System.out.println("Receiver: Frame " + (i % maxSeqNum) + " lost in transmission.");
                    break; // Simulate frame loss, go back to the lost frame
                }
                System.out.println("-----------------------------");
            }

            // If not all frames were acknowledged, go back and resend from base
            if (base < nextSeqNum) {
                System.out.println("Sender: Timeout, resending from frame " + (base % maxSeqNum));
                nextSeqNum = base; // Reset next sequence number to base to resend
            }
        }

        System.out.println("Transmission complete!");

        // Close the scanner to avoid resource leaks
        scanner.close();
    }
}
