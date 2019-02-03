package question1;

import java.io.*;
import java.net.*;
public class Sender extends Header{
	static String buffer;
	static int data;
	static ServerSocket s;
	static Socket sock;
	static PrintStream p;
	public static void main(String args[])throws Exception
	{
		System.out.println("\nSender started!!\nWaiting for connection....");
		s=new ServerSocket(8888);
		sock=s.accept();
		
		p=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
			from_network_layer();
			
			to_physical_layer(buffer);
			
			if(buffer.equals("Over"))
				break;
		}
		
		p.close();
		sock.close();
		s.close();
	}

}
