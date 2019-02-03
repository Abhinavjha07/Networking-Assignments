package question7;
import java.io.*;
import java.net.*;

public class Receiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	
	
	static String removeflag(String data)
	{
		return data.substring(8,data.length()-8);
	}
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		
		
		while(true)
		{
			String buffer=buff.readLine();
			if(buffer.equals("break"))
			{
				break;
			}
			else if(buffer.equals("sending"))
			{
				buffer=buff.readLine();
				System.out.println("\nFrame received : "+buffer);
				String data=removeflag(buffer);
				
				String d="";
				int count=0;
				for(int i=0;i<data.length();i++)
				{
					if(data.charAt(i)=='1')
					{
						count++;
						d+=data.charAt(i);
						if(count==5)
						{
							i++;
							count=0;
						}
					}
					else if(data.charAt(i)=='0')
					{
						d+=data.charAt(i);
						count=0;
					}
				}
				
				System.out.println("Original data is : "+d);
			}
		}
		
		in.close();
		buff.close();
		s.close();
		
	}
}
