package Question2;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;

public class ProxyThread extends Thread
{
	private Socket sock;
	 public PrintStream pClient;
	
	 public InputStreamReader inClient;
	 public BufferedReader buffClient;
	public Scanner sc;
	
	
public ProxyThread(Socket sock)
{
	this.sock=sock;
}
public void run()
{
	try
	{
	
	inClient=new InputStreamReader(sock.getInputStream());
	buffClient =new BufferedReader(inClient);
	pClient=new PrintStream(sock.getOutputStream());
	
	
	while(true)
	{
	
	String m=buffClient.readLine();
	
	if(m.equals("Over"))
	{
		break;
	}
	else if(m.equals("Highest Salary"))
	{
		if(Proxy.files.containsKey("employee.txt"))
		employeehighest(1);
		else
		{
			System.out.println("\nFetching file...");
			Proxy.pServer.println("employee.txt");
			Proxy.pServer.flush();
			String path=Proxy.buffServer.readLine();
			
			Proxy.files.put("employee.txt", path);
			employeehighest(1);
		}
	}
	
	else if(m.startsWith("Print"))
	{
		String dept[]=m.split(" ");
		if(Proxy.files.containsKey("employee.txt"))
		print(dept[1]);
		else
		{
			System.out.println("Fetching file...");
			Proxy.pServer.println("employee.txt");
			Proxy.pServer.flush();
			String path=Proxy.buffServer.readLine();
		
			Proxy.files.put("employee.txt", path);
			print(dept[1]);
		}
	}
	else if(m.equals("Employee Count"))
	{
		for(String j : Proxy.files.keySet())
		{
			System.out.println(Proxy.files.get(j));
		}
		if(Proxy.files.containsKey("employee.txt") && Proxy.files.containsKey("department.txt"))
			employee_count();
			else
			{
				System.out.println("Fetching file...");
				Proxy.pServer.println("employee.txt");
				Proxy.pServer.flush();
				String path=Proxy.buffServer.readLine();
				
				if(!Proxy.files.containsKey("employee.txt"))
				Proxy.files.put("employee.txt", path);
				
				Proxy.pServer.println("department.txt");
				Proxy.pServer.flush();
				path=Proxy.buffServer.readLine();
				
				Proxy.files.put("department.txt", path);
				employee_count();
			}
	}
	
	else if(m.equals("Second highest"))
	{
		if(Proxy.files.containsKey("employee.txt"))
			employeehighest(2);
			else
			{
				System.out.println("Fetching file...");
				Proxy.pServer.println("employee.txt");
				Proxy.pServer.flush();
				String path=Proxy.buffServer.readLine();
				
				Proxy.files.put("employee.txt", path);
				employeehighest(2);
			}
	}
	}
	
	
	
	buffClient.close();
	
	inClient.close();
	pClient.close();
	sock.close();
	}catch(Exception e)
	{
		
	}
	finally{
		Proxy.count--;
		
	}
}
	


void employeehighest(int k)
{
	String max="",s="",smax="";
	String[] x;
	int m=0,sm=0;
	
	try
	{
	sc=new Scanner(new File(Proxy.files.get("employee.txt")));
	while(sc.hasNextLine())
	{
		s=sc.nextLine();
		
		x=s.split(" ");
		if(x[0].equals("Name"))
			continue;
		else
		{
			if(m<Integer.parseInt(x[1]))
			{
				sm=m;
				smax=max;
				m=Integer.parseInt(x[1]);
				max=s;
			}
			
			else if(m>Integer.parseInt(x[1]) && sm<Integer.parseInt(x[1]))
			{
				smax=s;
				sm=Integer.parseInt(x[1]);
			}
		}
	}
	}catch(Exception e)
	{
		System.out.println(e);
	}
	finally
	{
		sc.close();
	}
	
	if(k==1)
	{
	pClient.println(max);
	pClient.flush();
	}
	else if(k==2)
	{
		pClient.println(smax);
		pClient.flush();
	}
	
}

void print(String dept)
{
	
	
	String s="";
	try
	{
		
		sc=new Scanner(new File(Proxy.files.get("employee.txt")));
		
		while(sc.hasNextLine())
		{
			s=sc.nextLine();
			String x[]=s.split(" ");
			if(x[0].equals("Name"))
				continue;
			if(x[2].equals(dept))
			{
				pClient.println(s);
			}
		}
		pClient.println("break");
		pClient.flush();
	}catch(Exception e)
	{
		System.out.println(e);
	}
	finally
	{
		sc.close();
	}
}

void employee_count()
{
	
	try
	{
	Scanner x=new Scanner(new File(Proxy.files.get("department.txt")));
	
	sc=new Scanner(new File(Proxy.files.get("employee.txt")));

	String m="";
	int p=0;
	while(x.hasNextLine())
	{
		String s[]=x.nextLine().split(" ");
		if(s[0].equals("Name"))
			continue;
		if(p<Integer.parseInt(s[1]))
		{
			p=Integer.parseInt(s[1]);
			m=s[0];
		}
	}
	x.close();
	
	while(sc.hasNextLine())
	{
		String b=sc.nextLine();
		String a[]=b.split(" ");
		if(a[0].equals("Name"))
			continue;
		if(a[2].equals(m))
		{
			pClient.println(b);
			pClient.flush();
		}
	}
	pClient.println("break");
	pClient.flush();
	sc.close();
	}catch(Exception e)
	{
		System.out.println(e);
	}


}
}



