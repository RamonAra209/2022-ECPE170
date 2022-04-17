# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
	addi $s0, $zero, 10 # A = 10
	addi $s1, $zero, 15 # B = 15
	addi $s2, $zero, 6 # C = 6

	li $t0, 5 # var=5 for C < 5 conditional
	bgt $s0, $s1, if_statement # A > B or
	blt $s2, $t0, if_statement # C < 5

	blt $s0, $s1, else # testing for inverse, if true go to else_if
	addi $t2, $s2, 1 # (C + 1)
	li $t0, 7 # temp var = 7
	beq $t2, $t0, else_if # (C+1) == 7 
	j else # jump to else block if beq == false

if_statement:
	addi $s3, $zero, 1
	j switch
else_if:
	addi $s3, $zero, 2 
	j switch
else:
	addi $s3, $zero, 3
	j switch

switch:
	beq $s3, 1, case1
	beq $s3, 2, case2
	j default
	case1:
		addi $s3, $zero, -1
		j end
	case2:
		addi $s3, $zero, -2
		j end
	default:
		addi $s3, $zero, 0
		j end
end:
	sw $s3, z	

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
