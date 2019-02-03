package question4;

import java.io.*;
import java.net.*;
public class ReceiverCheckSum {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static PrintStream p;
	
	
	public static String a="",b="";
	
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
	
	static String complement(String s)
	{
		String ans="";
		for(int i=0;i<s.length();i++)
		{
			if(s.charAt(i)=='1')
				ans+="0";
			else ans+="1";
		}
		
		return ans;
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
	
	public static void main(String ags[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		p=new PrintStream(s.getOutputStream());
		String buffer="";
		while(true)
		{
			buffer=buff.readLine();
			
			if(buffer.equals("break"))
			{
				break;
			}
			else if(buffer.equals("sending"))
			{
				String res="";
				int x=Integer.parseInt(buff.readLine());
				
				for(int i=0;i<x;i++)
				{
					String s=buff.readLine();
					System.out.println("\nData received -> "+s);
					System.out.println();
					if(i==0)
						res = addBitStrings(s,"0");
					else
						res = addBitStrings(s,res);	
				}
				
				String checkSum=buff.readLine();
				System.out.println("\nCheckSum received -> "+checkSum);
				System.out.println();
				res=addBitStrings(checkSum,res);
				checkSum=complement(res);
				
				int flag=0;
				for(int i=0;i<checkSum.length();i++)
				{
					if(checkSum.charAt(i)=='1')
					{
						flag=1;
						break;
					}
				}
				
				if(flag==1)
				{
					System.out.println("\nThere was error induced during transmission of data!!!\n");
				}
				else
					System.out.println("\nAccepted!!\nBlocks received sucessfully without any errors!!!\n");
			}
		}
		buff.close();
		in.close();
		p.close();
		s.close();
	}
}	
