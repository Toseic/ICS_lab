/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
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
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x)|(~y));
}
/* 
 * bitConditional - x ? y : z for each bit respectively
 *   Example: bitConditional(0b00110011, 0b01010101, 0b00001111) = 0b00011101
 *   Legal ops: & | ^ ~
 *   Max ops: 8
 *   Rating: 1
 */
int bitConditional(int x, int y, int z) {
  return (x&y)|((~x)&z);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int mask1, n4, m4, mask2, mask3, y;
    mask1 = 0xff;
    n4 = n << 3;
    m4 = m << 3;
    mask2 = mask1 << n4;
    mask3 = mask1 << m4;
    y = x&(~mask2);
    y = y &(~mask3);
    return (y|(((x&mask2)>>n4<<m4)&(mask1<<m4))|(((x&mask3)>>m4<<n4)&(mask1<<n4)));

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
    int mask, n_is_zero;
    mask = (1 << (~n + 0x01 + 0x20)) + ~0;
    n_is_zero = !(!n);
    return (x>>n)&(mask|(n_is_zero+~0));
}
/* 
 * cleanConsecutive1 - change any consecutive 1 to zeros in the binary form of x.
 *   Consecutive 1 means a set of 1 that contains more than one 1.
 *   Examples cleanConsecutive1(0x10) = 0x10
 *            cleanConsecutive1(0xF0) = 0x0
 *            cleanConsecutive1(0xFFFF0001) = 0x1
 *            cleanConsecutive1(0x4F4F4F4F) = 0x40404040
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 4
 */
