package question7;
import java.util.*;
import java.io.*;
import java.net.*;

public class Sender {
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	
	public static int hex2decimal(String s)
    {
             String digits = "0123456789ABCDEF";
             s = s.toUpperCase();
             int val = 0;
             for (int i = 0; i < s.length(); i++)
             {
                 char c = s.charAt(i);
                 int d = digits.indexOf(c);
                 val = 16*val + d;
             }
             return val;
    }
	
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
		String hex="7E";
		int flag=hex2decimal(hex);
		s=new ServerSocket(8888);
		System.out.println("\nSender started!!\nWaiting for the connection....");
		sock=s.accept();
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
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
				System.out.print("\nEnter the length of bit string to be sent : ");
				int x=sc.nextInt();
				String data=generate(x);
				//String data="11111111";
				System.out.println("\nGenerated bit string is : "+data);
				String d="";
				int count=0;
				for(int i=0;i<data.length();i++)
				{
					if(data.charAt(i)=='1')
					{
						count++;
						d+=data.charAt(i);
						if(count==5)
						{
							d+="0";
							count=0;
						}
					}
					else if(data.charAt(i)=='0')
					{
						d+=data.charAt(i);
						count=0;
					}
				}
				
				System.out.println("\nBit string after bit stuffing : "+d);
				data="0"+Integer.toBinaryString(flag)+d+"0"+Integer.toBinaryString(flag);
				System.out.println("\nBit string aftter adding the flag bits : "+data);
				p.println(data);
			}
		}
		
		sc.close();
		in.close();
		buff.close();
		p.close();
		sock.close();
		s.close();
	}

}
