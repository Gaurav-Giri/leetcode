class Solution:
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        def check(x):
            rotations_top = rotations_bottom = 0
            for i in range(len(tops)):
                if tops[i] != x and bottoms[i] != x:
                    return float('inf')  # impossible
                elif tops[i] != x:
                        rotations_top += 1  # need to rotate top

                elif bottoms[i] != x:
                    rotations_bottom += 1  # need to rotate bottom
            return min(rotations_top, rotations_bottom)

        candidates = [tops[0], bottoms[0]]
        min_rotations = min(check(candidates[0]), check(candidates[1]))
        return -1 if min_rotations == float('inf') else min_rotations
