class Solution {
public:
    double angleClock(int hour, int minutes) {
        // Position of minute hand
        double minuteAngle = minutes * 6.0; // 360/60
        
        // Position of hour hand
        double hourAngle = (hour % 12) * 30.0 + minutes * 0.5; // 360/12 + movement due to minutes
        
        double diff = abs(hourAngle - minuteAngle);
        
        return min(diff, 360.0 - diff);
    }
};
