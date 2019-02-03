package LibraryofProtocols;

import java.io.*;
import java.net.*;
import java.util.*;

public class GoBackReceiver {
	
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static String strbuff[];
	static int n,seq,k,window,last=0;
	static Random rn;
	
	static int generateSeq(String data)
	{
		return Integer.parseInt(data,2);
	}
	
	static void receive_data(int n)throws Exception
	{
		for(int i=0;i<n;i++)
		{
		String data=buff.readLine();
		strbuff[k]=data.substring(seq);
		k=(k+1)%window;
		}
	}
	
	static void sendack(int l)throws Exception
	{
		
		int i=l;
		while(i<=n)
		{
			System.out.printf("\nTrying to send the acknowledgement of %dth frame!!\n",(i));
			int z=rn.nextInt(10)%3;
			if(z!=0)
			{
				p.println(Integer.toString(i));
				
				if(i-last<=1)
				{
					last=i;
				}
			
				System.out.println("\nReceived bit string is : "+strbuff[i-1]);
				
				System.out.printf("Acknowledgement of frame %d is sent\n\n",(i));
				
				i++;
			}
			else
			{
				p.println("error");
				
				System.out.println("Error occured while sending acknowledgement of the frame!!");
				break;
			}
			
		}
		
	}
	
	public static void main(String args[])throws Exception
	{
		
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		rn=new Random();
		window=Integer.parseInt(buff.readLine());
		
		String buffer="";
		System.out.printf("\nThe window size is : %d\n",window);
		int instance=1;
		while(true)
		{
			System.out.printf("\n------Instance -> %d-------\n",instance);
			instance++;
			last=0;
			strbuff=new String[window];
			k=0;
			buffer=buff.readLine();
			if(buffer.equals("break"))
				break;
			else if(buffer.equals("sending"))
			{
				n=Integer.parseInt(buff.readLine());
				seq=Integer.parseInt(buff.readLine());
				if(n<=window)
				{
				receive_data(n);
				
				int l=Integer.parseInt(buff.readLine());
				
				sendack(l);
				String z="";
				while(true)
				{
					z=buff.readLine();
					
					if(z.equals("allReceived"))
						break;
					l=Integer.parseInt(z);
					sendack(l);
				}	
				}
			}
		}
		
		buff.close();
		in.close();
		p.close();
		s.close();
	}
}
