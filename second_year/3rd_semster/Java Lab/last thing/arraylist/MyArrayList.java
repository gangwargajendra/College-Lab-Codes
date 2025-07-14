import java.util.*;

public class MyArrayList {
	
	void displayList(ArrayList<String> aList){
		Iterator<String> iter = aList.iterator();
		System.out.print("Elements are: ");
		while (iter.hasNext())
			System.out.print(iter.next() + " ");		
	}
	
	void insertList1(ArrayList<String> aList){
		 aList.add("2");
		 aList.add("1");
		 aList.add("3");
		 aList.add("5");
		 aList.add("4");
	}
	
	void insertList2(ArrayList<String> aList){
		 aList.add("6");
		 aList.add("7");
		 aList.add("9");
		 aList.add("10");
		 aList.add("8");
		 aList.add("1");
		 aList.add("1");
	}
	
	void insertList3(ArrayList<String> aList){
		 aList.add("5");
		 aList.add("4");
	}
	
	public static void main(String[] args) {
		
		MyArrayList obj = new MyArrayList();
		
		/*Create First and Second ArrayList*/
		 ArrayList<String> aList1 = new ArrayList<String>();
		 ArrayList<String> aList2 = new ArrayList<String>();
		 obj.insertList1(aList1);
		 obj.insertList2(aList2);
		 
		 /*Get elements of first array list into an array*/
		 String[] strArray = new String[aList1.size()]; 
		 aList1.toArray(strArray);
		 System.out.print("String Array: ");
		 for(int i = 0;i<strArray.length;i++){
			 System.out.print(strArray[i] + " ");
		 }
		 System.out.println();
		 
		 /*Display First ArrayList*/
		 System.out.print("First List ");
		 obj.displayList(aList1);
		 
		 /*Get sublist*/
		 ArrayList<String> aList4 = new ArrayList<String>();
		 aList4 = new ArrayList<String>(aList1.subList(2, 5));
		 System.out.print("\n\nSub List ");
		 obj.displayList(aList4);
		 
		 /*Add elements of Second ArrayList at the end of First ArrayList*/
		 aList1.addAll(aList2);
		 
		 /*Add elements of Second ArrayList at specific index of First ArrayList*/
		 aList1.addAll(1, aList2);
		 
		 /*Display First ArrayList*/
		 System.out.println("\n\nAfter Adding Second List");
		 obj.displayList(aList1);
		 
		 /*Get an element from first ArrayList */
		 System.out.println("\n\nElement at position 5:" + aList1.get(5));
		 
		 /*Check whether an object is present in the given list*/
		 System.out.println("Is element 11 present : " + aList1.contains("11"));
		  
		 /*Randomly Shuffle elements of First ArrayList*/
		 System.out.println("\n\nAfter Shuffling: ");
		 Collections.shuffle(aList1);
		 obj.displayList(aList1);
		 		 
		 /*Sort and display First ArrayList*/
		 System.out.println("\n\nAfter Sorting: ");
		 Collections.sort(aList1);
		 obj.displayList(aList1);
		 
		 /*find last occurrence of an element in First ArrayList*/
		 System.out.println("\n\nLast index of \"1\": " + aList1.lastIndexOf("1"));
		 
		 /*Reverse and display First ArrayList*/
		 System.out.println("\n\nAfter Reversing: ");
		 Collections.reverse(aList1);
		 obj.displayList(aList1);
		 
		 /*Find frequency of an object in list*/
		 System.out.println("\n\nFrequency of element 1: " + Collections.frequency(aList1, "1"));
		 
		 /*Binary Search an object in list and display it's index*/
		 int index = Collections.binarySearch(aList1,"4");
		 System.out.println("Element found at (Binary Search) : " + index);
		 
		 /*Create third ArrayList*/
		 ArrayList<String> aList3 = new ArrayList<String>();
		 obj.insertList3(aList3);
		 
		 /*Verify whether all elements of third ArrayList are present in first ArrayList*/
		 System.out.println("Contains third list: " + aList1.containsAll(aList3));
		 
		 /*Get starting index of third ArrayList present in first ArrayList*/
		 System.out.println("Index of third list: " + Collections.indexOfSubList(aList1, aList3));
	}
}