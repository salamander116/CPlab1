import java.awt.geom.Point2D;
import java.util.concurrent.ConcurrentHashMap;

public class MonteSeq {

    public static ConcurrentHashMap<Point2D, Point2D> points = new ConcurrentHashMap<>(); //Shared dataStructure for each

    public static void main(String[] args) throws InterruptedException {

        double nShots = Double.parseDouble(args[0]); //Shots Parameter
        int threadNumber = Integer.parseInt(args[1]); //Thread Parameter
        int magician = (int) Math.floor(nShots / threadNumber); //Magic number for estimating the shooting amount of each thread
        int sum = 0; //accumulator for last thread load calculation
        Thread[] threads = new Thread[threadNumber];


        //Starts each worker
        for (int i = 0; i < threadNumber; i++) {
            if (i == threadNumber - 1) {
                threads[i] = new Worker((int) (nShots - sum), points);
            } else {
                sum += magician;
                threads[i] = new Worker(magician, points);
            }
            threads[i].start();
        }

        //Waits for all workers to be done
        for (int i = 0; i < threadNumber; i++) {
            threads[i].join();
        }

        //There are several ways of employing concurrency mechanisms, the above one is just one of them
        double p = (double) points.size() / nShots;
        double pi = p * 4;
        System.out.print(
                "Total Number of points: " + nShots + "\n" +
                        "Total number of Threads " + threadNumber + "\n" +
                        "Points within the circle: " + points.size() + "\n" +
                        "Pi estimation: " + pi + "\n");


    }
}
