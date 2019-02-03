package Question2;
import java.io.*;
import java.net.*;

public class Server {
	private static ServerSocket ss;
	private static Socket sock;
	private static InputStreamReader inProxy;
	private static BufferedReader buffProxy;
	private static PrintStream pp;
	public static void main(String args[]) throws Exception
	{
		String cwd=System.getProperty("user.dir");
		System.out.println(cwd);
		ss=new ServerSocket(8888);
		System.out.println("\nServer Started\n");
		sock=ss.accept();
		inProxy=new InputStreamReader(sock.getInputStream());
		buffProxy=new BufferedReader(inProxy);
		pp=new PrintStream(sock.getOutputStream());
		
		while(true)
		{
			String s=buffProxy.readLine();
			if(Proxy.count<0)
			{
			if(s.equals("Over"))
				break;
			}
			
			else
			{
				String path=cwd+"/"+s;//if in eclipse add /src
				
				pp.println(path);
				pp.flush();
			}
		}
		
		buffProxy.close();
		inProxy.close();
		pp.close();
		sock.close();
		ss.close();
	}
}
