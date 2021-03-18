package lab1.linear;

import java.awt.geom.Point2D;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class MonteSeq {

    static int min = 0;
    static int max = 1;
    public static List<Point2D> points = new LinkedList<Point2D>();

    private static void shotDarts() {

        Point2D p = null;

        do {
            //generates random value and in range
            double random = new Random().nextDouble();
            double x = min + (random * (max - min));

            //generates random value and in range
            random = new Random().nextDouble();
            double y = min + (random * (max - min));

            if (((x * x) + (y * y)) <= 1) {
                p = new Point2D.Double(x, y);
                if (!points.contains(p)) {
                    points.add(p);
                } else {
                    p = null;
                }
            } else {
                return;
            }
        } while (p == null);

    }

    public static void main(String[] args) {

        double nShots = Double.parseDouble(args[0]);

        for (int i = 0; i < nShots; i++) {
            shotDarts();
        }

        double p = (double) points.size() / nShots;
        double pi = p * 4;
        System.out.print("Total Number of points: " + nShots + "\n" +
                "Points within the circle: " + points.size() + "\n" +
                "Pi estimation: " + pi + "\n");
    }
}
