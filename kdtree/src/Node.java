import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;

public class Node {
    private Point2D p;      // Điểm tọa độ tại nút này
    private RectHV rect;    // Hình chữ nhật bao trùm không gian của nút này
    private Node lb;        // Cây con trái/dưới (left/bottom)
    private Node rt;        // Cây con phải/trên (right/top)

    public Node(Point2D p, RectHV rect) {
        this.p = p;
        this.rect = rect;
    }
}
