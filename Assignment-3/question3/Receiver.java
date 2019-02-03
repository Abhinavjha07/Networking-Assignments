package question3;
import java.net.*;
import java.io.*;

public class Receiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static boolean check(String s,int k)
	{
		int c=0;
		for(int i=0;i<s.length();i++)
		{
			if(s.charAt(i)=='1')
				c++;
		}
		
		if((c%2==0 && k==1) || (c%2!=0 && k==2))
		{
			return true;
		}
		return false;
	}
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		while(true)
		{
			String s=buff.readLine();
			Thread.sleep(500);
			p.println("Received");
			if(s.equals("1"))
			System.out.println("\n----Even Parity----");
			else if(s.equals("2"))
				System.out.println("\n----Odd Parity----");	
			else if(s.equals("Over"))
				break;
			
			int c=Integer.parseInt(s);
			String msg=buff.readLine();
			if(c==1)
			{
				if(check(msg,1))
				{
					System.out.println("Message received is : "+msg);
					p.println("Received");
				}
				else
				{
					System.out.printf("There was a error in the message - %s",msg);
					p.println("error");
				}	
			}
			
			else if(c==2)
			{
				if(check(msg,2))
				{
					System.out.println("Message received is : "+msg);
					p.println("Received");
				}
				else
				{
					System.out.printf("There was a error in the message - %s",msg);
					p.println("error");
				}	
			}
			
		}
		
		buff.close();
		in.close();
		p.close();
		s.close();
	}

}
