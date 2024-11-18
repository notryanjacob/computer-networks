import java.util.Scanner;
import java.util.Random;

public class StopAndWaitACKLost {
    private static Random random = new Random();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter total number of frames: ");
        int totalFrames = scanner.nextInt();
        System.out.print("Enter timeout duration (in milliseconds): ");
        int timeout = scanner.nextInt();
        System.out.print("Enter acknowledgement loss probability (0-1): ");
        double ackLossProbability = scanner.nextDouble();
        int sequenceNumber = 0;
        for (int i = 0; i < totalFrames; i++) {
            boolean ackReceived = false;
            while (!ackReceived) {
                System.out.println("Sender: Sending Frame " + i);
                System.out.println("Receiver: Received Frame " + i);
                System.out.println("Receiver: Sending ACK " + sequenceNumber);
                if (random.nextDouble() > ackLossProbability) {
                    System.out.println("Sender: Received ACK " + sequenceNumber);
                    ackReceived = true;
                } else {
                    System.out.println("ACK lost in transmission");
                    try {
                        Thread.sleep(timeout);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println("Sender: Timeout, resending frame");
                }
            }
            sequenceNumber = 1 - sequenceNumber; // Toggle between 0 and 1
        }
        System.out.println("Transmission complete!");
    }
}