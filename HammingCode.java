import java.util.Scanner;
import java.util.Vector;

public class HammingCode {

    // XOR operation between two vectors (lists)
    public static Vector<Integer> xorOperation(Vector<Integer> a, Vector<Integer> b) {
        Vector<Integer> result = new Vector<>(a.size());
        for (int i = 0; i < a.size(); ++i) {
            result.add((a.get(i).equals(b.get(i))) ? 0 : 1);
        }
        return result;
    }

    // Encode data with Hamming code
    public static String encodeHamming(String data) {
        if (data.length() != 8) {
            return "Error: Data length must be 8 bits";
        }

        // Convert data string to a vector of integers (bits)
        Vector<Integer> dataBits = new Vector<>(8);
        for (int i = 0; i < data.length(); i++) {
            dataBits.add(data.charAt(i) - '0');
        }

        // Initialize Hamming code array with 12 bits
        Vector<Integer> hammingCode = new Vector<>(12);
        for (int i = 0; i < 12; i++) {
            hammingCode.add(0);
        }
        //0,1,3,7

        // Place the data bits at specific positions in the Hamming code
        hammingCode.set(2, dataBits.get(0));
        hammingCode.set(4, dataBits.get(1));
        hammingCode.set(5, dataBits.get(2));
        hammingCode.set(6, dataBits.get(3));
        hammingCode.set(8, dataBits.get(4));
        hammingCode.set(9, dataBits.get(5));
        hammingCode.set(10, dataBits.get(6));
        hammingCode.set(11, dataBits.get(7));
        
        // Calculate r-bits (parity bits)
        hammingCode.set(0, hammingCode.get(2) ^ hammingCode.get(4) ^ hammingCode.get(6) ^ hammingCode.get(8)
                ^ hammingCode.get(10)); // r1
        hammingCode.set(1, hammingCode.get(2) ^ hammingCode.get(5) ^ hammingCode.get(6) ^ hammingCode.get(9)
                ^ hammingCode.get(10)); // r2
        hammingCode.set(3, hammingCode.get(4) ^ hammingCode.get(5) ^ hammingCode.get(6) ^ hammingCode.get(11)); // r4
        hammingCode.set(7, hammingCode.get(8) ^ hammingCode.get(9) ^ hammingCode.get(10) ^ hammingCode.get(11)); // r8

        // Print the r-bits after encoding
        System.out.println("r1 = " + hammingCode.get(0) + ", r2 = " + hammingCode.get(1) + ", r4 = "
                + hammingCode.get(3) + ", r8 = " + hammingCode.get(7));

        // Convert the Hamming code vector back to a string
        StringBuilder result = new StringBuilder();
        for (int bit : hammingCode) {
            result.append(bit);
        }
        return result.toString();
    }

    // Check the Hamming code for errors
    public static String checkHammingCode(String hammingCode) {
        if (hammingCode.length() != 12) {
            return "Error: Invalid length";
        }

        // Convert the Hamming code string to a vector of integers (bits)
        Vector<Integer> bits = new Vector<>(12);
        for (int i = 0; i < hammingCode.length(); i++) {
            bits.add(hammingCode.charAt(i) - '0');
        }

        // Extract the parity bits
        int p1 = bits.get(0);
        int p2 = bits.get(1);
        int p4 = bits.get(3);
        int p8 = bits.get(7);

        // Calculate the parity bits again from the received data
        int s1 = p1 ^ bits.get(2) ^ bits.get(4) ^ bits.get(6) ^ bits.get(8) ^ bits.get(10);
        int s2 = p2 ^ bits.get(2) ^ bits.get(5) ^ bits.get(6) ^ bits.get(9) ^ bits.get(10);
        int s4 = p4 ^ bits.get(4) ^ bits.get(5) ^ bits.get(6) ^ bits.get(11);
        int s8 = p8 ^ bits.get(8) ^ bits.get(9) ^ bits.get(10) ^ bits.get(11);

        // Calculate error position
        int errorCheck = s1 + (s2 * 2) + (s4 * 4) + (s8 * 8);

        // Print the calculated parity bits after receiving the code
        System.out.println("After receiving, s1 = " + s1 + ", s2 = " + s2 + ", s4 = " + s4 + ", s8 = " + s8);

        if (errorCheck == 0) {
            return "No Error";
        } else {
            return "Error at position " + errorCheck;
        }
    }

    // Simulate data transmission and Hamming code error checking
    public static void simulateDataTransmission(String data) {
        System.out.println("Original data: " + data);

        // Encode the data using Hamming code
        String encodedData = encodeHamming(data);
        System.out.println("Encoded Hamming Code (to be sent): " + encodedData);

        // Get the received data (with or without errors)
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter received Hamming Code: ");
        String receivedData = scanner.next();
        System.out.println("Received Data: " + receivedData);

        // Check the received Hamming code for errors
        String verificationResult = checkHammingCode(receivedData);
        System.out.println("Verification result: " + verificationResult);
    }

    public static void main(String[] args) {
        // Example data (8 bits)
        String data = "10101010";
        simulateDataTransmission(data);
    }
}