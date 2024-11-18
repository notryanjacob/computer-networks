public class BinaryChecksumCalculator {
    public static void main(String[] args) {
        String binary1 = "10101001";
        String binary2 = "00111001";

        int checksum = calculateBinaryChecksum(binary1, binary2);
        String binaryChecksum = String.format("%8s", Integer.toBinaryString(checksum)).replace(' ', '0');

        System.out.println("Binary number 1: " + binary1);
        System.out.println("Binary number 2: " + binary2);
        System.out.println("Checksum (binary): " + binaryChecksum);

        String dataWithChecksum = binary1 + binary2 + binaryChecksum;
        System.out.println("Data with checksum: " + dataWithChecksum);

        // Verify valid checksum
        boolean isValid = verifyChecksum(dataWithChecksum);
        System.out.println("Is checksum valid? " + isValid);

        // Demonstrate invalid checksum
        String invalidData = dataWithChecksum.substring(0, dataWithChecksum.length() - 1) +
                (dataWithChecksum.charAt(dataWithChecksum.length() - 1) == '0' ? '1' : '0');
        System.out.println("\nInvalid data: " + invalidData);
        isValid = verifyChecksum(invalidData);
        System.out.println("Is invalid checksum accepted? " + isValid);
    }

    public static int calculateBinaryChecksum(String binary1, String binary2) {
        int num1 = Integer.parseInt(binary1, 2);
        int num2 = Integer.parseInt(binary2, 2);

        int sum = num1 + num2;

        if (sum > 255) {
            sum = (sum & 0xFF) + 1;
        }

        return ~sum & 0xFF;
    }

    public static boolean verifyChecksum(String dataWithChecksum) {
        if (dataWithChecksum.length() != 24) { // 8 + 8 + 8 bits
            return false;
        }

        String binary1 = dataWithChecksum.substring(0, 8);
        String binary2 = dataWithChecksum.substring(8, 16);
        String receivedChecksum = dataWithChecksum.substring(16);

        int calculatedChecksum = calculateBinaryChecksum(binary1, binary2);
        String calculatedChecksumBinary = String.format("%8s", Integer.toBinaryString(calculatedChecksum)).replace(' ',
                '0');

        return receivedChecksum.equals(calculatedChecksumBinary);
    }
}