public class crc {
    // Function to perform CRC calculation
    public static String calculateCRC(String data, String divisor) {
        int dataLength = data.length();
        int divisorLength = divisor.length();
        // Append zeros to the data based on the length of the divisor
        StringBuilder paddedData = new StringBuilder(data);
        for (int i = 0; i < divisorLength - 1; i++) {
            paddedData.append("0");
        }
        // Perform division using XOR operation
        String result = divide(paddedData.toString(), divisor);
        return result;
    }

    // Helper function to perform division using XOR
    private static String divide(String data, String divisor) {
        int pointer = divisor.length();
        String temp = data.substring(0, pointer);
        while (pointer < data.length()) {
            if (temp.charAt(0) == '1') {
                temp = xor(divisor, temp) + data.charAt(pointer);
            } else {
                temp = xor("0".repeat(divisor.length()), temp) + data.charAt(pointer);
            }
            pointer++;
            temp = temp.substring(1);
        }
        if (temp.charAt(0) == '1') {
            temp = xor(divisor, temp);
        } else {
            temp = xor("0".repeat(divisor.length()), temp);
        }
        return temp.substring(1); // CRC remainder
    }

    // XOR function for binary strings
    private static String xor(String a, String b) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < a.length(); i++) {
            result.append(a.charAt(i) == b.charAt(i) ? '0' : '1');
        }
        return result.toString();
    }

    // Function to check if the received data is valid
    public static boolean checkCRC(String receivedData, String divisor) {
        // Remainder should be all zeros if no error
        String remainder = divide(receivedData, divisor);
        return !remainder.contains("1");
    }

    public static void main(String[] args) {
        System.out.println("\nTestcase 1: Valid Data\n");

        String data = "11010011101100"; // Original data
        String divisor = "1011"; // CRC-3 Polynomial
        // Calculate CRC value
        String crc = calculateCRC(data, divisor);
        System.out.println("Calculated CRC: " + crc);
        // Append CRC to the original data
        String transmittedData = data + crc;
        System.out.println("Transmitted Data: " + transmittedData);
        // Check if the transmitted data is valid
        boolean isValid = checkCRC(transmittedData, divisor);
        System.out.println("Data is " + (isValid ? "valid" : "corrupted"));

        System.out.println("\nTestcase 2: Corrupted Data\n");

        String corruptedData = transmittedData.substring(0, transmittedData.length() - 1)
                + (transmittedData.charAt(transmittedData.length() - 1) == '0' ? '1' : '0'); // Flip the last bit
        System.out.println("Corrupted Data: " + corruptedData);
        // Check if the corrupted data is valid
        boolean isCorrupted = checkCRC(corruptedData, divisor);
        System.out.println("Data is " + (isCorrupted ? "valid" : "corrupted"));
    }
}
