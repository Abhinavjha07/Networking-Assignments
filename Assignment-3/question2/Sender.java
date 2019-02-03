package question2;
import java.net.*;

import java.io.*;
import java.util.*;

public class Sender {
	
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	
	public static String data="",ack;
	public static int c=0;
	public static int flag=0;
	public static long t=2000;
	public static long x=0,time=0;
	
	static void stop_and_wait()throws Exception
	{
		time=System.currentTimeMillis();
		p.println(data);
		
		ack=buff.readLine();
		
		if(flag==0 && System.currentTimeMillis()-time>t)
		{
			flag=1;
			x++;
		}
		else if(System.currentTimeMillis()-time < t+(x*500))
		{
		c++;
		if(ack.equals("Received"))
		{
			System.out.println("Acknowledgement is received!!");
			
			Thread.sleep(1000);
			
			System.out.printf("Frame number %d is sent successfully!!\n\n",c);
			flag=0;
		}
		else
		{
			System.out.println("Error!!");
			flag=1;
		}
		}
		else
		{
			x++;
			flag=1;
		}
	}
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		System.out.println("\nSender started!!\nWaiting for connection....");
		
		s=new ServerSocket(8888);
		sock=s.accept();
		
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		System.out.print("\nEnter the number of data frames to be sent -> ");
		int n=sc.nextInt();
		sc.nextLine();
		
		while(true)
		{
			
			if(flag==0)
			{
			System.out.print("\nEnter the data : ");
			data=sc.nextLine();
			x=0;
			}
			else if(flag==1)
			{
				System.out.println("\nTime Out in receiving the acknowledgement!\nTrying to resend the data...\n");
			}
			
			stop_and_wait();
			
			if(n==c)
			{
				p.println("break");
				break;
			}
		}
		
		System.out.println("\nClosing connection!!!\n");
		buff.close();
		p.close();
		in.close();
		sock.close();
		s.close();
		sc.close();
	}

}
