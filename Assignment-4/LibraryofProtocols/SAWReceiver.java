package LibraryofProtocols;
import java.io.*;
import java.net.*;
import java.util.*;
public class SAWReceiver {
	
	static ServerSocket s;
	static Socket sock;
	static ObjectInputStream in;
	static PrintStream p;
	static BufferedReader buff;
	public static void Main()throws Exception
	{
		s=new ServerSocket(8888);
		System.out.println("\nReceiver Started!!!\nWaiting for the sender to send data..\n");
		sock=s.accept();
		in=new ObjectInputStream(sock.getInputStream());
		p=new PrintStream(sock.getOutputStream());
		Random rn=new Random();
		buff=new BufferedReader(new InputStreamReader(sock.getInputStream()));
		while(true)
		{
			int x=rn.nextInt(4000);
			Frame1 f=(Frame1) in.readObject();
			if(f.data.equals("break") && f.ack==1 && f.seq_no==1)
				break;
			Thread.sleep(x);
			System.out.printf("\nFrame received :\nSequence_no. : %d\nData: %s\n",f.seq_no,f.data);
			
			if(x>3000)
			{
				System.out.println("But unable to send acknowledgement!!");
			}
			else
			{
				p.println("ok");
				System.out.println("Acknowledgemt sent!!");
			}
		}
		
		in.close();
		p.close();
		buff.close();
		sock.close();
		s.close();
	}
}
