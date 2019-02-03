import java.io.*;
import java.util.*;
import java.net.*;
public class SW1Sender {
	
	static Socket sock;
	
	static BufferedReader buff;
	static ObjectOutputStream out;
	
	static PrintStream p;
	static Random rn;
	
	static String generate(int x)
	{
		String data="";
		for(int i=0;i<x;i++)
		{
			data+=Integer.toString(rn.nextInt(1024)%2);
		}
		
		return data;
	}
	public static void main(String args[])throws Exception
	{
		sock=new Socket("localhost",8888);
		System.out.println("\nConnected to the receiver!!");
		Scanner sc=new Scanner(System.in);
		buff=new BufferedReader(new InputStreamReader(sock.getInputStream()));
		p=new PrintStream(sock.getOutputStream());
		
		out=new ObjectOutputStream(sock.getOutputStream());
		rn=new Random();
		boolean flag=true;
		String data="";
		sock.setSoTimeout(2*1000+500);
		int x=0,k=1;
		boolean ack=true;
		while(true)
		{
			
			if(flag==true)
			{
			System.out.println("\nEnter:\n1 to send data\n2 to exit\n");
			int c=sc.nextInt();
			if(c==1)
			{
				System.out.print("\nEnter the length of data to be sent : ");
				x=sc.nextInt();
				data=generate(x);
			}
			else if(c==2)
			{
				Frame f=new Frame("break",1,1);
				out.writeObject(f);
				out.flush();
				break;
			}
			else
			{
				System.out.println("\nEnter the valid option!!");
				continue;
			}
			
			}
			System.out.println("\n\nData to be sent : "+data);
			
			Frame f=new Frame(data,k,0);
			
			
			
			ack=false;
			
			long curTime=System.currentTimeMillis();
			out.writeObject(f);
			out.flush();
			
			if(ack==false)
			{
			while(System.currentTimeMillis()-curTime<=3000)
			{
				String s="";
				try
				{
				s=buff.readLine();
				}catch(Exception e)
				{
				}
				
				if(s.equals("ok"))
				{
					ack=true;
					flag=true;
					k++;
					System.out.printf("\nAcknowledment received of frame %d having data %s\n",f.seq_no,f.data);
				}
				break;
			}
			}
			
			if(ack==false)
			{
				System.out.printf("\nTimeout in receiving the acknowledgement of frame %d\nTrying to resend the frame\n",f.seq_no);
				flag=false;
			}
			
		}
		sc.close();
		
		p.close();
		buff.close();
		out.close();
		sock.close();
	}
}
