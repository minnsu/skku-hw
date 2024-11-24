import java.util.*;

public class TestBoxing {
	public static void main(String[] args) {
		Vector dataStructure = new Vector<String>();

		dataStructure.add("Hello");
		String array[] = { "world!", "Java", "Interesting" };
		for (String s : array) {
			dataStructure.add(s);
		}

		// print all elements of the vector
		for (int i = 0; i < dataStructure.size(); i++) {

			System.out.println(dataStructure.get(i));
		}

		// print all elements of the vector using iterator

		ListIterator e = dataStructure.listIterator(); // pointer
		System.out.println("-------------------");
		while (e.hasNext()) { // update / write
			String currentValue = (String) e.next();
			e.set(currentValue + "++");
		}
		// e = dataStructure.listIterator(); // reset the pointer
		while (e.hasPrevious()) { // read
			System.out.println(e.previous());
		}

	}
}
