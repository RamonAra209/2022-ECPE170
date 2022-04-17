# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
	la $s0, buffer # load input buffer
	li $v0, 8 # read string syscode
	la $a0, buffer # address of buffer
	li $a1, 256 # buffer size
	syscall

	lb $t0, 0($s0) # loads first character into $t0

while:
	beq $t0, 0, e_not_found
	beq $t0, 101, e_found
	addi $s0, $s0, 1 # check next character in buffer
	lb $t0, 0($s0) # loads first character into $t0
	j while

e_found:
	li $v0, 4 # print string syscode
	la $a0, string_found_1 # load string not found message into $a0
	syscall

	li $v0, 1 # print integer that corresponds to mem address
	add $a0, $zero, $s0 # Adds address from $s0 to $a0
	syscall

	li $v0, 4 # print string syscode
	la $a0, string_found_2 # load string not found message into $a0
	syscall
	j end

e_not_found:
	li $v0, 4 # print string syscode
	la $a0, string_not_found # load string not found message into $a0
	syscall

end:
	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data
buffer: .space 256
string_found_1: .asciiz "First match found at address "
string_found_2: .asciiz "\nThe matching character is e\n"
string_not_found: .asciiz "No match found\n"
	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
