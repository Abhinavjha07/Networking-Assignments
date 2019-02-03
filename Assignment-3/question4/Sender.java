package question4;
import java.io.*;
import java.util.*;
import java.net.*;

//Cyclic Redundancy check using the generator polynomial.

public class Sender {
	
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static String data="";
	static Random rn;
	public static int flag=0;
	static String generate(int x)
	{
		int a=(int) Math.pow(2, x-1);
		int b=(int) Math.pow(2,x)-1;
		Random rn=new Random();
		long msg = rn.nextInt(b-a)+a;
		
		return Long.toBinaryString(msg);
	}
	
	static String xor(String a,String b)
	{
		String r="";
		
		for(int i=1;i<b.length();i++)
		{
			if(a.charAt(i)==b.charAt(i))
			{
				r+="0";
			}
			else
				r+="1";
		}
		
		return r;
	}
	
	
	static String induce_error()
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
	
	static String remainder(String data,String key)
	{
		int l=key.length();
		
		String temp=data.substring(0, l);
		while(l<data.length())
		{
			if(temp.charAt(0)=='1')
			{
				temp = xor(key,temp) + data.charAt(l);
			}
			else
			{
				String x="";
				for(int i=0;i<l;i++)
				{
					x+="0";
				}
				temp = xor(x,temp)+data.charAt(l);
			}
			l++;
		}
		
		if(temp.charAt(0)=='1')
		{
			temp=xor(key,temp);
		}
		else
		{
			String x="";
			for(int i=0;i<l;i++)
			{
				x+="0";
			}
			temp = xor(x,temp);
		}
		
		return temp;
	}
	
	static String encode_data(String data,String key)
	{
		for(int i=0;i<key.length()-1;i++)
		{
			data+="0";
		}
		
		String rem = remainder(data,key);
		return rem;
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
		String buffer=""; 
		int c=0;
		while(true)
		{
			if(flag==0)
			{
			System.out.println("\nEnter :\n1 to send data\n2 to exit\n");
			c=sc.nextInt();
			sc.nextLine();
			}
			if(c==2)
			{
				p.println("break");
				break;
			}
			
			else if(c==1)
			{
				if(flag==0)
				{
				System.out.print("\nEnter the generator polynomial(in binary without space) : ");
				String gen=sc.nextLine();
				p.println(gen);
				
				buffer=buff.readLine();
				if(buffer.equals("Ok"))
				System.out.print("\nOk!!\nReceiver has agreed to use the generator polynomial\n\nEnter the length of data to be sent : ");
				int x=sc.nextInt();
				
				data=generate(x);
				
				System.out.println("\nBit String generated is : "+data);
				
				data= data+encode_data(data,gen);
				System.out.println("\nEncoded data : "+data);
				}
				
				rn=new Random();
				int z=rn.nextInt(10)%3;
				if(z==1)
				{
					String msg = induce_error();
					p.println(msg);
				}
				else
				{
					p.println(data);
				}
				
				
				buffer=buff.readLine();
				
				if(buffer.equals("Received"))
				{
					System.out.println("Data has been received by the receiver correctly!!");
					flag=0;
				}
				else if(buffer.equals("Error"))
				{
					System.out.println("\nError has been introduced while transmission\n\ntrying to resend the data....");
					flag=1;
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
