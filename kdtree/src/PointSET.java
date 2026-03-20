import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;
// Nếu dùng TreeSet cho PointSET
import java.util.TreeSet;
public class PointSET {
    private TreeSet<Point2D> points;
    public PointSET() {
        points = new TreeSet<>();
    }
    public boolean isEmpty() {
        return points.isEmpty();
    }
    public int size() {
        return points.size();
    }
    public void insert(Point2D p) {
        points.add(p);
    }
    public boolean contains(Point2D p) {
        return points.contains(p);
    }
    public void draw() {
        for (Point2D p : points) {
            p.draw();
        }
    }
    public Iterable<Point2D> range(RectHV rectHV) {
        return null;
    }
    public  Point2D nearest(Point2D p) {
        return null;
    }
    public static void main(String[] args) {
        PointSET s = new PointSET();
        System.out.println("Hello");
    }
}
