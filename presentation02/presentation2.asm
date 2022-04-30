        # A Stub to develop assembly code using QtSPIM
        # Declare main as a global function
        .globl main

        # All program code is placed after the
        # .text assembler directive
        .text

# The label 'main' represents the starting point
main:
        li $t0, 0               # i = 0
        la $s0, array           # load array into $s0

        for_loop:
            bge $t0, 5, end     # if $t0 >= 5, jump to end

            # else: 
                lw $t1, 0($s0)      # load val from current position in stack 
                
                li $v0, 4           # 4 allows us to print string
                la $a0, string_arr1 # load string 
                syscall            # prints "Array["

                li $v0, 1           # 1 allows us to print int 
                move $a0, $t0       # load index into $a0 registry
                syscall             # prints index
                
                li $v0, 4           # 4 allows us to print string 
                la $a0, string_arr2 # load string into $a0 reigstry
                syscall             # prints "] = "

                li $v0, 1           # 1 allows us to print int 
                move $a0, $t1       # move val in stack to $a0
                syscall             # prints val at array[i]

                li $v0, 4           # 4 allows us to print string 
                la $a0, new_line    # load string into $a0 registry 
                syscall             # prints new line

                addi $s0, $s0, 4    # moves pointer to next index in the array
                addi $t0, $t0, 1    # i++

            j for_loop          # restart for loop

        end:
            li $v0, 4               # 4 allows us to print string 
            la $a0, string_sum_arr  # load string into $a0 registry 
            syscall                 # print "Sum of array is "
            
            # Recursive function call 
            # storing values into $a0 and $a1
            la $a0, array   # storing the array into $a0 
            li $a1, 5       # storing the length of the array into $a1
            jal sum_array

            move $a0, $v0   # move value returned by function into $a0
            li $v0, 1       # 1 allows us to print int
            syscall         # print sum returned by recurisve function

        # Exit the program by means of a syscall.
        # There are many syscalls - pick the desired one
        # by placing its code in $v0. The code for exit is "10"

        li $v0, 10 # Sets $v0 to "10" to select exit syscall
        syscall # Exit

        sum_array:
            # $a0 = address of the current place in array
            # $a1 = len of rest of the array
            beq $a1, 0, result_zero # if arr size == 0
            sw $ra, 0($sp)      # Stores return address in stack
            addi $sp, $sp, -4   # move stack down so that ra isn't overwritten
            lw $t0, 0($a0)      # getting the value of the Array

            sw $t0, 0($sp)      # Push value of array onto stack
            addi $sp, $sp, -4   # move stack down so that array val isnt overwritten 

            addi $a0, $a0, 4    # offset pointer to next value
            addi $a1, $a1, -1   # decrement len of array
           
            jal sum_array
            addi $sp, $sp, 4    # move stack down
            lw $t0, 0($sp)      # pop array value off of stack
            add $v0, $t0, $v0   # add array value to current sum

            addi $sp, $sp, 4    # move stack down
            lw $ra, 0($sp)      # pop return address from stack

            jr $ra              # return from function
            #* ra saves the state/place where the function was called in program

            result_zero:        # return 0
                li $v0, 0
                jr $ra

        # All memory structures are placed after the
        # .data assembler directive
        .data
        array: .word 2, 3, 5, 7, 11
        string_arr1: .asciiz "Array["
        string_arr2: .asciiz "] = "
        new_line: .asciiz "\n"
        string_sum_arr: .asciiz "Sum of array is "
        # The .word assembler directive reserves space
        # in memory for a single 4-byte word (or multiple 4-byte words)