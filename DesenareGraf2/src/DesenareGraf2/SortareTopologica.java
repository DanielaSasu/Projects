package DesenareGraf2;
import java.util.Vector;
import java.util.Stack;

public class SortareTopologica {

    public Vector<Integer> ProgramST (int numberOfNodes, int sourceNode, Vector<Vector<Integer>> lists) {

        int inf = Integer.MAX_VALUE;
        int n;
        int s;
        Vector<Integer> N = new Vector<Integer>();
        Vector<Boolean> U = new Vector<Boolean>();
        Stack<Integer> V = new Stack<Integer>();
        Vector<Integer> W = new Vector<Integer>();
        Vector<Integer> p = new Vector<Integer>();
        Vector<Integer> t1 = new Vector<Integer>();
        Vector<Integer> t2 = new Vector<Integer>();
        Vector<Vector<Integer>> A = new Vector<Vector<Integer>>();
        n = numberOfNodes;
        s = sourceNode;
        A = lists;
        Vector<Integer> listaTopologica = new Vector<Integer>();
        Vector<Integer> listaIndici = new Vector<Integer>();
        for (int index = 0; index < n; index++) {
            N.add(index + 1);
            U.add(false);
            p.add(0);
            t1.add(inf);
            t2.add(inf);
            listaIndici.add(0);
        }
        U.set(s - 1, true);
        V.push(s);
        W = new Vector<Integer>();
        int t = 1;
        t1.set(s - 1, 1);
        while (W.size() != N.size()) {

            while (V.size() != 0) {

                int x = V.peek();
                boolean ok1 = false;
                for (int indice = listaIndici.get(x - 1); indice < A.get(x - 1).size(); indice++) {

                    if (U.get(A.get(x - 1).get(indice) - 1) == false) {

                        int y = A.get(x - 1).get(indice);
                        U.set(y - 1, true);
                        V.push(y);
                        p.set(y - 1, x);
                        t = t + 1;
                        t1.set(y - 1, t);
                        listaIndici.set(x - 1, indice + 1);
                        ok1 = true;
                        break;
                    }
                }
                if (!ok1) {

                    V.pop();
                    W.add(x);
                    t = t + 1;
                    t2.set(x - 1, t);
                    listaTopologica.add(0, x);
                }
            }
            for (int index = 0; index < n; index++) {

                if (U.get(index) == false) {

                    s = index + 1;
                    U.set(s - 1, true);
                    V.push(s);
                    t = t + 1;
                    t1.set(s - 1, t);
                    break;
                }
            }
        }
        return listaTopologica;
    }
}