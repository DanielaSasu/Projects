package DesenareGraf2;
import java.awt.Button;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.Random;
import java.util.Vector;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.SwingUtilities;

import java.io.FileWriter;
import java.io.IOException;
public class MyPanel extends JPanel {
	private int nodeNr = 1;
	private int node_diam = 30;
	private Vector<Node> listaNoduri;
	private Vector<Arc> listaArce;
	private Vector<Vector<Integer>>listaAdiacenta=new Vector<Vector<Integer>>();
	private int matriceAdiacenta[][]=new int[nodeNr][nodeNr];
	private int matriceTemp[][];
	Point pointStart = null;
	Point pointEnd = null;
	boolean isDragging = false;
	boolean isRightMouse=false;
	JRadioButton rb1, rb2;
	public MyPanel(){
		listaNoduri = new Vector<Node>();
		listaArce = new Vector<Arc>();
		rb1=new JRadioButton("Graf neorientat");    
		rb1.setBounds(5,30,110,30);   
		rb2=new JRadioButton("Graf orientat");    
		rb2.setBounds(5,60,100,30);  
		ButtonGroup bg=new ButtonGroup();    
		bg.add(rb1);bg.add(rb2);       
		add(rb1);add(rb2);    
		setSize(300,300);    
		setLayout(null);    
		setVisible(true);
		setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));
		addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				pointStart = e.getPoint();
			}
			public void mouseReleased(MouseEvent e) {
				if (!isDragging) {
				addNode(e.getX(),e.getY());
				}
				else 
					if(!isRightMouse) { 
						int foundStart=0;
						int foundEnd=0;
						int start=-1;
						int end=-1;
						for(int index=0;index<listaNoduri.size();index++) {
							if(pointStart.x>listaNoduri.get(index).getCoordX() &&
									pointStart.x<listaNoduri.get(index).getCoordX()+25 &&
									pointStart.y>listaNoduri.get(index).getCoordY() &&
									pointStart.y<listaNoduri.get(index).getCoordY()+25) {
								foundStart=1;
								start=listaNoduri.get(index).getNumber();
							}
							if(pointEnd.x>listaNoduri.get(index).getCoordX() &&
									pointEnd.x<listaNoduri.get(index).getCoordX()+25 &&
									pointEnd.y>listaNoduri.get(index).getCoordY() &&
									pointEnd.y<listaNoduri.get(index).getCoordY()+25) {
								foundEnd=1;
								end=listaNoduri.get(index).getNumber();
							}
						}
						if(foundStart==1 && foundEnd==1) {
							if(matriceAdiacenta[start-1][end-1]==0) {
								Arc arc = new Arc(pointStart, pointEnd);
								listaArce.add(arc);	
								adaugareArcMatrice(start,end);
								afisareMatrice();
								transformaInListe();
							}
						}
					}
				pointStart = null;
				isDragging = false;
				isRightMouse=false;
			}
		});
		
		addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e) {
				if(SwingUtilities.isRightMouseButton(e)) {
					pointEnd = e.getPoint();
					int ok=0;
					int pozitie=0;
					for(int index=0;index<listaNoduri.size();index++) {
						if(pointEnd.x>listaNoduri.get(index).getCoordX() &&
								pointEnd.x<listaNoduri.get(index).getCoordX()+30 &&
								pointEnd.y>listaNoduri.get(index).getCoordY() &&
								pointEnd.y<listaNoduri.get(index).getCoordY()+30) {
							ok=1;
							pozitie=index;
						}
					}
						int found=0;
							for(int index2=0;index2<listaNoduri.size();index2++) {
								if(pozitie!=index2
										&&pointEnd.x>listaNoduri.get(index2).getCoordX()-50 
										&& pointEnd.x<listaNoduri.get(index2).getCoordX()+50
										&& pointEnd.y>listaNoduri.get(index2).getCoordY()-50 
										&& pointEnd.y<listaNoduri.get(index2).getCoordY()+50) {
									found=1;
								}
							}
							if(found==0 &&ok==1) {
								listaNoduri.get(pozitie).setCoordX(pointEnd.x-(node_diam/2));
								listaNoduri.get(pozitie).setCoordY(pointEnd.y-(node_diam/2));
							}
					for(int index=0;index<listaArce.size();index++) {
						if(pointEnd.x>listaArce.get(index).getStart().x-30&&
								pointEnd.x<listaArce.get(index).getStart().x+30&&
								pointEnd.y>listaArce.get(index).getStart().y-30&&
								pointEnd.y<listaArce.get(index).getStart().y+30) {
							listaArce.get(index).setStart(pointEnd);
						}
						if(pointEnd.x>listaArce.get(index).getEnd().x-30&&
								pointEnd.x<listaArce.get(index).getEnd().x+30&&
								pointEnd.y>listaArce.get(index).getEnd().y-30&&
								pointEnd.y<listaArce.get(index).getEnd().y+30) {
							listaArce.get(index).setEnd(pointEnd);
						}
					}
					isRightMouse=true;
					isDragging = true;
					repaint();
				}
				else {
					pointEnd = e.getPoint();
					isDragging = true;
					repaint();
				}
					}
		});
	}
	void afisareSortareTopologica() {
		 Vector<Integer> listaTopologica = new Vector<Integer>();
     	System.out.println("Sortare topologica:");
         SortareTopologica st = new SortareTopologica();
         int numarNoduri = listaNoduri.size();
         int nodSursa = 1;
         listaTopologica = st.ProgramST(numarNoduri, nodSursa, listaAdiacenta);
         System.out.println(listaTopologica);
	}
	void afisareComponenteConexe() {
		ComponenteConexe ComponenteConexe=new ComponenteConexe();
		int numarNoduri = listaNoduri.size();
        int nodSursa = 1;
        int matrice[][]=new int[nodeNr][nodeNr];
        Random rand = new Random();
        int redValue = rand.nextInt(255);
        int greenValue = rand.nextInt(255);
        int blueValue = rand.nextInt(255);
        Color clr = new Color(redValue, greenValue, blueValue);
        matrice=ComponenteConexe.ProgramCC(numarNoduri, nodSursa, listaAdiacenta);
        for(int index1=0;index1<matrice.length;index1++) {
        	for(int index2=0;index2<matrice[index1].length;index2++) {
        		if(matrice[index1][index2]!=0) {
        			listaNoduri.elementAt(matrice[index1][index2]-1).setColor(clr);
        		}
        	}
            redValue = rand.nextInt(255);
            greenValue = rand.nextInt(255);
            blueValue = rand.nextInt(255);
            clr = new Color(redValue, greenValue, blueValue);
        }
        repaint();
	}
	void afisareComponenteTareConexe() {
		ComponenteTareConexe ComponenteTareConexe=new ComponenteTareConexe();
		int numarNoduri = listaNoduri.size();
        int nodSursa = 1;
        ComponenteTareConexe.ProgramCTC(numarNoduri, nodSursa, listaAdiacenta);
	}
	void adaugareArcMatrice(int nod1, int nod2) {
		if(rb1.isSelected()) {
			matriceAdiacenta[nod1-1][nod2-1]=1;
			matriceAdiacenta[nod2-1][nod1-1]=1;
		}
		if(rb2.isSelected()) {
			matriceAdiacenta[nod1-1][nod2-1]=1;
		}
		}
	void afisareMatrice() {
		try {
			FileWriter fprint=new FileWriter("matriceAdiacenta.txt");
			fprint.write(nodeNr-1+"\n");
			for(int index1=0;index1<matriceAdiacenta.length-1;index1++) {
				for(int index2=0;index2<matriceAdiacenta.length-1;index2++) {
					fprint.write(matriceAdiacenta[index1][index2]+ " ");
				}
				fprint.write("\n");
			}
			fprint.close();
		}
		catch(IOException e) {
			System.out.println("EROARE");
		}
	}
	private void addNode(int x, int y) {
		int found=0;
		for(int index=0;index<listaNoduri.size();index++){
			if(x>listaNoduri.get(index).getCoordX()-50 && x<listaNoduri.get(index).getCoordX()+50 && 
					y>listaNoduri.get(index).getCoordY()-50 && y<listaNoduri.get(index).getCoordY()+50) {
				found=1;
			}
		}
		if(found==0) {
		Node node = new Node(x, y, nodeNr);
		listaNoduri.add(node);
		nodeNr++;
		matriceTemp=new int[nodeNr][nodeNr];
		for(int index1=0;index1<matriceAdiacenta.length-1;index1++) {
			for(int index2=0;index2<matriceAdiacenta.length-1;index2++) {
				matriceTemp[index1][index2]=matriceAdiacenta[index1][index2];
			}
		}
		matriceAdiacenta=new int[nodeNr][nodeNr];
		matriceAdiacenta=matriceTemp;
		afisareMatrice();
		transformaInListe();
		repaint();
		}
	}
	
	public void transformaInListe() {
		listaAdiacenta = new Vector<Vector<Integer>>(nodeNr);
        for (int linie = 0; linie < nodeNr; linie++) {
            Vector<Integer> listaNod = new Vector<Integer>();
            for (int coloana = 0; coloana < matriceAdiacenta.length-1; coloana++) {
                if (matriceAdiacenta[linie][coloana] == 1) {
                    listaNod.add(coloana + 1);
                }
            }
            listaAdiacenta.add(listaNod);
        }
        afisareListaAdiacenta();
    }
	public void afisareListaAdiacenta() {
		 try {
		    	FileWriter fout =new FileWriter("ListeAdiacenta");
		    	fout.write(nodeNr-1+ "\n");

	        for (int nod = 0; nod < listaAdiacenta.size()-1; nod++) {
	            fout.write((nod + 1) + ": " + listaAdiacenta.get(nod));
	            fout.write("\n");
	        }
	        fout.close();
		 }
	 catch (IOException e)
	    	{
	    		System.out.println("Eroare");
	    	}
	    }
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawString("Alegeti tipul grafului: ", 10, 20);
		if(rb1.isSelected()) {
			for (Arc a : listaArce)
			{
				a.drawArc(g,0);
			}
		}
		else {
			if(rb2.isSelected()) {
				for (Arc a : listaArce)
				{
					a.drawArc(g,1);
				}
			}
		}
		if (pointStart != null)
		{
			int foundStart=0;
			int foundEnd=0;
			int start=-1;
			int end=-1;
			for(int index=0;index<listaNoduri.size();index++) {
				if(pointStart.x>listaNoduri.get(index).getCoordX() &&
						pointStart.x<listaNoduri.get(index).getCoordX()+25 &&
						pointStart.y>listaNoduri.get(index).getCoordY() &&
						pointStart.y<listaNoduri.get(index).getCoordY()+25) {
					foundStart=1;
					start=listaNoduri.get(index).getNumber();
				}
				if(pointEnd.x>listaNoduri.get(index).getCoordX() &&
						pointEnd.x<listaNoduri.get(index).getCoordX()+25 &&
						pointEnd.y>listaNoduri.get(index).getCoordY() &&
						pointEnd.y<listaNoduri.get(index).getCoordY()+25) {
					foundEnd=1;
					end=listaNoduri.get(index).getNumber();
				}
			}
			if(foundStart==1 && foundEnd==1) {
				g.setColor(Color.PINK);
				if(matriceAdiacenta[start-1][end-1]==0) {
					Arc a=new Arc(pointStart, pointEnd);
					if(rb1.isSelected()) {
						a.drawArc(g,0);
					}
					else {
						if(rb2.isSelected()) {
							a.drawArc(g,1);
						}
					}
				}
				}
		}
		for(int i=0; i<listaNoduri.size(); i++)
		{
			listaNoduri.elementAt(i).drawNode(g, node_diam);
		}
	}
}