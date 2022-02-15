package Labirint2;

import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;
import java.io.File;
import java.util.Scanner;
import java.util.Vector;

public class Labirint extends JPanel{
	enum Colors{
		Black,
		White,
		Blue,
		Red,
		Green,
		NoColor
	}
	
	private Vector<Vector<Integer>>MazeMatrix=new Vector<Vector<Integer>>();
	private Vector<Vector<Integer>> NodesMatrix = new Vector<Vector<Integer>>();
    private Vector<Vector<Integer>> AdjacencyList = new Vector<Vector<Integer>>();
    private Vector<Integer> mazeExits = new Vector<Integer>();
    private Vector<Vector<Colors>> nodesColor = new Vector<Vector<Colors>>();
    private int nrNode = 0;
    private int nodeStart;
    private boolean press = false;
    private Vector<Integer> p = new Vector<Integer>();
    
    public Labirint() {

        ReadMatrix();
        ConvertMatrix();
        BuildGraph();
        repaint();
    }

    public void pressButton() {
        press = true;
        PBF();
    }

    public void ReadMatrix() {
    	File file = new File("src/Labirint2/Labirint.txt");
        try {
            Scanner fin = new Scanner(file);
            int nrLines = fin.nextInt();
            int nrColumns = fin.nextInt();
            for (int line = 0; line < nrLines; line++) {
                Vector<Integer> vectorLine = new Vector<Integer>();
                for (int node = 0; node < nrColumns; node++) {
                    int nrNode = fin.nextInt();
                    vectorLine.add(nrNode);
                }
                MazeMatrix.add(vectorLine);
            }
            fin.close();
        } catch (Exception exception) {
            System.out.println("A aparut o eroare!");
        }
    }
    
    public void ConvertMatrix() {

        for (int line = 0; line < MazeMatrix.size(); line++) {
            Vector<Integer> vectorLine = new Vector<Integer>();
            Vector<Colors> colorsVector = new Vector<Colors>();
            for (int column = 0; column < MazeMatrix.get(line).size(); column++) {
                if (MazeMatrix.get(line).get(column) != 0) {
                    nrNode++;
                    vectorLine.add(nrNode);
                    if (MazeMatrix.get(line).get(column) == 2) {
                        nodeStart = nrNode;
                    }
                    if (MazeMatrix.get(line).get(column) == 3) {
                        mazeExits.add(nrNode);
                    }
                } else {
                    vectorLine.add(0);
                }
                colorsVector.add(Colors.NoColor);
            }
            nodesColor.add(colorsVector);
            NodesMatrix.add(vectorLine);
        }
    }
    
    public void BuildGraph() {

        for (int node = 0; node < nrNode; node++) {
            Vector<Integer> vectorTemp = new Vector<Integer>();
            AdjacencyList.add(vectorTemp);
        }
        for (int line = 0; line < NodesMatrix.size(); line++) {
            for (int column = 0; column < NodesMatrix.get(line).size(); column++) {
                if (NodesMatrix.get(line).get(column) != 0) {
                    if (line > 0 && NodesMatrix.get(line - 1).get(column) != 0) {
                    	AdjacencyList.get(NodesMatrix.get(line - 1).get(column) -
                    			1).add(NodesMatrix.get(line).get(column));
                    }
                    if (line < NodesMatrix.size() - 1 && NodesMatrix.get(line 
                    		+ 1).get(column) != 0) {
                    	AdjacencyList.get(NodesMatrix.get(line + 1).get(column)
                    			- 1).add(NodesMatrix.get(line).get(column));
                    }
                    if (column > 0 && NodesMatrix.get(line).get(column - 1) != 0) {
                    	AdjacencyList.get(NodesMatrix.get(line).get(column - 1) 
                    			- 1).add(NodesMatrix.get(line).get(column));
                    }
                    if (column < NodesMatrix.get(line).size() -
                    		1 && NodesMatrix.get(line).get(column + 1) != 0) {
                    	AdjacencyList.get(NodesMatrix.get(line).get(column 
                    			+ 1) - 1).add(NodesMatrix.get(line).get(column));
                    }
                }
            }
        }
    }
    
