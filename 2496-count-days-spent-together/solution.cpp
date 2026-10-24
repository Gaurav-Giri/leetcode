class Solution {
private:
    // Days in each month for a non-leap year
    const int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Helper function to convert "MM-DD" string to the day number of the year (1 to 365)
    int dateToDays(string date) {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        
        int totalDays = 0;
        for (int i = 0; i < month - 1; ++i) {
            totalDays += months[i];
        }
        totalDays += day;
        
        return totalDays;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        // Convert all arrival and departure dates into absolute day numbers
        int startA = dateToDays(arriveAlice);
        int endA = dateToDays(leaveAlice);
        int startB = dateToDays(arriveBob);
        int endB = dateToDays(leaveBob);
        
        // Find the intersection window where both intervals overlap
        int overlapStart = max(startA, startB);
        int overlapEnd = min(endA, endB);
        
        // Calculate total days inside the inclusive overlap window
        if (overlapStart <= overlapEnd) {
            return overlapEnd - overlapStart + 1;
        }
        
        return 0; // No overlap
    }
};

