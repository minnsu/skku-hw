
public class EmployeeTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// 사람 이름과 초기 salary 값은?
		Employee em1 = new Employee("John", "Ewing", 3000); // employee1 : John Ewing, 3,000 as monthly salary
		Employee em2 = new Employee("Jack", "Sparrow", 100000); // employee2 : Jack Sparrow, 100,000 as monthly salary
		
		// print em1, em2's name and theirs monthly salary
		System.out.println(em1); 
		System.out.println(em2);

		// present salary is multiplied by 1.05 for a 5% increase
		em1.setM_Salary(1.05 * em1.getM_Salary());
		em2.setM_Salary(1.05 * em2.getM_Salary());
		System.out.println("After raise by 5%");
		
		// print em1, em2's name and theirs monthly salary after raise by 5%
		System.out.println(em1);
		System.out.println(em2);
	}

}
