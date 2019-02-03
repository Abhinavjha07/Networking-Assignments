package LibraryofProtocols;

import java.util.*;
import java.io.*;
import java.net.*;
public class GoBackSender {
	
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static int window;
	static String strbuff[];
	ArrayList<Integer> notReceived;
	static int k=0,seqNo=0,lastReceived=0,n;
	static String generate(int x)
	{
		int a=(int) Math.pow(2, x-1);
		int b=(int) Math.pow(2,x)-1;
		Random rn=new Random();
		long msg = rn.nextInt(b-a)+a;
		
		return Long.toBinaryString(msg);
	}
	
	static String sequence_number(int x,int l)
	{
		String s=Integer.toBinaryString(x);
		String data="";
		for(int i=0;i<(l-s.length());i++)
		{
			data+="0";
		}
		data+=s;
		return data;
	}
	
	static void receive_ack(int l)throws Exception
	{
		p.println(Integer.toString(l));
		
		while(l<=n)
		{
			String s=buff.readLine();
			if(!s.equals("error"))
			{
			int x=Integer.parseInt(s);
			
			lastReceived = x;
				
				System.out.printf("\nAcknowledgement received of frame : %d\n",x);
			
			l++;
			}
			else
			{
				if(lastReceived>0)
				{
				System.out.printf("\nERROR induced\nLast acknowledgment received of frame : %d\n",lastReceived);
				System.out.printf("Trying to resend the frame from %d\n",lastReceived+1);
				}
				break;
			}
			
		}
		
	}
	
	static void Senddata(String data,int i)
	{
		
		strbuff[k]=data;
		
		k=(k+1)%window;
		
		String flag=sequence_number(i,seqNo);
		data=flag+data;
		p.println(data);
	}
	
	
	public static void Main()throws Exception
	{
		Scanner sc=new Scanner(System.in);
		s=new ServerSocket(8888);
		System.out.println("\nSender started!!\nWaiting for the connection...\n");
		sock=s.accept();
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		sock.setSoTimeout(3500);
		System.out.print("\nEnter the size of the window : ");
		window=sc.nextInt();
		
		p.println(Integer.toString(window));
		while(true)
		{
			strbuff=new String[window];
			k=0;
			lastReceived=0;
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
				System.out.print("\nEnter the number of frames you want to send : ");
				n=sc.nextInt();
				seqNo=(Integer.toBinaryString(n)).length()+1;
				p.println(Integer.toString(n));
				p.println(Integer.toString(seqNo));
				
				if(n<=window)
				{
					System.out.printf("\n------Enter %d frames to send--------\n",n);
					for(int i=1;i<=n;i++)
					{
						System.out.printf("\nEnter the size of the bit string to be sent : ");
						int x=sc.nextInt();
						String data=generate(x);
						
						System.out.println("\nGenerated data is : "+data);
						Senddata(data,i);
					}
					
					
					receive_ack(1);
					
					while(lastReceived<n)
					{
						receive_ack(lastReceived+1);
					}
					
					p.println("allReceived");
				}
				else
				{
					System.out.println("\nThe number of frames exceeds the window size.\n");
				}
			}
			
		}
		
		
		buff.close();
		in.close();
		p.close();
		sock.close();
		s.close();
	}
}
