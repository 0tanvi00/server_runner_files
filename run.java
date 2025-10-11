import static spark.Spark.*;
import java.io.*;

public class Server {
    public static void main(String[] args) {
        port(3000);
        get("/", (req, res) -> {
            callPythonScript();
            return "Java server is running!\n";
        });
    }

    private static void callPythonScript() {
        try {
            Process process = new ProcessBuilder("python", "test.py").start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedReader errReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println("Python script output: " + line);
            }
            while ((line = errReader.readLine()) != null) {
                System.err.println("Error from Python script: " + line);
            }
            int exitCode = process.waitFor();
            System.out.println("Python script exited with code " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
