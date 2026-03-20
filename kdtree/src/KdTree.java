import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import java.util.ArrayList;
import java.util.List;

public class KdTree {

    private static class Node {
        private Point2D p;      // Điểm tọa độ tại nút này
        private RectHV rect;    // Hình chữ nhật bao trùm không gian của nút này
        private Node lb;        // Cây con trái/dưới (left/bottom)
        private Node rt;        // Cây con phải/trên (right/top)

        public Node(Point2D p, RectHV rect) {
            this.p = p;
            this.rect = rect;
        }
    }

    private Node root;
    private int size;

    // Construct an empty set of points
    public KdTree() {
        root = null;
        size = 0;
    }

    // Is the set empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // Number of points in the set
    public int size() {
        return size;
    }

    // Add the point to the set (if it is not already in the set)
    public void insert(Point2D p) {
        if (p == null) throw new IllegalArgumentException("Argument to insert() is null");

        // Tránh chèn điểm trùng lặp
        if (!contains(p)) {
            // Nút gốc sẽ bao phủ toàn bộ vùng Unit Square [0, 1] x [0, 1]
            root = insert(root, p, true, 0.0, 0.0, 1.0, 1.0);
            size++;
        }
    }

    private Node insert(Node x, Point2D p, boolean useX, double xmin, double ymin, double xmax, double ymax) {
        if (x == null) {
            return new Node(p, new RectHV(xmin, ymin, xmax, ymax));
        }

        if (useX) { // So sánh theo trục X
            if (p.x() < x.p.x()) {
                // Đi sang trái, giới hạn xmax mới chính là x.p.x()
                x.lb = insert(x.lb, p, !useX, xmin, ymin, x.p.x(), ymax);
            } else {
                // Đi sang phải, giới hạn xmin mới chính là x.p.x()
                x.rt = insert(x.rt, p, !useX, x.p.x(), ymin, xmax, ymax);
            }
        } else { // So sánh theo trục Y
            if (p.y() < x.p.y()) {
                // Đi xuống dưới, giới hạn ymax mới chính là x.p.y()
                x.lb = insert(x.lb, p, !useX, xmin, ymin, xmax, x.p.y());
            } else {
                // Đi lên trên, giới hạn ymin mới chính là x.p.y()
                x.rt = insert(x.rt, p, !useX, xmin, x.p.y(), xmax, ymax);
            }
        }
        return x;
    }

    // Does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null) throw new IllegalArgumentException("Argument to contains() is null");
        return contains(root, p, true);
    }

    private boolean contains(Node x, Point2D p, boolean useX) {
        if (x == null) return false;
        if (x.p.equals(p)) return true;

        if (useX) {
            if (p.x() < x.p.x()) return contains(x.lb, p, !useX);
            else                 return contains(x.rt, p, !useX);
        } else {
            if (p.y() < x.p.y()) return contains(x.lb, p, !useX);
            else                 return contains(x.rt, p, !useX);
        }
    }

    // Draw all points to standard draw
    public void draw() {
        draw(root, true);
    }

    private void draw(Node x, boolean useX) {
        if (x == null) return;

        // Vẽ điểm (màu đen)
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.setPenRadius(0.01);
        x.p.draw();

        // Vẽ đường thẳng chia không gian
        StdDraw.setPenRadius(); // Reset độ dày
        if (useX) {
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.line(x.p.x(), x.rect.ymin(), x.p.x(), x.rect.ymax());
        } else {
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.line(x.rect.xmin(), x.p.y(), x.rect.xmax(), x.p.y());
        }

        draw(x.lb, !useX);
        draw(x.rt, !useX);
    }

    // All points that are inside the rectangle (or on the boundary)
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new IllegalArgumentException("Argument to range() is null");
        List<Point2D> results = new ArrayList<>();
        range(root, rect, results);
        return results;
    }

    private void range(Node x, RectHV rect, List<Point2D> results) {
        if (x == null) return;

        // PRUNING: Nếu hình chữ nhật truy vấn không giao cắt với không gian của Node này, bỏ qua toàn bộ nhánh
        if (!rect.intersects(x.rect)) return;

        // Nếu điểm nằm trong hình chữ nhật, thêm vào kết quả
        if (rect.contains(x.p)) {
            results.add(x.p);
        }

        range(x.lb, rect, results);
        range(x.rt, rect, results);
    }

    // A nearest neighbor in the set to point p; null if the set is empty
    public Point2D nearest(Point2D p) {
        if (p == null) throw new IllegalArgumentException("Argument to nearest() is null");
        if (isEmpty()) return null;

        // Khởi tạo điểm gần nhất ban đầu là gốc
        return nearest(root, p, root.p, true);
    }

    private Point2D nearest(Node x, Point2D queryPoint, Point2D closestPoint, boolean useX) {
        if (x == null) return closestPoint;

        // PRUNING: Nếu khoảng cách từ điểm truy vấn đến hình chữ nhật của Node hiện tại
        // lớn hơn khoảng cách ngắn nhất đã tìm được -> Bỏ qua toàn bộ nhánh này.
        if (x.rect.distanceSquaredTo(queryPoint) >= closestPoint.distanceSquaredTo(queryPoint)) {
            return closestPoint;
        }

        // Cập nhật điểm gần nhất nếu tìm thấy
        if (x.p.distanceSquaredTo(queryPoint) < closestPoint.distanceSquaredTo(queryPoint)) {
            closestPoint = x.p;
        }

        // QUAN TRỌNG: Quyết định nhánh nào để tìm kiếm trước
        // (Luôn đi về phía nhánh chứa điểm truy vấn trước để khả năng prune nhánh còn lại cao hơn)
        Node first = x.lb;
        Node second = x.rt;
        boolean goLeft = useX ? queryPoint.x() < x.p.x() : queryPoint.y() < x.p.y();

        if (!goLeft) {
            first = x.rt;
            second = x.lb;
        }

        closestPoint = nearest(first, queryPoint, closestPoint, !useX);
        closestPoint = nearest(second, queryPoint, closestPoint, !useX);

        return closestPoint;
    }

    // Unit testing of the methods (optional)
    public static void main(String[] args) {
        // Bạn có thể viết code test đơn giản ở đây
    }
}