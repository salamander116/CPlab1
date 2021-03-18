import java.awt.geom.Point2D;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

public class Worker extends Thread {

    public ConcurrentHashMap<Point2D, Point2D> sharedPoints; //Shared memmory among ther other threads

    public int nshots;

    //Defines the range of points
    static int min = 0;
    static int max = 1;

    public Worker(int nShots, ConcurrentHashMap<Point2D, Point2D> p) {
        sharedPoints = p;
        this.nshots = nShots;

    }

    public void run() {


        for (int i = 0; i < nshots; i++) {

            Point2D p;

            //generates random value and in range
            double random = new Random().nextDouble();
            double x = min + (random * (max - min));

            //generates random value and in range
            random = new Random().nextDouble();
            double y = min + (random * (max - min));

            if (((x * x) + (y * y)) <= 1) {
                p = new Point2D.Double(x, y);
                if (!sharedPoints.containsKey(p)) {
                    sharedPoints.put(p, p);
                }

            }


        }
    }
}
