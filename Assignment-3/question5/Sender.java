package question5;
import java.util.*;
import java.io.*;
import java.net.*;
public class Sender {
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static Random rn;
	
	static int check(String s)
	{
		int c=0;
		for(int i=0;i<s.length();i++)
		{
			if(s.charAt(i)=='1')
				c++;
		}
		
		if(c%2==0)
			return 0;
		else return 1;
	}
	
	static String induce_error(String data)
	{
		
		char x[]=data.toCharArray();
		
		for(int i=0;i<rn.nextInt(10)%4;i++)
		{
			int z=rn.nextInt(data.length());
			
			if(x[z]=='1')
				x[z]='0';
			else x[z]='1';
		}
			String ans="";
			for(int i=0;i<x.length;i++)
			{
				ans+=x[i];
			}
		return ans;
	}
	
	public static void main(String args[])throws Exception
	{
		s=new ServerSocket(8888);
		System.out.println("Sender started!!\nWaiting for the connecction....");
		sock=s.accept();
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		Scanner sc=new Scanner(System.in);
		System.out.println("\nEach block will be 8 bits long\n");
		while(true)
		{
			System.out.println("\nEnter:\n1 to send data\n2 to exit");
			int c=sc.nextInt();
			if(c==2)
			{
				p.println("break");
				break;
			}
			else if(c==1)
			{
			p.println("sending");
			System.out.print("Enter the number of blocks to be sent : ");
			int x=sc.nextInt();
			sc.nextLine();
			String s[]=new String[x+1];
			p.println(Integer.toString(x));
			for(int i=0;i<x;i++)
			{
				System.out.print("\nEnter the bit string : ");
				String str=sc.nextLine();
				if(str.length()==8)
				{
				s[i]=str;
				
				if(check(s[i])==0)
					s[i]=s[i]+"0";
				else if(check(s[i])==1)
					s[i]+="1";
				
				}
				else
					System.out.println("Enter the bit strings of length 8\n");
			}
			int cnt=0;
			String str="";
			for(int i=0;i<9;i++)
			{
				cnt=0;
				for(int j=0;j<x;j++)
				{
					if(s[j].charAt(i)=='1')
						cnt++;
				}
				if(cnt%2==0)
					str+="0";
				
				else str+="1";
			}
			s[x]=str;
			System.out.println("\nThe bit string are : ");
			for(int i=0;i<s.length;i++)
			{
				System.out.println(s[i]);
				rn=new Random();
				if(rn.nextInt(10)%3==1)
				{
					s[i]=induce_error(s[i]);
				}
				
				p.println(s[i]);
			}
			}
		}
		sc.close();
		p.close();
		buff.close();
		in.close();
		sock.close();
		s.close();
	}
}
