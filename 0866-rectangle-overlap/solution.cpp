class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // Check if one rectangle is completely to the left, right, above, or below the other.
        // If none of these conditions are true, they must overlap.
        return (rec1[0] < rec2[2] && rec2[0] < rec1[2] && 
                rec1[1] < rec2[3] && rec2[1] < rec1[3]);
    }
};

