package Question3;
import java.net.*;
import java.io.*;
import java.util.*;

public class Client {
	private static Socket sock;
	private static InputStreamReader in;
	private static BufferedReader buff;
	private static PrintStream out;
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		if(args.length <2)
		sock=new Socket("localhost",8888);
		else
			sock=new Socket(args[0],Integer.parseInt(args[1]));
			
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		out=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
			System.out.print("\nType your text: ");
			String s=sc.nextLine();
			if(s.equals("Over"))
			{
				out.println("Over");
				break;
			}
			else
			{
				
				if(s.matches("^[0-9]*$"))
				{
					System.out.println("\nServer output: ");
					while(s.length()!=1)
					{
						out.println(s);
						
						s=buff.readLine();
						System.out.println(s);
					}
				}
				else
				{
				out.println(s);
				
				String ans=buff.readLine();
				System.out.println("\nServer output: "+ans);
				}
			}
		}
		
		System.out.println("\n\tClosing connection.");
		sc.close();
		buff.close();
		in.close();
		out.close();
		sock.close();
	}
}
