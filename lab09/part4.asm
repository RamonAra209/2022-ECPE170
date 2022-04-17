# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
	la $s0, array_a # puts memory address of a[0] into $s0, like pointers
	la $s1, array_b # puts memory address of b[0] into $s1
	addi $s2, $zero, 12 # C = 12
	addi $s3, $zero, 0 # i = 0

add $t0, $zero, $s0 # stores the starting memory address of array a
add $t1, $zero, $s1 # stores the starting memory address of array b
for_loop:
	bge $s3, 5, end_for # repeat until i >= 5`

	lw $t3, 0($t1) # b: load value at ith position into $t3
	add $t3, $t3, $s2 # b[i] + C
	sw $t3, 0($t0) # a[i] = b[i] + C

	addi $s3, $s3, 1 # i++
	addi $t1, $t1, 4 # increment memory address of b
	addi $t0, $t0, 4 # increment memory address of a 
	j for_loop

end_for: 
	# add $t0, $zero, $s0 # stores the starting memory address of array a
	addi $s3, $s3, -1 # i--
	addi $t0, $t0, -4 # increment memory address of a	

while:
	blt $s3, 0, end # inverse, if i < 0, exit while loop
	lw $t4, 0($t0) # a: load value at ith position into $t4	

	add $t4, $t4, $t4 # a[i] = a[i] * 2
	sw $t4, 0($t0)
	addi $s3 $s3, -1 # i--
	addi $t0, $t0, -4 # increment memory address of a	
	j while

end:
	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data
	array_a: .space 20
	array_b: .word 1, 2, 3, 4, 5

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
