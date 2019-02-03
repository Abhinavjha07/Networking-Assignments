package Selective;
import java.io.*;
import java.net.*;
import java.util.*;
public class Receiver {
	
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static ObjectInputStream inObject;
	static ObjectOutputStream out;
	
	public static int window,k=0,n,sent=0,flag=0;
	static Frame buffer[];
	static Random rn;
	
	
	static void send_ack(int l)throws Exception
	{
		int x=0;
		if(flag==0)
		{
			for(int i=0;i<n;i++)
			{
				if(x==0)
				System.out.printf("\nTrying to send the acknowledgement of frame %d\n",i+1);
				int z=rn.nextInt(10)%3;
				if(z!=1)
				{
					buffer[i].ack="1";
					out.writeObject(buffer[i]);
					if(x==0)
					{
					System.out.println("Received bit string is : "+buffer[i].Data);
					sent++;
					System.out.printf("Acknowledgement of frame %d is sent\n\n",(i+1));
					}
					else
					{
						System.out.printf("\nFrame %d is stored in buffer",(i+1));
						sent++;
					}
				}

				else
				{
					System.out.printf("Error occured while sending the acknowledgement of frame : %d\n",i+1);
					x=1;
				}		
			}
		}
		
		else
		{
			
			buffer[l].ack="1";
			out.writeObject(buffer[l]);
			sent++;
			
			System.out.printf("\n\nTrying to send the acknowledgement of frame %d\n",l+1);
			System.out.println("Received bit string is : "+buffer[l].Data);
			System.out.printf("Acknowledgement of frame %d is sent\n\n",l+1);
		}
	}
	
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		inObject=new ObjectInputStream(s.getInputStream());
		out=new ObjectOutputStream(s.getOutputStream());
		//s.setSoTimeout(3500);
		rn=new Random();
		window=Integer.parseInt(buff.readLine());
		System.out.printf("\nThe window size is : %d\n",window);
		buffer=new Frame[window];
		int instance=1;
		while(true)
		{
			System.out.printf("\n\n-------Instance -> %d --------\n\n",instance);
			instance++;
			k=0;
			buffer=new Frame[window];
			sent=0;
			String s=buff.readLine();
			if(s.equals("break"))
				break;
			else if(s.equals("sending"))
			{
				n=Integer.parseInt(buff.readLine());
				if(n<=window)
				{
					for(int i=0;i<n;i++)
					{
					Frame f=(Frame) inObject.readObject();
					buffer[k]=f;
					k=(k+1)%window;
				
					}
				flag=0;
				int x=Integer.parseInt(buff.readLine());
				send_ack(x);
				
				Frame f=new Frame("break",0,"1");
				out.writeObject(f);
				
				flag=1;
				while(sent<n)
				{
					x=Integer.parseInt(buff.readLine());
					
					send_ack(x);
				}
				}
			}		
		}
		
		buff.close();
		in.close();
		inObject.close();
		
		out.close();
		s.close();
	}
}
