class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        result  = 0
        count = defaultdict(int)
        
        for a, b in dominoes:
            key  = tuple(sorted((a, b)))
            result += count[key]
            count[key]+= 1

        return result
