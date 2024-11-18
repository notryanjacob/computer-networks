import java.util.Scanner;
import java.util.Random;

public class StopAndWaitFrameLost {
    private static final Random random = new Random();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter total number of frames: ");
        int totalFrames = scanner.nextInt();
        System.out.print("Enter timeout duration (in milliseconds): ");
        int timeout = scanner.nextInt();
        System.out.print("Enter frame loss probability (0-1): ");
        double frameLossProbability = scanner.nextDouble();
        int sequenceNumber = 0;

        for (int frameNumber = 1; frameNumber <= totalFrames; frameNumber++) {
            boolean frameReceived = false;

            while (!frameReceived) {
                System.out
                        .println("Sender: Sending Frame " + frameNumber + " (Sequence Number " + sequenceNumber + ")");
                if (random.nextDouble() > frameLossProbability) {
                    System.out.println(
                            "Receiver: Received Frame " + frameNumber + " (Sequence Number " + sequenceNumber + ")");
                    System.out.println("Receiver: Sending ACK " + sequenceNumber);
                    frameReceived = true;
                } else {
                    System.out.println("Frame lost in transmission");
                    try {
                        Thread.sleep(timeout);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println("Sender: Timeout, resending Frame " + frameNumber);
                }
            }
            sequenceNumber++;
        }
        System.out.println("Transmission complete!");
        scanner.close();
    }
}
