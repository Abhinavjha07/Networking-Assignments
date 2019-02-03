package LibraryofProtocols;
import java.util.*;
import java.io.*;
import java.net.*;
public class SenderCheckSum {
	static ServerSocket s;
	static Socket sock;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	public static String a="",b="";
	static Random rn;
	
	static void makeEqualLength(String str1, String str2)
	{
	    int len1 = str1.length();
	    int len2 = str2.length();
	    if (len1 < len2)
	    {
	        for (int i = 0 ; i < len2 - len1 ; i++)
	            str1 = '0' + str1;
	    }
	    else if (len1 > len2)
	    {
	        for (int i = 0 ; i < len1 - len2 ; i++)
	            str2 = '0' + str2;
	    }
	    
	    a=str1;
	    b=str2;
	    
	}
	 
	static String addBitStrings( String first, String second )
	{
	    String result="";  
	 
	  
	    makeEqualLength(first, second);
	 
	    int carry = 0; 
	 
	    for (int i =a.length()-1  ; i >= 0 ; i--)
	    {
	        int firstBit = a.charAt(i) - '0';
	        int secondBit = b.charAt(i) - '0';
	 
	       
	        int sum = (firstBit ^ secondBit ^ carry)+'0';
	 
	        result = (char)sum + result;
	 
	  
	        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
	    }
	 
	    
	    if (carry==1)
	        addBitStrings(result,"1");
	 
	    return result;
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
	
	public static void Main()throws Exception
	{
		Scanner sc=new Scanner(System.in);
		System.out.println("\nSender started!!\nWaiting for connection....");
		s=new ServerSocket(8888);
		sock=s.accept();
		
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(sock.getOutputStream());
		rn=new Random();
		int c=0;
		while(true)
		{
			System.out.println("\nEnter : \n1 to send data\n2 to exit\n");
			c=sc.nextInt();
			if(c==2)
			{
				p.println("break");
				break;
			}
			else if(c==1)
			{
				p.println("sending");
				String res="";
				System.out.print("\nEnter the number of frames you want to send : ");
				int x=sc.nextInt();
				p.println(Integer.toString(x));
				sc.nextLine();
				
				for(int i=0;i<x;i++)
				{
					System.out.print("\nEnter the bit String : ");
					String s=sc.nextLine();
					
					if(i==0)
						res = addBitStrings(s,"0");
					else
						res = addBitStrings(s,res);	
					
					int z=rn.nextInt(10)%4;
					if(z==1)
					s=induce_error(s);
					p.println(s);
				}
				
				String checkSum="";
				
				for(int i=0;i<res.length();i++)
				{
					if(res.charAt(i)=='1')
						checkSum+="0";
					else checkSum+="1";
				}
				System.out.println("\nCheckSum generated -> "+checkSum);
				int z=rn.nextInt(10)%10;
				if(z==1)
				checkSum=induce_error(checkSum);
				p.println(checkSum);
			}
		}
		
		
	}
}
