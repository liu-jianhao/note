package main

import "fmt"
import "os"
import "strconv"

func divide(numerator int, denominator int) int {
	quotient := 0
	for numerator >= denominator {
		numerator -= denominator
		quotient++
	}
	return quotient
}

func neg(a int, b int, r int) int {
	if (a < 0) != (b < 0) {
		return -r
	} else {
		return r
	}
}

const INT_MAX = int(^uint(0) >> 1)

func abs(a int) (ret int) {
	ret = (a ^ a>>31) - a>>31
	return
}

func division_naive(num int, den int) int {
	if den == 0 {
		return INT_MAX
	} else {
		abs_num := abs(num)
		abs_den := abs(den)

		quo := 0
		for abs_num >= abs_den {
			abs_num -= abs_den
			quo++
		}
		return neg(num, den, quo)
	}
}

func division_optimized(num int, den int) int {
	if den == 0 {
		return INT_MAX
	} else {
		abs_num := abs(num)
		abs_den := abs(den)

		var quo uint
		var bits uint
		for abs_num >= abs_den {
			bits = 0
			for abs_num >= abs_den<<bits {
				abs_num -= abs_den
				quo += 1 << bits
				bits++
			}
		}
		return neg(num, den, int(quo))
	}
}
func main() {
	if len(os.Args) != 3 {
		fmt.Printf("Usage: %s num1 num2\n", os.Args[0])
		os.Exit(0)
	}
	num1, _ := strconv.Atoi(os.Args[1])
	num2, _ := strconv.Atoi(os.Args[2])
	fmt.Printf("%d / %d = %d\n", num1, num2, division_naive(num1, num2))
	fmt.Printf("%d / %d = %d\n", num1, num2, division_optimized(num1, num2))
}
