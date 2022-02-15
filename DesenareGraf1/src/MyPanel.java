import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
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
	//matrice adiacenta
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
		// borderul panel-ului
		setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));
		addMouseListener(new MouseAdapter() {
			//evenimentul care se produce la apasarea mousse-ului
			public void mousePressed(MouseEvent e) {
				pointStart = e.getPoint();
			}
			
			//evenimentul care se produce la eliberarea mousse-ului
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
							}
						}
					}
				pointStart = null;
				isDragging = false;
				isRightMouse=false;
			}
		});
		
		addMouseMotionListener(new MouseMotionAdapter() {
			//evenimentul care se produce la drag&drop pe mousse
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
	void adaugareArcMatrice(int nod1, int nod2) {
		if(rb1.isSelected()) {
			matriceAdiacenta[nod1-1][nod2-1]=1;
			matriceAdiacenta[nod2-1][nod1-1]=1;
		}
		if(rb2.isSelected()) {
			matriceAdiacenta[nod1-1][nod2-1]=1;
		}
		}
	//afisare matrice
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
	//metoda care se apeleaza la eliberarea mouse-ului
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
		repaint();
		}
	}
	
	//se executa atunci cand apelam repaint()
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);//apelez metoda paintComponent din clasa de baza
		g.drawString("Alegeti tipul grafului: ", 10, 20);
		//deseneaza arcele existente in lista
		/*for(int i=0;i<listaArce.size();i++)
		{
			listaArce.elementAt(i).drawArc(g);
		}*/
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
		//deseneaza arcul curent; cel care e in curs de desenare
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
		//deseneaza lista de noduri
		for(int i=0; i<listaNoduri.size(); i++)
		{
			listaNoduri.elementAt(i).drawNode(g, node_diam);
		}
		/*for (Node nod : listaNoduri)
		{
			nod.drawNode(g, node_diam, node_Diam);
		}*/
	}
}