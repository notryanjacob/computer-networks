import java.util.Scanner;
import java.util.Random;

public class GoBackNACKLost {
    private static Random random = new Random();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter sender window size: ");
        int windowSize = scanner.nextInt();

        System.out.print("Enter max sequence number: ");
        int maxSeqNum = scanner.nextInt();

        System.out.print("Enter total number of frames to be sent: ");
        int totalFrames = scanner.nextInt();

        System.out.print("Enter acknowledgement loss probability (0-1): ");
        double ackLossProbability = scanner.nextDouble();

        System.out.print("Enter timeout duration (in milliseconds): ");
        int timeout = scanner.nextInt();

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
                System.out.println("Receiver: Received Frame " + (i % maxSeqNum));
                System.out.println("Receiver: Sending ACK " + (i % maxSeqNum));

                if (random.nextDouble() > ackLossProbability) {
                    System.out.println("Sender: Received ACK " + (i % maxSeqNum));
                    base = i + 1;
                } else {
                    System.out.println("ACK " + (i % maxSeqNum) + " lost in transmission");
                    break;
                }
                System.out.println("-----------------------------");
            }

            // If not all frames were acknowledged, simulate timeout and go back
            if (base < nextSeqNum) {
                try {
                    Thread.sleep(timeout);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("Sender: Timeout, resending from frame " + (base % maxSeqNum));
                nextSeqNum = base;
            }
        }
        System.out.println("Transmission complete!");
    }
}
