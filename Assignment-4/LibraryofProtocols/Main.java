package LibraryofProtocols;

import java.util.Scanner;

public class Main {
	static Scanner scanner;
	public static void main(String args[])throws Exception
	{
		
		while(true)
		{
		scanner=new Scanner(System.in);
		System.out.println("\nEnter :\n1 to send data using Stop and wait\n2 to use CRC\n3 to use checkSum\n4 to use hamming code\n5 to use Go back N\n6 to use Selective repeat\n7 to exit\n");
		int option=scanner.nextInt();
		if(option==1)
		{
			SAWReceiver.Main();
		}
		else if(option==2)
		{
			CRCSender.Main();
		}
		else if(option==3)
		{
		
			SenderCheckSum.Main();
		}
		else if(option==4)
		{
			HammingSender.Main();
		}
		else if(option==5)
		{
			
			GoBackSender.Main();
		}
		else if(option==6)
		{
			
			SelectiveSender.Main();
		}
		else if(option==7)
			break;
			
		}
		
		scanner.close();
	}

}
