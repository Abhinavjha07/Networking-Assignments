package LibraryofProtocols;

import java.io.*;
import java.net.*;
public class CRCReceiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	
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
	
	
	static boolean check(String msg,String gen)
	{
		String rem = remainder(msg,gen);
		for(int i=0;i<rem.length();i++)
		{
			if(rem.charAt(i)=='1')
			{
				return false;
			}
		}
		
		return true;
	}
	
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		String buffer="";
		String gen="",msg="";
		int flag=0;
		while(true)
		{
			if(flag==0)
			buffer=buff.readLine();
			
			if(buffer.equals("break"))
				break;
			
			else
			{
				if(flag==0)
				{
					gen=buffer;
					System.out.println("Generator polynomial is : "+gen);
					p.println("Ok");	
				}
				
				msg=buff.readLine();
				
				if(check(msg,gen))
				{
					System.out.println("\nPacket Received successfully!!\n\nData Received : "+msg.substring(0, msg.length()-gen.length()+1));
					p.println("Received");
					flag=0;
				}
				else
				{
					flag=1;
					System.out.println("\nThere was an error induced during transmission of packet");
					p.println("Error");
				}
			}
		}
		
		p.close();
		buff.close();
		in.close();
		s.close();
	}
	
}
