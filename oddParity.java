import java.util.Scanner;

public class oddParity {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a binary string: ");
        String binaryString = scanner.nextLine();
        if (checkOddParity(binaryString)) {
            System.out.println("Data accepted (odd parity correct)");
        } else {
            System.out.println("Data rejected (odd parity error)");
        }
    }

    public static boolean checkOddParity(String binaryString) {
        int onesCount = 0;
        for (char c : binaryString.toCharArray()) {
            if (c == '1') {
                onesCount++;
            }
        }
        return onesCount % 2 == 1;
    }
}