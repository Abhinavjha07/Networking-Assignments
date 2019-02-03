package Question2;
import java.io.*;
import java.util.*;
import java.net.*;

public class Client {
	private static PrintStream ps;
	private static InputStreamReader inProxy;
	private static BufferedReader buffProxy;
	public static String dept="";
	public static void main(String args[])throws Exception
	{
		Scanner sc=new Scanner(System.in);
		Socket sock=new Socket("localhost",8080);
		inProxy=new InputStreamReader(sock.getInputStream());
		buffProxy=new BufferedReader(inProxy);
		ps=new PrintStream(sock.getOutputStream());
		int flag=1;
		System.out.println("\nClient Started\n");
		while(true && flag==1)
		{
			System.out.println("\nEnter :\n1 to display the record of employee with highest salary.\n2 to Display the record of employees with particular department_Name\n3 to Display the record of employees who belong to the department with highest Employee_Count\n4 to Display record of the employee with secondhighest salary\n5 to exit\n");
			int t=sc.nextInt();
			sc.nextLine();
			switch(t)
			{
			case 1:
				displayHighestSalary();
				break;
			case 2:
				System.out.print("\nEnter the department name : ");
				dept=sc.nextLine();
				
				displaydept(dept);
				break;
			case 3:
				displayrecord();
				break;
			case 4:
				displaysecondhighest();
				break;
			case 5:
				flag=0;
				ps.println("Over");
				break;
			default:
				System.out.println("\nEnter the option from within the given menu.");
			}
		}
		sc.close();
		ps.close();
		buffProxy.close();
		inProxy.close();
		sock.close();
	}
	
	static void displayHighestSalary()throws Exception
	{
		System.out.println("\nServer Output:\n");
		ps.println("Highest Salary");
		ps.flush();
		System.out.println(buffProxy.readLine());
	}
	
	static void displaydept(String dept)throws Exception
	{
		System.out.println("\nServer Output:\n");
		ps.println("Print "+dept);
		ps.flush();
		String m="";
		while(!(m=buffProxy.readLine()).equals("break"))
		{
			System.out.println(m);
		}
	}
	static void displayrecord()throws Exception
	{
		System.out.println("\nServer Output:\n");
		ps.println("Employee Count");
		ps.flush();
		String m="";
		while(!(m=buffProxy.readLine()).equals("break"))
		{
			System.out.println(m);
		}
	}
	
	static void displaysecondhighest()throws Exception
	{
		System.out.println("\nServer Output:\n");
		ps.println("Second highest");
		ps.flush();
		System.out.println(buffProxy.readLine());
	}
}
