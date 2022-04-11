# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
# 	int A=15;
#   int B=10;
#   int C=7;
#   int D=2;
#   int E=18;
#   int F=-3;
#   int Z=0;
	# Z = (A+B) + (C-D) + (E+F) - (A-C);
	lw $s0 z
	add $t0, 15, 10 # (A + B)
	sub $t1, 7, 2 # (C - D)
	add $t2, 18, 3 # (E + F)
	sub $t3, 15, 7 # (A - C)

	# $t6 = Solution
	add $t6, $t0, $t1 # Adding (A+B) + (C-D)
	add $t6, $t6, $t2 # Adding solution + (E+F)
	sub $t6, $t6, $t3 # Subtracting (A - C) from solution
	sw $t6, z
	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"
	
	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit
	
	# All memory structures are placed after the
	# .data assembler directive
	.data
	z: .word 0

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12