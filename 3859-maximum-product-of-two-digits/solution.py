

class Solution:
    def maxProduct(self, n: int) -> int:
        digits = []
        freq = [0]*10
        temp = n
        while temp >0:
            d = temp % 10
            digits.append(d)
            freq[d] +=1
            temp //= 10
        max_digit_product = 0
        for i in range(len(digits)):
            for j in range(i, len(digits)):
                d1 = digits[i]
                d2 = digits[j]
                if i == j and freq[d1] < 2:
                    continue

                product = d1* d2
                if product > max_digit_product:
               
                    max_digit_product = max(max_digit_product, product)
        return max_digit_product

