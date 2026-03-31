import edu.princeton.cs.algs4.Picture;
import java.awt.Color; // Cần thiết để làm việc với màu sắc

public class TestPicture {
    public static void main(String[] args) {
        // 1. Tạo đối tượng Picture từ một URL hoặc file local
        // Nếu dùng file máy tính, hãy thay bằng đường dẫn: "C:/images/pic.jpg"
        Picture pic = new Picture("https://introcs.cs.princeton.edu/java/stdlib/mandrill.jpg");

        // 2. Hiển thị ảnh lên cửa sổ
        pic.show();

        // 3. In thông tin kích thước
        System.out.println("Chiều rộng: " + pic.width());
        System.out.println("Chiều cao: " + pic.height());
        System.out.println(pic.getARGB(0,0));
    }
}