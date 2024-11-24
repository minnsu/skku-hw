import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class TestSet {
	public static void main(String[] args) {
		Set<Integer> setDataStructure = new HashSet<Integer>();
		setDataStructure.add(12);
		setDataStructure.add(8);
		setDataStructure.add(12);
		setDataStructure.add(9);
		setDataStructure.add(1);
		for (Integer i : setDataStructure) {
			System.out.println(i);
			
		}
	
	}
}
