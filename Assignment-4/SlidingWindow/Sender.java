package SlidingWindow;
import java.util.*;
import java.io.*;
import java.net.*;
public class Sender {
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static String strbuff[];
	static String generate(int x)
	{
		int a=(int) Math.pow(2, x-1);
		int b=(int) Math.pow(2,x)-1;
		Random rn=new Random();
		long msg = rn.nextInt(b-a)+a;
		
		return Long.toBinaryString(msg);
	}
	
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		System.out.println("\nSender started!!\nWaiting for the connection....\n");
		s=new ServerSocket(8888);
		sock=s.accept();
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		sock.setSoTimeout(3500);
		int window,k=0;
		
		System.out.print("\nEnter the length of the window : ");
		window=sc.nextInt();
		
		p.println(Integer.toString(window));
		while(true)
		{
			strbuff=new String[window];
			k=0;
			System.out.println("\nEnter :\n1 to send data\n2 to exit\n");
			int c=sc.nextInt();
			if(c==2)
			{
				p.println("break");
				break;
			}
			else if(c==1)
			{
				p.println("sending");
				
				
				System.out.println("\nEnter the number of frames you want to send : ");
				int n=sc.nextInt();
				p.println(Integer.toString(n));
				if(n<=window)
				{
					System.out.printf("\nEnter %d frames to be send -> \n",n);
					for(int i=1;i<=n;i++)
					{
						System.out.print("\nEnter the length of bit string to be send : ");
						int x=sc.nextInt();
						String s=generate(x);
						System.out.println("\nGenerated bit string is : "+s);
						strbuff[k]=s;
						p.println(s);
						k=(k+1)%window;
					}
					
					window-=n;
					for(int i=1;i<=n;i++)
					{
						String buffer=buff.readLine();
						if(buffer.startsWith("Received"))
						{
							System.out.println("\nAcknowledgement received of frame : "+buffer.substring(8));
						}
					}
					
					window+=n;
					
				}
				else
				{
					System.out.println("\nThe number of frames exceeds the window size.\n");
				}
			}
		}
		
		in.close();
		buff.close();
		p.close();
		sock.close();
		s.close();
		sc.close();
	}
}
