import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;
import java.util.ArrayList; // Khai báo thư viện
import java.util.List;
// Nếu dùng TreeSet cho PointSET
import java.util.Iterator;
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
        ArrayList<Point2D> result = new ArrayList<>();
        for (Point2D p : points) {
            if (rectHV.contains(p)) {
                result.add(p);
            }
        }
        return result;
    }
    public  Point2D nearest(Point2D p) {
        if (points.isEmpty()) {
            return null;
        }
        Point2D res = points.first();
        double min_distance = res.distanceSquaredTo(p);
        for (Point2D p2 : points) {
            double distanceSquared = p2.distanceSquaredTo(p);
            if (distanceSquared < min_distance) {
                min_distance = distanceSquared;
                res = p2;
            }
        }
        return res;
    }
    public static void main(String[] args) {
        PointSET s = new PointSET();
        System.out.println("Hello");
    }
}
