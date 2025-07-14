interface CallBack {
    public void s(int t);
}

class Client implements CallBack {
    public void s(int t){
        System.out.println("inside Client" + t);
    }
}

public class interface1 {
    public static void main(String[] args) {
        CallBack c = new Callback();
        c.s(42);
    }
}
