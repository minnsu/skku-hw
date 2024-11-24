import java.util.Stack;

public class CalculateFunction {
	public String answer;
	public int getPri(String op) { // get priority of operator
		if(op.equals("x") || op.equals("/")) {
			return 1;
		}
		else if(op.equals("+") || op.equals("-")) {
			return 2;
		}
		return 100;
	}
	public String in2Post(String infix) { // change infix to postfix
		String split[] = infix.split(" "); // split text in calculator
		Stack<String> opStack = new Stack<String>(); // operator stack
		String postfix = "";
		int opPriority;
		float value;
		for(int i = 0; i < split.length; i++) { // number of splits element
			try{
				value = Float.parseFloat(split[i]); // if split part is number
				postfix = postfix + String.format("%f ", value); // add that number to postfix string
			} catch(NumberFormatException e1) { // if error occur : split part is not a number
				opPriority = getPri(split[i]); // find operator priority
				while(!opStack.isEmpty() && getPri(opStack.peek()) <= opPriority) {
					// while stack is not empty and stack top's priority has small or equal to now operator
					postfix = postfix + opStack.pop() + " "; // pop the value and add to postfix string
				}
				opStack.push(split[i]); // push now operator to operator stack 
			}
		}
		while(!opStack.isEmpty()) { // while stack is not empty
			postfix = postfix + opStack.pop() + " "; // pop the value and add to postfix string
		}
		return postfix;
	}

	private float calcOp(String op, String pop1, String pop2) { // calculate the value by pop value and operator
		float num1 = Float.parseFloat(pop1); // parse string to number
		float num2 = Float.parseFloat(pop2);
		switch(op) {
		case "+": // add
			return num2 + num1;
		case "-": // sub
			return num2 - num1;
		case "x": // mul
			return num2 * num1;
		case "/": // div
			return num2 / num1;
		}
		return 0.0f;
	}
	
	public void calc(String postfix) { // calculate the value using postfix string
		Stack<String> answer = new Stack<String>();
		String split[] = postfix.split(" "); // split postfix string
		float value;
		for(int i = 0; i < split.length; i++) { // iterate number of splits elements
			try {
				value = Float.parseFloat(split[i]); // if splits value is number
				answer.push(String.format("%f", value)); // push to answer stack that number
			}
			catch(NumberFormatException e1) { // if splits value is operator
				value = calcOp(split[i], answer.pop(), answer.pop()); // pop two value from stack and calculate the value
				answer.push(String.format("%f", value)); // and push to answer stack
			}
		}
		this.answer = answer.pop(); // set answer instance to last element of stack
	}
}