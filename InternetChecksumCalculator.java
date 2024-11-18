import java.util.Random;

public class InternetChecksumCalculator {
    public static void main(String[] args) {
        // Example with valid data (will be accepted)
        String validData = generateRandomHexString(16); // 8 bytes (16 hex characters)
        String dataWithValidChecksum = appendChecksum(validData);
        System.out.println("Valid data example:");
        boolean isValid = verifyChecksum(dataWithValidChecksum);
        System.out.println("Data : " + dataWithValidChecksum);
        System.out.println("Data accepted: " + isValid);

        // Example with invalid data (will be rejected)
        String invalidData = dataWithValidChecksum.substring(0, dataWithValidChecksum.length() - 4) +
                (dataWithValidChecksum.charAt(dataWithValidChecksum.length() - 4) == 'F' ? '0' : 'F') +
                dataWithValidChecksum.substring(dataWithValidChecksum.length() - 3);
        System.out.println("\nInvalid data example:");
        isValid = verifyChecksum(invalidData);
        System.out.println("Data : " + invalidData);
        System.out.println("Data accepted: " + isValid);
    }

    public static String appendChecksum(String hexData) {
        int checksum = calculateChecksum(hexData);
        return hexData + String.format("%04X", checksum);
    }

    public static int calculateChecksum(String hexData) {
        int sum = 0;
        for (int i = 0; i < hexData.length(); i += 2) {
            int byteValue = Integer.parseInt(hexData.substring(i, i + 2), 16);
            sum += byteValue;
            if (sum > 0xFFFF) {
                sum = (sum & 0xFFFF) + 1;
            }
        }
        return ~sum & 0xFFFF; // One's complement
    }

    public static boolean verifyChecksum(String dataWithChecksum) {
        if (dataWithChecksum.length() < 4) {
            return false; // Not enough data for a checksum
        }
        String hexData = dataWithChecksum.substring(0, dataWithChecksum.length() - 4);
        int expectedChecksum = Integer.parseInt(dataWithChecksum.substring(dataWithChecksum.length() - 4), 16);
        int calculatedChecksum = calculateChecksum(hexData);
        return (calculatedChecksum & 0xFFFF) == expectedChecksum;
    }

    public static String generateRandomHexString(int length) {
        Random random = new Random();
        StringBuilder sb = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            sb.append(Integer.toHexString(random.nextInt(16)).toUpperCase());
        }
        return sb.toString();
    }
}
