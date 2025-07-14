import java.util.*;

public class Operation {
	private int operand1;
	private String operator;
	private int operand2;
	public double result;
	
	public Operation(int operand1,String operator , int operand2){
		this.operand1 = operand1;
		this.operator = operator;
		this.operand2 = operand2;
	}
	public void calculateValue(){
		if("+".equals(operator)){
			result = operand1 + operand2;
		}else if("-".equals(operator)){
			result = operand1 - operand2;
		}else if("*".equals(operator)){
			result = operand1 * operand2;
		}else if("/".equals(operator)){
			result = ((double)operand1) / operand2;
		}else{
			System.out.println("invalid condition");
			result = 0;
		}
	}
	public void displayResult(){
		System.out.println(operand1+" "+operator+" "+operand2+" = "+result);
	}
	
}