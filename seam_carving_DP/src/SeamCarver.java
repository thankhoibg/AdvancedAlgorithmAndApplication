import edu.princeton.cs.algs4.Picture;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Stack;

public class SeamCarver {
    private Picture picture;
    private ArrayList<ArrayList<Double>> dp;
    private final double oo = 1000000.0;
    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new IllegalArgumentException("Picture can't be null");
        }
        this.picture = picture;
        dp = new ArrayList<>();
        for (int i = 0; i < picture.height(); ++ i) {
            ArrayList<Double> row = new ArrayList<>();
            for (int j = 0; j < picture.width(); ++ j) {
                row.add(0.0);
            }
            dp.add(row);
        }
    }
    public Picture picture() {
        return picture;
    }
    public int width() {
        return picture.width();
    }
    public int height() {
        return picture.height();
    }
    private boolean isValidCoordinate(int x, int y) {
        return x >= 0 && y >= 0 && x < picture.width() && y < picture.height();
    }
    private boolean isBorder(int x, int y) {
        return x == 0 || y == 0 || x == picture.width() - 1 || y == picture.height() - 1;
    }
    public double energy(int x, int y){
        if (!isValidCoordinate(x, y)) {
            throw new IllegalArgumentException("Coordinates out of bounds");
        }
        if (isBorder(x, y)) return 1000.0;
        Color c1 = picture.get(x-1, y);
        Color c2 = picture.get(x+1, y);
        double delta_x = (c1.getRed() - c2.getRed()) * (c1.getRed() - c2.getRed())
                        +(c1.getGreen() - c2.getGreen()) * (c1.getGreen() - c2.getGreen())
                        +(c1.getBlue() - c2.getBlue()) * (c1.getBlue() - c2.getBlue());
        c1 = picture.get(x, y-1);
        c2 = picture.get(x, y+1);
        double delta_y =  (c1.getRed() - c2.getRed()) * (c1.getRed() - c2.getRed())
                        +(c1.getGreen() - c2.getGreen()) * (c1.getGreen() - c2.getGreen())
                        +(c1.getBlue() - c2.getBlue()) * (c1.getBlue() - c2.getBlue());
        return Math.sqrt(delta_x + delta_y);
    }
    private void prepare() {
        for (int i = 0; i < picture.height(); ++ i) {
            for (int j = 0; j < picture.width(); ++ j) {
                dp.get(i).set(j, oo);
            }
        }
    }
    public int[] findHorizontalSeam() {
        int[] a = new int[width()];
        prepare();
        for (int i = 0; i < height(); ++ i) {
            dp.get(i).set(0, 1000.0);
        }
        for (int col = 1; col < width(); ++ col) {
            for (int row = 0; row < height(); ++ row) {
                double energy = energy(col, row);
                double tmp = dp.get(row).get(col-1);
                double tmp1 = oo, tmp2 = oo;
                if (row > 0) {
                    tmp1 = dp.get(row-1).get(col-1);
                }
                if (row < height()-1) {
                    tmp2 = dp.get(row+1).get(col-1);
                }
                dp.get(row).set(col, Math.min(Math.min(tmp, tmp1), tmp2) + energy);
            }
        }
        int x = -1;
        double mn = -1;
        for(int i = 0; i < height(); ++ i) {
            if (x == -1 || mn > dp.get(i).get(width()-1)) {
                x = i;
                mn = dp.get(i).get(width()-1);
            }
        }
        Stack<Integer> stack = new Stack<>();
        stack.push(x);
        int cnt = width() - 1;
        while (cnt > 0) {
            double energy = energy(cnt, x);
            if (dp.get(x).get(cnt) == dp.get(x).get(cnt - 1) + energy) {
                stack.push(x);
            } else if (x > 0 && dp.get(x).get(cnt) == dp.get(x-1).get(cnt-1) + energy) {
                x --;
                stack.push(x);
            } else if (x < height()-1 && dp.get(x).get(cnt) == dp.get(x+1).get(cnt-1) + energy) {
                x ++;
                stack.push(x);
            }
            cnt --;
        }
        cnt = -1;
        while (!stack.isEmpty()) {
            cnt ++;
            x = stack.pop();
            a[cnt] = x;
        }
        return a;
    }
    public int[] findVerticalSeam() {
        prepare();
        for (int i = 0; i < width(); ++ i) {
            dp.get(0).set(i, 1000.0);
        }
        for(int i = 1; i < height(); ++ i) {
            for(int j = 0; j < width(); ++ j) {
                double energy = energy(j, i);
                double tmp = dp.get(i-1).get(j);
                double tmp1 = oo, tmp2 = oo;
                if (j > 0) tmp1 = dp.get(i-1).get(j-1);
                if (j < width()-1) tmp2 = (dp.get(i-1).get(j+1));
                dp.get(i).set(j, Math.min(Math.min(tmp1, tmp2), tmp) + energy);
            }
        }
        double mn = -1;
        int x = -1;
        for (int i = 0; i < width(); ++ i) {
            if (x == -1 || mn > dp.get(height()-1).get(i)) {
                x = i;
                mn = dp.get(height()-1).get(i);
            }
        }
        Stack<Integer> stack = new Stack<>();
        stack.push(x);
        int cnt = height() - 1;
        while (cnt > 0) {
            double energy = energy(x, cnt);
            if (dp.get(cnt).get(x) == dp.get(cnt-1).get(x) + energy) {
                stack.push(x);
            } else if (x > 0 && dp.get(cnt).get(x) == dp.get(cnt-1).get(x-1) + energy) {
                stack.push(x-1);
                x --;
            } else {
                stack.push(x+1);
                x ++;
            }
            cnt --;
        }
        int[] a = new int[height()];
        cnt = -1;
        while (!stack.isEmpty()) {
            cnt ++;
            a[cnt] = stack.pop();
        }
        return a;
    }
    private boolean checkSeam(int[] seam, int mx) {
        for(int i = 0; i < seam.length; ++ i) {
            if (seam[i] >= mx || seam[i] < 0) {
                return false;
            }
            if (i > 0 && Math.abs(seam[i] - seam[i-1]) > 1) {
                return false;
            }
        }
        return true;
    }
    public void removeHorizontalSeam(int[] seam) {
        if (seam == null || seam.length != width()) {
            throw new IllegalArgumentException("Invalid seam array");
        }
        if (height() <= 1) {
            throw new IllegalArgumentException("Can't remove seam");
        }
        if (!checkSeam(seam, height())) {
            throw new IllegalArgumentException("Invalid seam array");
        }
        Picture newp = new Picture(width(), height()-1);
        for(int col = 0; col < width(); ++ col) {
            for (int row = 0; row < seam[col]; ++ row) {
                newp.set(col, row, picture.get(col, row));
            }
            for (int row = seam[col]+1; row < height(); ++ row) {
                newp.set(col, row-1, picture.get(col, row));
            }
        }
        picture = newp;
    }
    public void removeVerticalSeam(int[] seam) {
        if (seam == null || seam.length != height()) {
            throw new IllegalArgumentException("Invalid seam array");
        }
        if (width() <= 1) {
            throw new IllegalArgumentException("Can't remove seam");
        }
        if (!checkSeam(seam, width())) {
            throw new IllegalArgumentException("Invalid seam array");
        }
        Picture newp = new Picture(width()-1, height());
        for (int row = 0; row < height(); ++ row) {
            for (int col = 0; col < seam[row]; ++ col) {
                newp.set(col, row, picture.get(col, row));
            }
            for (int col = seam[row] + 1; col < width(); ++ col) {
                newp.set(col-1, row, picture.get(col, row));
            }
        }
        picture = newp;
    }
}
