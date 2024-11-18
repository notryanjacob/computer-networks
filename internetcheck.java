public class internetcheck {
    public static void main(String[] args) {
        // Example with valid data
        String validData = "0001F203F4F5F6F7";
        String dataWithValidChecksum = appendChecksum(validData);
        System.out.println("Valid data example:");
        boolean isValid = verifyChecksum(dataWithValidChecksum);
        System.out.println("Data entered: " + validData);
        System.out.println("Checksum Calculated : " + String.format("%04X", calculateChecksum(validData)));
        System.out.println("Data with checksum: " + dataWithValidChecksum);
        System.out.println("Data accepted: " + isValid);

        // Example with invalid data (will be rejected)
        String invalidData = dataWithValidChecksum.substring(0, dataWithValidChecksum.length() - 4) +
                (dataWithValidChecksum.charAt(dataWithValidChecksum.length() - 4) == 'F' ? '0' : 'F') +
                dataWithValidChecksum.substring(dataWithValidChecksum.length() - 3);
        System.out.println("\nInvalid data example:");
        isValid = verifyChecksum(invalidData);
        System.out.println("Data: " + invalidData);
        System.out.println("Data accepted: " + isValid);
    }

    public static String appendChecksum(String hexData) {
        int checksum = calculateChecksum(hexData);
        return hexData + String.format("%04X", checksum);
    }

    public static int calculateChecksum(String hexData) {
        int sum = 0;
        for (int i = 0; i < hexData.length(); i += 4) {
            int wordValue = Integer.parseInt(hexData.substring(i, i + 4), 16);
            sum += wordValue;
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
        return calculatedChecksum == expectedChecksum;
    }
}