int cleanConsecutive1(int x){
    int x_left_shift1,x_right_shift1,left_empty,right_empty;
    x_left_shift1 = x << 1 & (~1);
    x_right_shift1 = x >> 1 & (~(1<<31));
    left_empty = x & (~x_right_shift1);
    right_empty = x & (~x_left_shift1);
    return left_empty & right_empty;
}
/* 
 * countTrailingZero - return the number of consecutive 0 from the lowest bit of 
 *   the binary form of x.
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   YOU MAY USE BIG CONST IN THIS PROBLEM, LIKE 0xFFFF0000
 *   Examples countTrailingZero(0x0) = 32, countTrailingZero(0x1) = 0,
 *            countTrailingZero(0xFFFF0000) = 16,
 *            countTrailingZero(0xFFFFFFF0) = 4,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int countTrailingZero(int x){
    int cons_16,cons_8;
    int morthan_16, morthan_8;
    int shifted_x_1, shift_len_1;
    cons_16 = 0x0000FFFF;
    cons_8 = 0xFFFFFF00;

    morthan_16 = !((cons_16) & x);
    morthan_8 = !((~(cons_8 << (morthan_16 << 4))) & x);
    shift_len_1 = ((morthan_16 << 4)+ (morthan_8 << 3));
    shifted_x_1 = x >> shift_len_1;

    return shift_len_1 + (
      !(shifted_x_1 & (0x1)) +
      !(shifted_x_1 & (0x3)) +
      !(shifted_x_1 & (0x7)) +
      !(shifted_x_1 & (0xf)) +
      !(shifted_x_1 & (0x1f)) +
      !(shifted_x_1 & (0x3f)) +
      !(shifted_x_1 & (0x7f)) +
      !(shifted_x_1 & (0xff))
    );
 
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
    return (x+((~(!(!(x&(1<<31)))+(~0)))&((1<<(n))+~0))) >> n;
}
/* 
 * oneMoreThan - return 1 if y is one more than x, and 0 otherwise
 *   Examples oneMoreThan(0, 1) = 1, oneMoreThan(-1, 1) = 0
 *   Legal ops: ~ & ! ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int oneMoreThan(int x, int y) {
  return (!((x+1)^y))&((!y)|(!((x>>31)^(y>>31))));
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    // int is_neg,upover,upline,one_left_31,x1;
    // one_left_31 = 1<<31;
    // is_neg = x>>31;
    // upline = (0x2a<<24)+(0xaa<<16)+(0xaa<<8)+(0xab);
    // x1 = x^is_neg;
    // upover = ~((x1+1+~upline)>>31);
    // return (upover&(~((is_neg)|(one_left_31))+((is_neg)&(one_left_31))))+((~upover)&((x<<1)+x));
    int is_neg, x1, x1_isneg,x2,x2_isneg,one_left_31,overflow;
    one_left_31 = 1<<31;
    is_neg = x>>31;
    x1 = x +x;
    x1_isneg = x1>>31;
    x2 = x1+x;
    x2_isneg = x2>>31;
    overflow = ~(is_neg^one_left_31);
    return ((~((x1_isneg^is_neg)|(is_neg^x2_isneg)))&x2)+(((x1_isneg^is_neg)|(is_neg^x2_isneg))&overflow);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    int y1,x_is_neg,y1_is_neg,x_y1_isdiff,x_plus_y1_is_neg;
    y1 = ~y+(1^(!(y^(1<<31))));
    x_is_neg = x>>31;   y1_is_neg = y1>>31;
    x_y1_isdiff = x_is_neg^y1_is_neg;
    x_plus_y1_is_neg = (x+y1+(!(y^(1<<31))))>>31;
    return !((~(x_y1_isdiff))&(x_is_neg^x_plus_y1_is_neg));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int neg_y,x_is_neg,negy_is_neg, x_plus_negy,x_plus_negy_isneg;
    neg_y = (~y)+1;
    x_is_neg = x>>31;
    negy_is_neg = neg_y>>31;
    x_plus_negy = x+neg_y;  // x-y
    x_plus_negy_isneg = x_plus_negy>>31;
    return (!(x^y))|((!(!(((~(x_is_neg^negy_is_neg))&(x_plus_negy_isneg^x_is_neg))^(x_plus_negy_isneg))))&(!(!(y^(1<<31)))));
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
    int a1,a2,a3,a4,a5;
    a1 = x&0x3;
    a2 = (x&1)<<1;
    a3 = (a1+a2);
    a4 = a3&(~0x3);
    a5 = !(!((a3&0x3)&(x>>31)));
    return (x>>1)+(x>>2)+(!(!a4))+a5;
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
    int mask1, mask3, simp_1, maskans1, maskans3;
    unsigned uf1;
    mask1 = ((1<<8)-1)<<23;
    uf1 = uf;
    maskans1 = uf & mask1;
    mask3 = (1<<23) -1;
    maskans3 = uf & mask3;
    simp_1 = 1<<23;
    if (maskans1) {
        if (maskans1 >= 0x7f000000) {
          if ((maskans1 == 0x7f800000) && maskans3) {
            return uf;
          }
          return 0x7f800000|((1<<31)&uf);
        }
        return uf + simp_1;
    } else if (maskans3) {
          return (uf1^maskans3)|((maskans3<<1));
    }
    return uf;
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
  int x1,x2, p1, one_left_shift_31;
  one_left_shift_31 = 1<<31;
  x1 = x;
  if (x == 0) {
    return 0;
  }
  if (x == 0x80000000) {
    return 0xcf000000;
  }
  if (x<0) {
    x1 = -x;
  }
  p1 = 31;
  while (p1--) {
    if ((x1>>(p1))) {
      break;
    }
  }
  x1 &= ~(1<<(p1));
  
  if (p1>23) {
    x2 = x1 << (55-p1);
    x1 = x1>>(p1-23);
    if (!(x2^one_left_shift_31)) {
      if (x1%2 != 0) {
          x1++;
      }
    } else {
      if (x2<0) {
        x1++;
      }
    }
  } else {
    x1 = x1 << (23-p1);
  }
  return ((x&one_left_shift_31)+((127+p1)<<23)+x1);
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int exp,ans;
  unsigned int mask1, mask2, is_neg, t, mask_ans1, mask_ans2;
  mask1 = 0x7f800000;
  mask2 = 0x007fffff;
  is_neg = uf>>31;
  mask_ans1 = uf&mask1;
  mask_ans2 = uf&mask2;
  if (!mask_ans1) {
    return 0;
  } 
  exp = (mask_ans1 >> 23)-127;
  if (exp<0) {
    return 0;
  } 
  t = 31;
  mask_ans2 += 1<<(23);
  if (exp > 30) {
    return 0x80000000u;
  }
  if (exp<23) {
    ans = mask_ans2>>(23-exp);
  }else {
    ans = mask_ans2<<(exp-23);
  }
  if ((uf&(1<<31))) {
    ans = -ans;
  }
  return ans;
  
}
/* 
 * float_pwr2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned float_pwr2(int x) {
  int exp;
  if (x>127) {
    return 0x7f800000u;
  } else if (x<-149) {
    return 0;
  }
  if (x<-126) {
    return 1<<((149+x));
  } else {
    exp = x+127;
    return exp<<(23);
  }
}
