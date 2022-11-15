public class Fib {
  static int fibonachi(int n) {
    if (n == 0){
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    else {
        return fibonachi(n - 1) + fibonachi(n - 2);
    }
  }
  public static void main(String[] args) {
		int reply = fibonachi(10);
		System.out.println(reply);
	}
}

