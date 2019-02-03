package LibraryofProtocols;
import java.io.*;
import java.net.*;
public class HammingReceiver {
	
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	
	
	static void check(String a,int parity_count)
	{
		int p;
		
		char b[]=a.toCharArray();
		
		int parity[]=new int[parity_count];
		String s="";
		
		for(p=0;p<parity_count;p++)
		{
			for(int i=0;i<a.length();i++)
			{
				int k=i+1;
				String x=Integer.toBinaryString(k);
				int bit=((Integer.parseInt(x))/((int)Math.pow(10, p)))%10;
				if(bit==1)
				{
					if(a.charAt(i)=='1')
					{
						parity[p]=(parity[p]+1)%2;
					}
				}
			}
			
			s=parity[p]+s;
		}
		
		int e=Integer.parseInt(s,2);
		if(e!=0)
		{
			System.out.println("Error is at location : "+e);
			
			if(b[e-1]=='1')
				b[e-1]='0';
			else b[e-1]='1';
			System.out.print("\nCorrected code is : ");
			for(int i=0;i<b.length;i++)
			{
				System.out.print(b[i]);
			}
			
			System.out.println();
		}
		else
			System.out.println("\nThere was no error in the received string!!");
		
		System.out.print("\nOriginal data sent was : ");
		p = 0;
		for(int i=1 ; i <=b.length ; i++) {
			if(Math.pow(2, p) != i) {
				System.out.print(b[i-1]);
			}
			else {
				p++;
			}
		}
		System.out.println();
	}
	
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		
		
		while(true)
		{
			String s=buff.readLine();
			
			if(s.equals("break"))
				break;
			else
			{
				System.out.println("\nReceived bit string is : "+s);
				int x=s.length();
				String p=Integer.toBinaryString(x);
				int parity_count=p.length();
				
				check(s,parity_count);
			}
		}
	}
}
