package question3;

import java.net.*;
import java.util.*;
import java.io.*;

public class Sender {
	
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		s=new ServerSocket(8888);
		System.out.println("Sender started!!\n Waiting for the receiver....");
		
		sock=s.accept();
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
			System.out.println("\nEnter\n1 to choose even parity\n2 to choose odd parity\n3 to exit\n");
			int c=sc.nextInt();
			if(c==3)
			{
				p.println("Over");
				break;
			}
			p.println(Integer.toString(c));
			
			Thread.sleep(500);
			String s=buff.readLine();
			if(s.equals("Received"))
			{
				if(c==1)
				System.out.println("\nReceiver agreed on using the even parity.");
				else if(c==2)
					System.out.println("\nReceiver agreed on using the odd parity.");
			}
			
			System.out.print("\n Enter the length of bit string : ");
			int n=sc.nextInt();
			n-=1;
			int a=(int) Math.pow(2, n-1);
			int b=(int) Math.pow(2,n)-1;
			Random rn=new Random();
			long x = rn.nextInt(b-a)+a;
			
			String msg=Long.toBinaryString(x);
			
			System.out.println("Generated message is : "+msg);
			p.println(msg);
			
			Thread.sleep(1000);
			
			s=buff.readLine();
			if(s.equals("Received"))
			{
				System.out.println("Message Received by the receiver!!");
			}
			if(s.equals("error"))
			{
				System.out.println("ERROR was intrdouced in transmission!!");
				
			}
		}
		
		sc.close();
		buff.close();
		in.close();
		p.close();
		sock.close();
		s.close();
	}
}
