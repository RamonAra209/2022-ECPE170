# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
	lw $s0, z
	lw $s1, i

first_while:
	bgt $s1, 20, do_while # if i > 20, break / jump to do-while
	addi $s0, $s0, 1 # increment Z
	addi $s1, $s1, 2 # increment i by 2
	j first_while  # repeat while until conditions satisfied

do_while: 
	addi $s0, $s0, 1 # Z++ 
	blt $s0, 100, do_while # while (Z < 100)

second_while:
	ble $s1, 0, end # Check inverse, if i <= 0, don't run second_while
	addi $s0, $s0, -1 # Z--
	addi $s1, $s1, -1 # i--
	j second_while # repeat second_while until condition satisfied

end:
	sw $s0, z
	sw $s1, i

	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data
	z: .word 2
	i: .word 0
	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
