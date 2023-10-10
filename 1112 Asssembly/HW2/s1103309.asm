.data
	steps: .space 48 		### at most 12 stairs, create an array of 12*4 Bytes
	sID: .string "s1103309\n"
	question: .string "How many stairs?\n"
	answer: .string "Step Combinations:\n"
	start: .string ": { "
	finish: .string "}\n"
	space: .string " "
	
.text
	main:
		#print my sID
		la a0, sID 			### load the addr of sID into a0 as an arg
		li a7, 4 			### set a7 to 4, indicatiing [PrintString]
		ecall 				### environment call, [PrintString]
		
		# print the question
		la a0, question 	### load the addr of sID into a0 as an arg
		li a7, 4			### set a7 to 4, indicatiing [PrintString]
		ecall				### environment call, [PrintString]
		
		# read number of stairs
		li a7, 5			### set a7 to 4, indicatiing [ReadInt]
		ecall				### environment call, [ReadInt] (read to a0)
		
		# prepare args to call function 
		# a0:n; a1:current_pointer;
		la a1, steps		### set a1(index) to 0
		li s0, 1			### s0 is count the answers
		jal calculate		### jump to "calculate" (link ra)	
		
		li a7, 10			### set a7 to 10 to exit
		ecall 				### environment call
	
	# the "calculate" function
	calculate:
		li t0, 1			### set t0 to 1
		bge a0, t0, bge1	### if a0 >= t0 (if n >= 1), jump to "bge1"
	if2:
		li t0, 2			### set t0 to 2
		bge a0, t0, bge2	### if a0 >= t0 (if n >= 2), jump to "bge2"
		
		# if n != 0, ignore and jump to end
		li t0, 0			### set t0 to 0
		bne a0, t0, end		### if n != 0, jump to end
		
		# if n == 0
		la a0, answer
		li a7, 4
		ecall				### print string "Step Combinations: "
		mv a0, s0
		li a7, 1
		ecall				### print the data of s0 (count of answers)
		la a0, start
		li a7, 4
		ecall				### print the string ": { "
		la a1, steps 		### point a1 to the start of array
	
	# the loop to print the answer
	loop:
		lw a0, 0(a1)		### load data from the address a1 currently pointing to
		li a7, 1			### a7 = 1, [PrintInt]
		ecall				### environment call
		la a0, space		
		li a7, 4
		ecall				### print a space
		addi a1,a1,4		### move a1 (pointer) 4 bytes forward
		bne a1, a3, loop	### if a1 != a3 (if pointer != wall), jump back to "loop"
		
		# after loop
		la a0, finish		
		li a7, 4
		ecall				### print the string "}\n"
		addi s0, s0, 1		### S0 += 1 (++answer_count)
		j end				### jump to "end" (return)
		
	# section for case n >= 1
	bge1:
		jal t6, set_sp 		### call "set_sp" to store data in the stack
		sw t0, 0(a1)		### save t0 to the array (steps[index] = 1)
		addi a1, a1, 4		### move the array pointer 4-Byte forward (++index)
		mv a3, a1			### a3 is the wall of the array (set the wall to index)
		sub a0, a0, t0		### a0 -= t0 (n -= 1)
		jal calculate		### recursively call "calculate", link next line to ra
		jal t6, get_sp		###	call "get_sp" to restore the data previously saved in the stack
		j if2				### jump back to the unfinished part (label "if2")
		
	# section for case if n >= 2
	bge2:
		jal t6, set_sp		### call "set_sp" to store data in the stack, link t6 (without overwriting ra)
		sw t0, 0(a1)		### save t0 to the array (steps[index] = 2)
		addi a1, a1, 4		### move the array pointer 4-Byte forward (++index)
		mv a3, a1			### a3 is the wall of the array (set the wall to index)
		sub a0, a0, t0		### a0 -= t0 (n -= 2)
		jal calculate		### recursively call "calculate", link next line to ra
		jal t6, get_sp		###	call "get_sp" to restore the data of registers, link t6 (without overwriting ra)
		j end				### jump to "end" directly (return to the address stored in ra)
		
	# the "set_sp" function
	set_sp:
		addi sp, sp, -12	### move stack_pointer 12 Bytes backwards to make space 	
		sw ra, 8(sp)		### push ra into stack
		sw a0, 4(sp)		### push a0 (n) into stack
		sw a1, 0(sp)		### push a1 (the array pointer) into stack
		jr t6				### jump to the address previously linked using t6
		
	# the "get_sp" function
	get_sp:
		lw a1, 0(sp)		### load corresponding data from stack to a1
		lw a0, 4(sp)		### load corresponding data from stack to a0
		lw ra, 8(sp)		### load corresponding data from stack to ra
		addi sp, sp, 12		### move stack_pointer 12 bytes forward (pop from stack)
		jr t6				### jump to the address previously linked using t6
		
	end:
		ret					### return (jump to address linked with ra)
		
