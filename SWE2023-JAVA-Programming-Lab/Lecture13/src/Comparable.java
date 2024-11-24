
public interface Comparable<T> {
	public T method(T var);
}

class example<T> implements Comparable<T>{

	@Override
	public T method(T var) {
		// TODO Auto-generated method stub
		return var;
	}
	
	public static void main(String[] args) {
		example object = new <Integer> example();
		System.out.println(object.method(123));
	}
}