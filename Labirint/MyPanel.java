package Labirint2;

import java.awt.Button;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;


public class MyPanel {
	public static void MakeFrame() {
		Labirint maze = new Labirint();
        Button PrintPath = new Button();
        PrintPath.setSize(150, 50);
        PrintPath.setLabel("Afisare drumuri");
        PrintPath.addActionListener( new ActionListener() {

            public void actionPerformed(ActionEvent ae) {

                maze.pressButton();
            }
        });
        Button resetButton = new Button();
        resetButton.setSize(150, 50);
        resetButton.setLocation(200, 0);
        resetButton.setLabel("Resetare");
		JFrame frame = new JFrame("Algoritmica grafurilor | Tema 2 | Sasu Daniela Claudia | 10LF393");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    frame.add(resetButton);
	    frame.add(PrintPath);
	    frame.add(maze);
        frame.setSize(700, 700);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setLocation(dim.width/2-frame.getSize().width/2,
        		dim.height/2-frame.getSize().height/2);
        frame.setVisible(true);
        resetButton.addActionListener( new ActionListener() {

            public void actionPerformed(ActionEvent ae) {

                frame.setVisible(false);
                SwingUtilities.invokeLater( new Runnable() {

                    public void run() {

                        MakeFrame();
                    }
                });
            }
        });
    }

public static void main (String[] args) {

    SwingUtilities.invokeLater( new Runnable() {

        public void run() {

            MakeFrame();
        }
    });
  }
}
