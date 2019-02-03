package Question3;
import java.io.*;
import java.net.*;


public class Server {
	private static ServerSocket ss;
	private static Socket sock;
	private static InputStreamReader in;
	private static BufferedReader buff;
	private static PrintStream out;
	public static void main(String args[]) throws Exception
	{
		System.out.println("\n\tServer Started\n\tWaiting for the connection...\n");
		ss=new ServerSocket(8888);
		sock=ss.accept();
		
		in=new InputStreamReader(sock.getInputStream());
		buff=new BufferedReader(in);
		out=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
			String s=buff.readLine();
			if(s.equals("Over"))
			{
				System.out.println("\n\tClient closed the connection.");
				break;
			}
			else
			{
			long sum=0;
			if(s.matches("^[0-9]*$"))
			{
				for(int i=0;i<s.length();i++)
				{
					int c=s.charAt(i)-'0';
					sum+=c;
				}
				
				out.println(Long.toString(sum));
				out.flush();
			}
			else
			{
				out.println("Sorry,cannot compute!!");
				out.flush();
			}
			}
		}
		System.out.println("\n\tClosing Server.");
		buff.close();
		out.close();
		in.close();
		sock.close();
		ss.close();
	}
}
