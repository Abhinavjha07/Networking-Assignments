package question1;
import java.util.*;

public class Header {
	private static Scanner sc=new Scanner(System.in);
	
	
	public static void from_network_layer()
	{	
		System.out.println("\nType your text - ");
		Sender.buffer=sc.nextLine();
	}
	
	public static void to_physical_layer(String s) throws Exception
	{
		Sender.p.println(s);
	}
	
	public static void to_network_layer(String s) 
	{
			System.out.println(s);
	}
	
	public static void from_physical_layer() throws Exception
	{	
		Receiver.buffer = Receiver.buff.readLine();
	}
	
	
}
