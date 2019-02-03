package Question2;


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.*;
import java.util.*;
public class Proxy {
	static private ServerSocket ss;
	public static int count=1;
	static public Socket sck;
static public PrintStream pServer;
	
	static public InputStreamReader inServer;
	static public BufferedReader buffServer;
	static public HashMap<String,String> files=new HashMap<String,String>();
	public static void main(String args[])throws Exception
	{
		ss =new ServerSocket(8080);
		sck=new Socket("localhost",8888);
		System.out.println("Proxy Server Started\n");
		boolean listening =true;
		inServer=new InputStreamReader(Proxy.sck.getInputStream());
		buffServer =new BufferedReader(inServer);
		pServer=new PrintStream(Proxy.sck.getOutputStream());
		while(listening)
		{
			new ProxyThread(ss.accept()).start();
			count++;
		}
		
		buffServer.close();
		inServer.close();
		pServer.close();
		ss.close();
		sck.close();
		
	}
	
}