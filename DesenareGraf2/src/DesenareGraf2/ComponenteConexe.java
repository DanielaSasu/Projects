package DesenareGraf2;
import java.util.Stack;
import java.util.Vector;

public class ComponenteConexe {

    static int[][]ProgramCC (int numarNoduri, int nodSursa, Vector<Vector<Integer>> listeAdiacenta) {

        int inf = Integer.MAX_VALUE;
        int n;
        int s;
        Vector<Integer> N = new Vector<Integer>();
        Vector<Boolean> U = new Vector<Boolean>();
        Stack<Integer> V = new Stack<Integer>();
        Vector<Integer> W = new Vector<Integer>();
        Vector<Vector<Integer>> A = new Vector<Vector<Integer>>();
        int matrice[][]=new int[numarNoduri][numarNoduri];
        n = numarNoduri;
        s = nodSursa;
        A = listeAdiacenta;
        Vector<Integer> listaIndici = new Vector<Integer>();
        for (int indice = 0; indice < n; indice++) {
            N.add(indice + 1);
            U.add(false);
            listaIndici.add(0);
        }
        U.set(s - 1, true);
        V.push(s);
        W = new Vector<Integer>();
        int p = 1;
        Vector<Integer> Nsecund= new Vector<Integer>();
        Nsecund.add(s);
        while (W.size() != N.size()) {
            while (V.size() != 0) {
                int x = V.peek();
                boolean ok1 = false;
                for (int indice = listaIndici.get(x - 1); indice < A.get(x - 1).size(); indice++) {
                    if (U.get(A.get(x - 1).get(indice) - 1) == false) {
                        int y = A.get(x - 1).get(indice);
                        U.set(y - 1, true);
                        V.push(y);
                        Nsecund.add(y);
                        listaIndici.set(x - 1, indice + 1);
                        ok1 = true;
                        break;
                    }
                }
                if (ok1 == false) {
                    V.pop();
                    W.add(x);
                }
            }
            System.out.print("Componenta conexa nr. " + p + " este formata din nodurile: ");
            System.out.print(Nsecund);
            for(int index=0;index<Nsecund.size();index++)
            {
            	matrice[p-1][index]=Nsecund.elementAt(index);
            }
            Nsecund.clear();
            System.out.println();
            for (int indice = 0; indice < n; indice++) {
                if (U.get(indice) == false) {
                    s = indice + 1;
                    U.set(s - 1, true);
                    V.push(s);
                    p++;
                    Nsecund.add(s);
                    break;
                }
            }
        }
        return matrice;
    }
}