import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.*;

public class MonteSeq {

//    static int min = 0;
//    static int max = 1;
    public static ConcurrentHashMap<Point2D, Point2D> points = new ConcurrentHashMap<>();

    //Not used in Concurrent Implementation
//    private static void shotDarts() {
//
//        Point2D p;
//
//        do {
//            //generates random value and in range
//            double random = new Random().nextDouble();
//            double x = min + (random * (max - min));
//
//            //generates random value and in range
//            random = new Random().nextDouble();
//            double y = min + (random * (max - min));
//
//            if (((x * x) + (y * y)) <= 1) {
//                p = new Point2D.Double(x, y);
//                if (!points.contains(p)) {
//                    points.add(p);
//                } else {
//                    p = null;
//                }
//            } else {
//                return;
//            }
//        } while (p == null);
//
//    }

    public static void main(String[] args) throws InterruptedException {

        double nShots = Double.parseDouble(args[0]); //Shots Parameter
        int threadNumber = Integer.parseInt(args[1]); //Thread Parameter
        int magicnumber = (int) Math.floor(nShots /threadNumber);
        int sum = 0;





        Thread[] threads = new Thread[threadNumber];

        for(int i = 0; i< threadNumber; i++){
            if(i == threadNumber -1){
               threads[i] = new Worker((int)(nShots - sum),points);
               threads[i].start();
            }else{
                sum += magicnumber;
                threads[i] = new Worker(magicnumber,points);
                threads[i].start();
            }
        }

        for(int i = 0; i< threadNumber; i++){
            threads[i].join();
        }

            double p = (double) points.size() / nShots;
            double pi = p * 4;
            System.out.print("Total Number of points: " + nShots + "\n" +
                    "Points within the circle: " + points.size() + "\n" +
                    "Pi estimation: " + pi + "\n");




    }
}
