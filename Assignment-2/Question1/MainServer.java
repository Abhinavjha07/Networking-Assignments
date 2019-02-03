package Question1;
import java.io.*;
import java.net.*;

public class MainServer {
	public static void main(String args[]) throws Exception
	{
		MainServer s=new MainServer();
		s.run();
	}
	
	public void run() throws Exception
	{
		ServerSocket ss =new ServerSocket(8888);
		Socket sock=ss.accept();
		
		InputStreamReader in=new InputStreamReader(sock.getInputStream());
		BufferedReader buff=new BufferedReader(in);
		System.out.println(buff.readLine());
		sock.close();
		ss.close();
	}
}