    private void PBF() {

        int infinit = Integer.MAX_VALUE;
        Vector<Boolean> U = new Vector<Boolean>();
        Vector<Integer> V = new Vector<Integer>();
        Vector<Integer> W = new Vector<Integer>();
        Vector<Integer> l = new Vector<Integer>();
        for (int indice = 0; indice < AdjacencyList.size(); indice++) {
            p.add(0);
            l.add(infinit);
            U.add(false);
        }
        U.set(nodeStart - 1, true);
        V.add(nodeStart);
        W = new Vector<Integer>();
        l.set(nodeStart - 1, 0);
        while (V.size() != 0) {
            int x = V.firstElement();
            for (int y : AdjacencyList.get(x - 1)) {
                if (U.get(y - 1) == false) {
                    U.set(y - 1, true);
                    V.add(y);
                    p.set(y - 1, x);
                    l.set(y - 1, l.get(x - 1) + 1);
                    if (mazeExits.contains(y)) {
                        isPath(y);
                    }
                }
            }
            V.remove(V.firstElement());
            W.add(x);
        }
        repaint();
    }
    
    private void isPath(int exit) {
        while (exit != nodeStart) {
            for (int line = 0; line < NodesMatrix.size(); line++) {
                for (int column = 0; column < NodesMatrix.get(line).size(); column++) {
                    if (NodesMatrix.get(line).get(column) == exit) {
                    	nodesColor.get(line).set(column,Colors.Green);
                        break;
                    }
                }
            }
            exit = p.get(exit - 1);
        }
    }
    
    protected void paintComponent(Graphics graphic) {
        super.paintComponent(graphic);
        if (press == false) {
            for (int line = 0; line < MazeMatrix.size(); line++) {
                for (int column = 0; column < MazeMatrix.get(line).size(); column++) {
                    if (MazeMatrix.get(line).get(column) == 0) {
                        nodesColor.get(line).set(column, Colors.Black);
                        graphic.setColor(Color.BLACK);
                        graphic.fillRect(50 * column + 100, 50 * line + 100, 50, 50);
                        graphic.setColor(Color.BLACK);
                        graphic.drawRect(50 * column + 100, 50 * line + 100, 50, 50);
                    } else if (MazeMatrix.get(line).get(column) == 2) {
                    	nodesColor.get(line).set(column, Colors.Blue);
                        graphic.setColor(Color.BLUE);
                        graphic.fillRect(50 * column + 100, 50 * line + 100, 50, 50);
                        graphic.setColor(Color.BLACK);
                        graphic.drawRect(50 * column + 100, 50 * line + 100, 50, 50);
                    } else if (MazeMatrix.get(line).get(column) ==1) {
                    	nodesColor.get(line).set(column, Colors.White);
                        graphic.setColor(Color.WHITE);
                        graphic.fillRect(50 * column + 100, 50 * line + 100, 50, 50);
                        graphic.setColor(Color.BLACK);
                        graphic.drawRect(50 * column + 100, 50 * line + 100, 50, 50);
                    }else if (MazeMatrix.get(line).get(column) ==3) {
                    	nodesColor.get(line).set(column, Colors.Red);
                        graphic.setColor(Color.RED);
                        graphic.fillRect(50 * column + 100, 50 * line + 100, 50, 50);
                        graphic.setColor(Color.BLACK);
                        graphic.drawRect(50 * column + 100, 50 * line + 100, 50, 50);
                    }
                }
            }
        } else {
            for (int line = 0; line < MazeMatrix.size(); line++) {
                for (int column = 0; column < MazeMatrix.get(line).size(); column++) {
                    switch (nodesColor.get(line).get(column)) {
                        case White:
                            graphic.setColor(Color.WHITE);
                            break;
                        case Black:
                        	graphic.setColor(Color.BLACK);
                            break;
                        case Blue:
                        	graphic.setColor(Color.BLUE);
                            break;
                        case Red:
                        	graphic.setColor(Color.RED);
                        	break;
                        case Green:
                        	graphic.setColor(Color.GREEN);
                            break;
                        default:
                            break;
                    }
                    graphic.fillRect(50 * column + 100, 50 * line + 100, 50, 50);
                    graphic.setColor(Color.BLACK);
                    graphic.drawRect(50 * column + 100, 50 * line + 100,50, 50);
                }
            }
        }
    }
}