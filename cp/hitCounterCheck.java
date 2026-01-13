
class hitCounter {
    private final int[] times;
    private final int[] hits;
    private final int trackTime;
    
    public hitCounter(int time){
        trackTime = time;
        times =new int[time];
        hits = new int[time];
    }

    public synchronized void hit(int timestamp){
        if(times[timestamp % trackTime] != timestamp){
            times[timestamp % trackTime]=timestamp;
            hits[timestamp % trackTime]=1;
        }
        else{
            hits[timestamp % trackTime]++;
        }
    }

    public synchronized int getHits(int timestamp){
        int totalHit=0;
        for(int i=0;i<trackTime;i++){
            if(timestamp - times[i] < trackTime){
                totalHit += hits[i];
            }
        }
        return totalHit;
    }
}

public class hitCounterCheck {
    public static void main(String[] args) {
        hitCounter counter = new hitCounter(300); // Track hits for the last 300 seconds

        // Simulate some hits
        counter.hit(1);
        counter.hit(2);
        counter.hit(2);
        counter.hit(3);

        // Get hits at timestamp 4
        System.out.println("Hits at timestamp 4: " + counter.getHits(4)); // Should print 4

        // Simulate more hits
        counter.hit(300);
        counter.hit(301);
        counter.hit(302);

        // Get hits at timestamp 302
        System.out.println("Hits at timestamp 302: " + counter.getHits(302)); // Should print 3
    }
}
