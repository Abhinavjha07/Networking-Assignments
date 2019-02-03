package Question1;
import java.net.*;
import java.io.*;

public class ProxyServer
{
	public static void main(String args[]) throws Exception
	{
		run();
	}
	
	public static void run() throws Exception
	{
		
		ServerSocket ss =new ServerSocket(8080);
		Socket sock=ss.accept();
		
		InputStreamReader in=new InputStreamReader(sock.getInputStream());
		BufferedReader buff =new BufferedReader(in);
		
		String m="";
		m=buff.readLine();
		System.out.println(m);
		Socket sck=new Socket("localhost",8888);
		PrintStream p=new PrintStream(sck.getOutputStream());
		p.println("Hey Server\n, Client says: "+m);
		sck.close();
		sock.close();
		ss.close();
	}
}
