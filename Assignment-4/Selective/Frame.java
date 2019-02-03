package Selective;
import java.io.*;
public class Frame implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public String Seq_No,Data,ack;
	
	public Frame(String data,int no,String ack)
	{
		String fno=Integer.toBinaryString(no);
		this.Seq_No=fno;
		this.Data=data;
		this.ack=ack;
	}
}
 

