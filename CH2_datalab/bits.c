/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * HarveyChen 20180426
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	//return (x&(0xff<<(n<<3)))>>(n<<3);	//the last >> will take logical shift, make 0x80 as 0x ffffff80.
	return (x>>(n<<3))&0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {		
//	int mark=((1<<( (32+(~n+1)) &0x1f))+(~1+1));	//-n=~n+1
//	return (x>>n)&mark;	
// The solution 0x1000 -1 to get 0x0fff is impracticable when wo want to get 0xffffffff, which cause overflow
	int mask=~( ((1<<31) >>n) <<1 );
	return (x>>n)&mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {	
	//byte value 0xff > sizeof(int), so caculate the number of 1b in every byte, partition int into 4 space. Add 4 values at last.
	int tmp=((0x01<<8|0x01)<<8|0x01)<<8|0x01;//tmp=0x01010101
	int val=x&tmp;
	val+=tmp&(x>>1);
	val+=tmp&(x>>2);
	val+=tmp&(x>>3);
	val+=tmp&(x>>4);
	val+=tmp&(x>>5);
	val+=tmp&(x>>6);
	val+=tmp&(x>>7);
	val+=(val>>8);
	val+=(val>>16);
	return val & 0xff;
	
#if 0
	int result=x;;
	int mask1=0x55555555;	//(0101...0101)b
	int mask2=0x33333333;	//(0011...0011)b
	int mask3=0x0f0f0f0f;	//(00001111...00001111)b
	int mask4=0x00ff00ff;	//
	int mask5=0x0000ffff;	//
	result = (result & mask1)+( (result>>1) & mask1);
	result = (result & mask2)+( (result>>2) & mask2);
	result = (result & mask3)+( (result>>4) & mask3);
	result = (result & mask4)+( (result>>8) & mask4);
	result = (result & mask5)+( (result>>16) & mask5);
	return result;

#endif
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	x = (x>>16)| x;	//x |= (x>>16)
	x = (x>>8) | x;	//x |= (x>>8)
	x = (x>>4) | x;
	x = (x>>2) | x;
	x = (x>>1) | x;
  	return (~x) & 0x01;
	// Another solution: return ~( x | (-x) >>31 ) & 0x01;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1<<31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  	int isPositive=!(x>>31);
	int shift=n+(~0);	//n-1
	int P=!(x>>shift);	//when x is positive number
	int N=!((~x)>>shift);	//when x is negative number
	return (isPositive & P) | ((~isPositive) & N);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    return x/(1<<n);//right... but the / operator is banned
//	return x>>n;
// Considering "Round toward zero", x>>n=x/(1<<n) is valid when x is positive. But when x is odd and negative, x>>n is round to smaller one, not "Round to zero".
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x+1);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return (!!x) & (!(x>>31));	//"!!x" means not zero, and "(!(x>>31))" means not negative num.
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {    
	/*
	 The point is overflow.
	 x<=y is equivalent to 0<=y-x. 
	 When overflow occur, signal x is different to signal y, and the signal of the compute result 'y-x' is same as x's(different to y's). But the value of result is same as y's.
	 Thus, when overflow occur, we care the signal of x and y, ignoring (y-x).
	*/
	int sig_x=(x>>31)&0x01;	//signal of x
	int sig_y=(y>>31)&0x01;	//signal of y
	int sig_sub=((y+(~x+1))>>31)&0x01;	//signal of y-x
	//(sig_x^sig_y)&sig_x when signal of x and y is different
	//(sig_x^sig_y^1)&sig_sub when signal of x and y is same
	return ((sig_x^sig_y)&sig_x) | ((sig_x^sig_y^1)&(!sig_sub));
}	
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {	
/*	dichotomy, er fen fa.
	2^n=1<<n, 2^16=1<<16, 2^32=1<<32(overflow)
	
	sizeof(int)=32, so the result of this func n is between 0(0x00) to 31(0x1F). This func is to find the 'most left bit 1' in x.And the result n maximum 31 is also (11111)b, [BIT0] to [BIT4] is 1s.
	Let's consider [BIT4] firstly.
	[BIT4]:	BIT4=(!!(x>>16))<<4;	// If the 'most left bit 1' is in highest 16 bit, [BIT4]=1; If the 'most left bit 1' is lowest 16 bit, [BIT4]=0.
	[BIT3]: BIT3=(!!( x>> (BIT4+8) ))<<3;	
	//If 'the most left bit 1s' is in high 16 bit , (BIT4+8)=24, it will continue comfirming 'the most left bit 1s' is in high 8 bit(bit24 to bit 31) or in the low(bit16 to bit23).
	//If 'the most left bit 1s' is in low 16 bit , (BIT$+8)=8.It will continue comfirming 'the most left bit 1s' is in low 8 bit(bit0 to bit7) or in the high(bit8 to bit15).
	// And so on... to consider [BIT2], [BIT1], [BIT0].
*/
	int BIT4=(!!(x>> 16    )) <<4;
	int BIT3=(!!(x>>(BIT4+8)))<<3;
	int BIT2=(!!(x>>(BIT4+BIT3+4)))<<2;
	int BIT1=(!!(x>>(BIT4+BIT3+BIT2+2)))<<1;
	int BIT0=(!!(x>>(BIT4+BIT3+BIT2+BIT1+1)))<<0;
	return BIT4 | BIT3 | BIT2 | BIT1 | BIT0;
}






/* ignore the following float part - harvey20180427*/

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
