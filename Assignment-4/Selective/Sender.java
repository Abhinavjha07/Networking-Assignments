package Selective;
import java.util.*;
import java.io.*;
import java.net.*;

public class Sender {
	
	static ServerSocket s;
	static Socket sock;
	static ObjectInputStream in;
	static ObjectOutputStream out; 
	static PrintStream p;
	static int window,k=0,received=0;
	static Frame buffer[];
	
	static String generate(int x)
	{
		int a=(int) Math.pow(2, x-1);
		int b=(int) Math.pow(2,x)-1;
		Random rn=new Random();
		long msg = rn.nextInt(b-a)+a;
		
		return Long.toBinaryString(msg);
	}
	
	static void receive_ack(int l)throws Exception
	{
		int z=0;
		if(l==-1)
		{
			p.println(Integer.toString(0));
			while(true)
			{
				
					Frame f=(Frame) in.readObject();
					
					
					if(f.Data.equals("break"))
						break;
				
					
					int x=Integer.parseInt(f.Seq_No,2);
					if(x-z<=1)
					{
					buffer[x-1].ack="1";
					received++;
					System.out.printf("\nAcknowledgement of frame %d is received\n",x);
					z=x;
					}
					else
					{
						buffer[x-1].ack="1";
						received++;
					}
				
			}
		}
		else
		{
		p.println(Integer.toString(l));
		Frame f=(Frame)in.readObject();
		String s=f.Seq_No;
		int x=Integer.parseInt(s,2);
		System.out.printf("\nAcknowledgement of frame %d is received\n",x);
		received++;
		buffer[x-1].ack="1";
		}
	}
	
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		s=new ServerSocket(8888);
		
		System.out.println("\nSender Started!!\nWaiting for the connection...");
		sock=s.accept();
		
		out=new ObjectOutputStream(sock.getOutputStream());
		
		in=new ObjectInputStream(sock.getInputStream());
		sock.setSoTimeout(3500);
		
		p=new PrintStream(sock.getOutputStream());
		
		System.out.printf("\nEnter the size of the window : ");
		window=sc.nextInt();
		p.println(Integer.toString(window));
		buffer=new Frame[window];
		while(true)
		{
			buffer=new Frame[window];
			k=0;
			received=0;
			System.out.println("\nEnter :\n1 to send data\n2 to exit");
			int c=sc.nextInt();
			if(c==2)
			{
				p.println("break");
				break;
			}
			else if(c==1)
			{
				p.println("sending");
				System.out.printf("\nEnter the number of frames to be sent : ");
				int n=sc.nextInt();
				
				p.println(Integer.toString(n));
				
				if(n>window)
				{
					System.out.println("\nThe number of frame exceeds the window size.");
				}
				else
				{
					System.out.printf("\n------Enter %d frames to send--------\n",n);
					for(int i=1;i<=n;i++)
					{
					System.out.printf("\nEnter the size of bit string to be sent : ");
					int x=sc.nextInt();
					String s=generate(x);
					System.out.println("\nGenerated bit string is : "+s);
					Frame f=new Frame(s,i,"0");
					
					buffer[k]=f;
					k=(k+1)%window;
					out.writeObject(f);
					}
					
					receive_ack(-1);
					while(received<n)
					{
						for(int i=0;i<n;i++)
						{
							if(buffer[i].ack.equals("0"))
							{
								receive_ack(i);
							
							for(int j=i+1;j<n;j++)
							{
								if(buffer[j].ack.equals("1"))
								{
									System.out.printf("\nAcknowledgement of frame %d is received\n",(j+1));
								}
								else
									break;
							}
							}
						}
					}
				}
				
				
			}
		}
		
		sc.close();
		in.close();
		out.close();
		p.close();
		sock.close();
		s.close();
	}
}
