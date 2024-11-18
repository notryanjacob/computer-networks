import java.util.HashMap;
import java.util.Scanner;

public class evenParity {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a binary string: ");
        String binaryString = scanner.nextLine();
        if (checkOddParity(binaryString)) {
            System.out.println("Data accepted (even parity correct)");
        } else {
            System.out.println("Data rejected (even parity error)");
        }
    }

    public static boolean checkOddParity(String binaryString) {
        int onesCount = 0;
        for (char c : binaryString.toCharArray()) {
            if (c == '1') {
                onesCount++;
            }
        }
        return onesCount % 2 == 0;
    }
}