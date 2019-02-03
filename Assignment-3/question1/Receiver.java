package question1;


import java.io.*;
import java.net.*;
public class Receiver extends Header{
	
	static Socket s;
	static InputStreamReader in;
	static BufferedReader buff;
	static String buffer;
	public static void main(String args[])throws Exception
	{
		s=new Socket("localhost",8888);
		in=new InputStreamReader(s.getInputStream());
		buff=new BufferedReader(in);
		
		while(true)
		{
		
		from_physical_layer();
		if(buffer.equals("Over"))
			break;
		System.out.print("Output -> ");
		to_network_layer(buffer);
		}
		
		buff.close();
		in.close();
		s.close();
	}

}
