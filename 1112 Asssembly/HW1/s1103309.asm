# comment by professor (one #)
## comment by me, so I can understand better (two #)
### comment for the assignment (added code) (three #)

###s1103309 王聖允

.data ## data section contains all the declaration of words and strings
one: .word 1 ## allocate 32-bit (4 bytes) in the memory to save this word
str1: .string " input number X= "
str2: .string " input number N= "
sID: .string "s1103309\n" ### create a string containing "s1103309\n\0" (ascii, null terminated)
Und: .string "undefined" ### a string containing "undefined"
Ovfl: .string "overflow" ### a string containong "overflow"

## the `.string` can be replaced with `.asciz`

.text
main:
    jal printID 	### jump to the symbol 'printID', and save address of next command in `ra`
	jal printMsg1	## jump to symbol `printMsg1`, and save next command's address in `ra`
	jal inputXN		# return the result a0	
	mv s0,a0		# Set s0 equal to the result (X: s0)
	jal printMsg2	## jump to symbol `printMsg2`, and save next command's address in `ra`
	jal inputXN		# return the result a0	
	mv s1,a0		# Set s1 equal to the result (N: s1)
	
	mv a0,s0 		## a0<-s0 (X)
	mv a1,s1		## a1<-s1 (N)
	jal power 		# power(X=a0, N=a1), return a0
	mv s0,a0		## s0<-a0 (result)
	jal printResult #printResult(s0)
	j end

power: 
	beq a1, zero, cmp_X	### break if(N == 0), and turn to `cmp_X`
	
	li t0, 0 			## t0 is used to count from 0 to (a1-1) 
	mv t1, a0			## t1 = X
	addi a1,a1,-1		## a1 -= 1
loop: 
	bge t0, a1, endpower 		## loop continues if(t0 <= a1)
	mv t2, a0					### temporarily save a0 to t2 (before `mul`)
	mul a0, a0, t1				## a0 *= t1
	
	blt a0, t2, printOvfl		### after `mul`, if (a0 < t2) means an overflow occurs, jump to printOvfl
								### this can handle most of the overflow cases, but not all (e.g. 10^10)
								
	addi t0, t0, 1				## ++t0
	jal  x0, loop 				## jump to the start of loop, but don't save address in `ra`
								## the above line can be replaced with `j loop`
								
cmp_X:
	beqz a0, printUnd	### if (X also == 0), jump to `printUnd`, else continue to `assign_zero:`
							
assign_zero:			### code segment to assign 0 to result, in case (X != 0 &&N == 0)
	li a0, 0			### set a0(result) to 0, conntinue to `endpower`
	
endpower: 
	jr ra				## jump register `ra`, which is previously saved
						## this line can be replaced with `ret` (return)

printResult:
	mv a0,s0
	li a7, 1			## print int (result)
 	ecall
 	ret
inputXN:
	li a7,5
	ecall
	ret
		
printMsg1:
	la a0, str1			# prepare to print string 1
	li a7, 4			# print string
 	ecall
 	ret
 
printMsg2:
	la a0, str2			# prepare to print string 2
	li a7, 4			# print string
 	ecall
 	ret

printID: 				### function to print string of sID
	la a0, sID 			### load the address of the sID string
	li a7, 4 			### load '1' to a7, in order to make ecall of 'printing a string'
	ecall 				### after a7 is set, make the environment call
	ret 				### return to the address of the next command after jal (saved in ra)
	
printOvfl:				### if overflow occurs, jump to here to print "overflow"
	la a0, Ovfl			### set a0 to the starting address of string `Ovfl`
	li a7, 4			### set a7 to 4, in order to make ecall of print_string
	ecall				### after a0 and a7 is ready, make the environment call
	j end				### jump to the end

printUnd:				### jump to this segment when 0^0 is encountered
	la a0, Und			### set a0 to the starting address of string `Und`
	li a7, 4			### set a7 to 4, in order to make ecall of print_string
	ecall				### after a0 and a7 is ready, make the environment call
 	
end:
	li a7, 10			
 	ecall

