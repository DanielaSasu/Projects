package DesenareGraf2;

import java.awt.Button;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class Graf
{	
	private static void initUI() {
		MyPanel MyPanel=new MyPanel();
        JFrame f = new JFrame(" Algoritmica grafurilor | Tema 3 | Sasu Daniela Claudia | 10LF393 ");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        Button butonComponenteConexe = new Button();
        butonComponenteConexe.setSize(150, 50);
        butonComponenteConexe.setLocation(150, 30);
        butonComponenteConexe.setLabel("Componente conexe");
        butonComponenteConexe.addActionListener( new ActionListener() {

            public void actionPerformed(ActionEvent ae) {
            	
                MyPanel.afisareComponenteConexe();
                
            }
        });
    	 f.add(butonComponenteConexe);
        
    	 Button butonComponenteTareConexe = new Button();
         butonComponenteTareConexe.setSize(150, 50);
         butonComponenteTareConexe.setLocation(310, 30);
         butonComponenteTareConexe.setLabel("Componente tare conexe");
         butonComponenteTareConexe.addActionListener( new ActionListener() {

             public void actionPerformed(ActionEvent ae) {
                 MyPanel.afisareComponenteTareConexe();
             }
         });
    	f.add(butonComponenteTareConexe);
    	 
    	Button butonSortareTopologica = new Button();
        butonSortareTopologica.setSize(150, 50);
        butonSortareTopologica.setLocation(470, 30);
        butonSortareTopologica.setLabel("Sortare topologica");
        butonSortareTopologica.addActionListener( new ActionListener() {

            public void actionPerformed(ActionEvent ae) {
                MyPanel.afisareSortareTopologica();
            }
        });
    	f.add(butonSortareTopologica);
    	
        f.add(MyPanel);
        f.setSize(700,700);
        f.setVisible(true);
    }
	
	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(new Runnable() 
		{
            public void run() 
            {
            	initUI(); 
            }
        });
	}	
}
