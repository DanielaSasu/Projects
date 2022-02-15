package DesenareGraf2;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.geom.AffineTransform;

public class Arc{
	private Point start;
	private Point end;
	
	public Arc(Point start, Point end){
		this.start = start;
		this.end = end;
	}
	public Point getStart() {
		return start;
	}
	public void setStart(Point start) {
		this.start = start;
	}
	public Point getEnd() {
		return end;
	}
	public void setEnd(Point end) {
		this.end = end;
	}
	public static void drawArrow(Graphics g1, int x1, int y1, int x2, int y2) {
	    Graphics2D g = (Graphics2D) g1.create();

	    double dx = x2 - x1, dy = y2 - y1;
	    double angle = Math.atan2(dy, dx);
	    int len = (int) Math.sqrt(dx*dx + dy*dy);
	    AffineTransform at = AffineTransform.getTranslateInstance(x1, y1);
	    at.concatenate(AffineTransform.getRotateInstance(angle));
	    g.transform(at);
	    g.drawLine(0, 0, len, 0);
	    int ARR_SIZE=10;
	    g.fillPolygon(new int[] {len-15, len-ARR_SIZE-20, len-ARR_SIZE-20, len-15},
	                  new int[] {0, -ARR_SIZE, ARR_SIZE, 0}, 4);
	}
	
	public void drawArc(Graphics g, int option){
		if (start != null){
            g.setColor(Color.BLACK);
            if(option==0) {
            	g.drawLine(start.x, start.y, end.x, end.y);
            }
            else {
            	drawArrow(g,start.x, start.y, end.x, end.y);
            }
        }
	}
}
