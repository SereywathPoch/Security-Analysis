// File: HashChecker.java
import java.io.*;
import java.security.*;
import java.util.*;

public class HashChecker {

    public static String sha256(File file) throws Exception {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        FileInputStream fis = new FileInputStream(file);

        byte[] byteArray = new byte[1024];
        int bytesCount = 0;

        while ((bytesCount = fis.read(byteArray)) != -1) {
            digest.update(byteArray, 0, bytesCount);
        }

        fis.close();

        byte[] bytes = digest.digest();

        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }

        return sb.toString();
    }

    public static void main(String[] args) throws Exception {

        File folder = new File("SecurityFiles");
        File[] files = folder.listFiles();

        PrintWriter report = new PrintWriter("hash_report.csv");
        report.println("File,SHA256");

        for (File file : files) {
            if (file.isFile()) {
                String hash = sha256(file);
                report.println(file.getName() + "," + hash);
            }
        }

        report.close();

        System.out.println("Hash report generated: hash_report.csv");
    }
}
// Compile: javac HashChecker.java
// Run: java HashChecker