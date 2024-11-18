import java.util.*;

public class sr_arq1 {

    // Constants
    private static final int TOTAL_FRAMES = 10;
    private static final int WINDOW_SIZE = 4;
    private static final int FRAME_LOSS_CHANCE = 0; // 0% chance
    private static final int ACK_LOSS_CHANCE = 20; // 20% chance

    private static final Random random = new Random();

    // Simulate sending a frame with a chance of frame loss
    public static boolean sendFrame(int frameID) {
        if (random.nextInt(100) < FRAME_LOSS_CHANCE) {
            System.out.println("Frame " + frameID + " lost in transmission.");
            return false;
        }
        System.out.println("Frame " + frameID + " sent successfully.");
        return true;
    }

    // Simulate receiving an acknowledgment with a chance of loss
    public static boolean receiveAck(int frameID) {
        if (random.nextInt(100) < ACK_LOSS_CHANCE) {
            System.out.println("Acknowledgment for frame " + frameID + " lost.");
            return false;
        }
        System.out.println("Acknowledgment for frame " + frameID + " received.");
        return true;
    }

    public static void main(String[] args) {
        boolean[] frameStatus = new boolean[TOTAL_FRAMES]; // To track acknowledged frames
        int sendBase = 0; // Base of the window (oldest unacknowledged frame)
        int nextFrameToSend = 0; // Next frame to be sent

        while (sendBase < TOTAL_FRAMES) {
            // Send frames within the window size
            while (nextFrameToSend < sendBase + WINDOW_SIZE && nextFrameToSend < TOTAL_FRAMES) {
                if (!frameStatus[nextFrameToSend]) {
                    // Simulate sending the frame
                    if (sendFrame(nextFrameToSend)) {
                        // Simulate receiving acknowledgment
                        if (receiveAck(nextFrameToSend)) {
                            frameStatus[nextFrameToSend] = true;
                        }
                    }
                }
                nextFrameToSend++;
            }

            // Slide the window if base frame is acknowledged
            while (sendBase < TOTAL_FRAMES && frameStatus[sendBase]) {
                System.out.println("Sliding window, frame " + sendBase + " acknowledged.");
                sendBase++;
            }

            // Resend unacknowledged frames within the window
            for (int i = sendBase; i < Math.min(sendBase + WINDOW_SIZE, TOTAL_FRAMES); i++) {
                if (!frameStatus[i]) {
                    System.out.println("Resending frame " + i);
                    if (sendFrame(i) && receiveAck(i)) {
                        frameStatus[i] = true;
                    }
                }
            }

            // Pause to simulate time delay between frames
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("All frames sent and acknowledged successfully.");
    }
}