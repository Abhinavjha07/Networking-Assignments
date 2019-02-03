package question2;
import java.io.*;
import java.net.*;
import java.util.*;

public class Receiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		
		String buffer;
		while(true)
		{
			buffer=buff.readLine();
			
			if(buffer.equals("break"))
			{
				break;
			}
			
			System.out.println("\nFrame received successfully!!");
			Random rn=new Random();
			long x=rn.nextInt(3000);
			
			Thread.sleep(x);
			p.println("Received");
			Thread.sleep(1000);
			if(x<3000)
				System.out.println("\nData Received -> "+buffer);
		}
		
		System.out.println("Closing connection!!!");
		
		p.close();
		in.close();
		buff.close();
		s.close();
	}
}
