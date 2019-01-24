import java.math.BigInteger;
import java.util.Scanner;
import java.io.File;

class BigNum {
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File("BigNum.inp"));
            BigInteger a = scanner.nextBigInteger();
            BigInteger b = new BigInteger("19283192319861041312312756");
            System.out.println("a: " + a);
            System.out.println("b: " + b);
            System.out.println("-a: " + a.negate());
            System.out.println("a + b: " + a.add(b));
            System.out.println("a - b: " + a.subtract(b));
            System.out.println("a * b: " + a.multiply(b));
            System.out.println("a / b: " + a.divide(b));
            System.out.println("a % b: " + a.mod(b));
            System.out.println("a ^ 3: " + a.pow(3));
            System.out.println("gcd(a, b): " + a.gcd(b));
        }
        catch (Exception exception) {
            exception.printStackTrace();
        }
    }
}
