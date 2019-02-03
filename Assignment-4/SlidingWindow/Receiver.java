package SlidingWindow;

import java.io.*;
import java.net.*;
public class Receiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	static String strbuff[];
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		String buffer="";
		int wsize=Integer.parseInt(buff.readLine());
		//s.setSoTimeout(3500);
		int k=0;
		while(true)
		{
			strbuff=new String[wsize];
			k=0;
			buffer=buff.readLine();
			if(buffer.equals("break"))
				break;
			else if(buffer.equals("sending"))
			{
				int n=Integer.parseInt(buff.readLine());
				
				if(n<=wsize)
				{
				for(int i=1;i<=n;i++)
				{
					String s=buff.readLine();
					strbuff[k]=s;
					k=(k+1)%wsize;
				}
				wsize-=n;
				for(int i=0;i<k;i++)
				{
					System.out.println("\nReceived bit string is : "+strbuff[i]);
					p.println("Received"+Integer.toString(i+1));
					System.out.printf("Acknowledgement sent of frame : %d\n\n",(i+1));
				}
				
				wsize+=n;
				}
			}
		}
		
		buff.close();
		in.close();
		p.close();
		s.close();
	}
}
