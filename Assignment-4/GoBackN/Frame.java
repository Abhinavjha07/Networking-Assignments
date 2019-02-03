package GoBackN;
import java.io.Serializable;

public class Frame  implements Serializable {
	
	 /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String data;
	int seq_no;
	 int ack;
	
	public Frame(String d,int s,int a)
	{
		data=d;
		seq_no=s;
		ack=a;
	}
}
