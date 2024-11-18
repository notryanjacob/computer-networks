import java.util.Scanner;

public class IPAddressCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter an IP address (e.g., 192.168.1.1) or 'quit' to exit: ");
            String ipAddress = scanner.nextLine();

            if (ipAddress.equalsIgnoreCase("quit")) {
                break;
            }

            System.out.print("Enter the number of desired subnets: ");
            int numSubnets = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            String[] octets = ipAddress.split("\\.");
            int firstOctet = Integer.parseInt(octets[0]);

            // Determine class and default subnet mask
            char ipClass;
            String defaultSubnetMask;
            if (firstOctet >= 1 && firstOctet <= 127) {
                ipClass = 'A';
                defaultSubnetMask = "255.0.0.0";
            } else if (firstOctet >= 128 && firstOctet <= 191) {
                ipClass = 'B';
                defaultSubnetMask = "255.255.0.0";
            } else if (firstOctet >= 192 && firstOctet <= 223) {
                ipClass = 'C';
                defaultSubnetMask = "255.255.255.0";
            } else {
                System.out.println("Invalid IP address or unsupported class.");
                continue;
            }

            // Calculate network address
            String networkAddress = calculateNetworkAddress(ipAddress, defaultSubnetMask);

            // Calculate subnet bits and new subnet mask
            int subnetBits = (int) Math.ceil(Math.log(numSubnets) / Math.log(2));
            String newSubnetMask = calculateNewSubnetMask(defaultSubnetMask, subnetBits);

            // Display results
            System.out.println("IP Class: " + ipClass);
            System.out.println("Network Address: " + networkAddress);
            System.out.println("Default Subnet Mask: " + defaultSubnetMask);
            System.out.println("New Subnet Mask: " + newSubnetMask);
            System.out.println("Number of subnets (2^n): " + (1 << subnetBits));

            // Divide into subnets
            System.out.println("\nSubnet Information:");
            divideIntoSubnets(networkAddress, newSubnetMask, numSubnets);

            System.out.println(); // Add a blank line for readability
        }

        scanner.close();
    }

    private static String calculateNetworkAddress(String ipAddress, String subnetMask) {
        String[] ipOctets = ipAddress.split("\\.");
        String[] maskOctets = subnetMask.split("\\.");
        int[] networkOctets = new int[4];

        for (int i = 0; i < 4; i++) {
            networkOctets[i] = Integer.parseInt(ipOctets[i]) & Integer.parseInt(maskOctets[i]);
        }

        return networkOctets[0] + "." + networkOctets[1] + "." + networkOctets[2] + "." + networkOctets[3];
    }

    private static String calculateNewSubnetMask(String defaultSubnetMask, int subnetBits) {
        int maskBits = 0;
        String[] maskOctets = defaultSubnetMask.split("\\.");
        for (String octet : maskOctets) {
            maskBits += Integer.bitCount(Integer.parseInt(octet));
        }

        int newMaskBits = maskBits + subnetBits;
        int[] newMaskOctets = new int[4];
        for (int i = 0; i < 4; i++) {
            if (newMaskBits >= 8) {
                newMaskOctets[i] = 255;
                newMaskBits -= 8;
            } else if (newMaskBits > 0) {
                newMaskOctets[i] = (int) (256 - Math.pow(2, 8 - newMaskBits));
                newMaskBits = 0;
            } else {
                newMaskOctets[i] = 0;
            }
        }

        return newMaskOctets[0] + "." + newMaskOctets[1] + "." + newMaskOctets[2] + "." + newMaskOctets[3];
    }

    private static void divideIntoSubnets(String networkAddress, String subnetMask, int numSubnets) {
        String[] networkOctets = networkAddress.split("\\.");
        String[] maskOctets = subnetMask.split("\\.");

        int subnetBits = (int) Math.ceil(Math.log(numSubnets) / Math.log(2));
        int maskBits = 0;
        for (String octet : maskOctets) {
            maskBits += Integer.bitCount(Integer.parseInt(octet));
        }
        int hostBits = 32 - maskBits;
        int subnetSize = (int) Math.pow(2, hostBits - subnetBits);

        for (int i = 0; i < numSubnets; i++) {
            int subnetId = i * subnetSize;
            String subnetStart = calculateSubnetAddress(networkAddress, subnetMask, subnetId);
            String subnetEnd = calculateSubnetAddress(networkAddress, subnetMask, subnetId + subnetSize - 1);

            System.out.println("Subnet " + (i + 1) + ":");
            System.out.println("  Network Address: " + subnetStart);
            System.out.println("  First Usable: " + calculateFirstAddress(subnetStart));
            System.out.println("  Last Usable: " + calculateLastAddress(subnetEnd));
            System.out.println("  Broadcast Address: " + subnetEnd);
        }
    }

    private static String calculateSubnetAddress(String networkAddress, String subnetMask, int subnetId) {
        String[] networkOctets = networkAddress.split("\\.");
        int[] subnetOctets = new int[4];

        int currentSubnetId = subnetId;
        for (int i = 3; i >= 0; i--) {
            int networkPart = Integer.parseInt(networkOctets[i]);
            subnetOctets[i] = (networkPart & Integer.parseInt(subnetMask.split("\\.")[i])) | (currentSubnetId % 256);
            currentSubnetId /= 256;
        }

        return subnetOctets[0] + "." + subnetOctets[1] + "." + subnetOctets[2] + "." + subnetOctets[3];
    }

    private static String calculateFirstAddress(String networkAddress) {
        String[] octets = networkAddress.split("\\.");
        int lastOctet = Integer.parseInt(octets[3]) + 1;
        octets[3] = String.valueOf(lastOctet);
        return String.join(".", octets);
    }

    private static String calculateLastAddress(String broadcastAddress) {
        String[] octets = broadcastAddress.split("\\.");
        int lastOctet = Integer.parseInt(octets[3]) - 1;
        octets[3] = String.valueOf(lastOctet);
        return String.join(".", octets);
    }
}