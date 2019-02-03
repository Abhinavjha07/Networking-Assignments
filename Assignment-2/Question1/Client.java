package Question1;
import java.net.*;
import java.io.*;

public class Client {
	public static void main(String args[]) throws Exception
	{
		Client c=new Client();
		c.run();
	}
	
	public void run() throws Exception
	{
		Socket sock=new Socket("localhost",8080);
		PrintStream ps=new PrintStream(sock.getOutputStream());
		ps.println("Hello Server");
		sock.close();
	}
}
