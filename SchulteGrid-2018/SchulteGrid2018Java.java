import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class SchulteGrid2018Java {
	private static final int nCount = 25;
	public static int nextInt(int n){
		return (int)(Math.random() * n);
	}
	public static void log(int n){
		System.out.println(n);
	}
	public static List<Integer> getData1(){
		List<Integer> list = new ArrayList<Integer>();
		List<Integer> source = new ArrayList<Integer>();
		for(int i = 0; i < nCount; i++){
			source.add(i + 1);
		}
		for(int i = 0; i < nCount; i++){
			int r = nextInt(nCount - i);
			list.add(source.get(r));
			source.remove(r);
		}
		return list;
	}
	
	private static int[][] source2 = new int[nCount][2]; // 0:n, 1:next
	private static int[] list2 = new int[nCount];
	public static int[] getData2(){
		//int[][] source2 = new int[nCount][2]; // 0:n, 1:next
		//int[] list2 = new int[nCount];
		int list_ptr = 0;
		for(int i = 0; i < nCount; i++){
			source2[i][0] = source2[i][1] = i + 1;
		}
		
		int current = 0;
		int prev = nCount - 1;
		source2[prev][1] = current;
		for(int i = 0; i < nCount; i++){
			int r = nextInt(nCount - i);
			for(int n = 0; n < r; n++){
				prev = current;
				current = source2[current][1];
			}
			
			list2[list_ptr++] = source2[current][0];
			source2[prev][1] = source2[current][1];
			source2[current][1] = -1;
			current = source2[prev][1];
		}
		return list2;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		Date date = null;
//		date = new Date();
//		for(int i = 0; i < 100000; i++){
//			getData1();
//		}
//		System.out.println("Method1:" + ((new Date()).getTime() - date.getTime()));//Method1:346

		List list = getData1();
		for(int i = 0; i < list.size(); i++){
			System.out.print(list.get(i) + ", ");
		}
		
		System.out.println();
//		date = new Date();
//		for(int i = 0; i < 100000; i++){
//			getData2();
//		}
//		System.out.println("Method2:" + ((new Date()).getTime() - date.getTime()));//Method2:258

		int[] list2 = getData2();
		for(int i = 0; i < list2.length; i++){
			System.out.print(list2[i] + ", ");
		}
	}

}
