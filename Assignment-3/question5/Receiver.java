package question5;
import java.io.*;
import java.net.*;
import java.util.*;
public class Receiver {
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static ArrayList<Integer> row,col;
	
	static void check_rows(String s[])
	{
		int x=0;
		for(int i=0;i<s.length-1;i++)
		{
			x=0;
			
			for(int j=0;j<s[i].length()-1;j++)
			{
				if(s[i].charAt(j)=='1')
					x++;
			}
			
			if(x%2==0)
			{
				if(s[i].charAt(s[i].length()-1)=='1')
					row.add(i);
			}
			else 
			{
				if(s[i].charAt(s[i].length()-1)=='0')
					row.add(i);
			}
		}
	}
	
	
	static void check_col(String s[])
	{
		int x=0;
		for(int i=0;i<8;i++)
		{
			x=0;
			for(int j=0;j<s.length-1;j++)
			{
				if(s[j].charAt(i)=='1')
					x++;
			}
			
			if(x%2==0)
			{
				if(s[s.length-1].charAt(i)=='1')
					col.add(i);
			}
			else
			{
				if(s[s.length-1].charAt(i)=='0')
					col.add(i);
			}
		}
	}
	
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
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
				int x=Integer.parseInt(buff.readLine());
				String s[]=new String[x+1];
				
				System.out.println("\nThe received bit strings are : ");
				for(int i=0;i<x+1;i++)
				{
					s[i]=buff.readLine();
					System.out.println(s[i]);
				}
				
				row=new ArrayList<Integer>();
				col=new ArrayList<Integer>();
				
				check_rows(s);
				check_col(s);
				if(row.size()>0 && col.size()>0)
				{
					System.out.println("There are errors in : ");
				for(int i=0;i<row.size();i++)
				{
					for(int j=0;j<col.size();j++)
					{
						System.out.println("-> row : " + row.get(i) + "\t column : "+col.get(j));
					}
				}
				}
				else if(row.size()==0 && col.size() >0 )
				{
					System.out.println("There are errors in : ");
					
						for(int j=0;j<col.size();j++)
						{
							System.out.println("-> column : "+col.get(j));
						}
					
				}
				
				else if(col.size()==0 && row.size() >0 )
				{
					System.out.println("There are errors in : ");
					
						for(int j=0;j<row.size();j++)
						{
							System.out.println("-> row : " + row.get(j));
						}
					
				}
				else if(row.size()==0 && col.size()==0)
					System.out.println("There was no error in transmission!!");
			}
		}
		
		in.close();
		buff.close();
		s.close();
		
	}
}
