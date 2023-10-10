.data
	divisor: .space 12							
	remainder: .space 12
	magic: .space 12
	sID: .string "s1103309\n"
	in_msg1: .string "input divisor "
	in_msg2: .string "input remainder "
	colon: .string ": "
	endl: .string "\n"
	out_msg1: .string "magic numbers are "
	out_msg2: .string "answer="
	space: .string ","
	
.text 
	main:
		la t0, in_msg1			### t0 = start of .string in_msg1
		li t1, 0				### used to count times of loops
		la t2, colon			### t2 = start of .string colon
		li t3, 3				### a constant, indicating how many times the loop should be done
		la s0, divisor			### s0 = pointer to divisor array
		la s1, remainder		### s1 = pointer to remainder array 
		la s2, magic			### s2 = pointer to magic array
	#print_sID:
		la a0, sID			
		li a7, 4
		ecall					### print sID
	loop1:
		addi t1, t1, 1			### start of loop1, ++t1
		mv a0, t0
		li a7, 4
		ecall					### print "input divisor"
		mv a0, t1
		li a7, 1
		ecall 					### printInt: 1 or 2 or 3
		mv a0, t2
		li a7, 4
		ecall					### print ": "
		li a7, 5
		ecall					### get input from keyboard
		sw a0, 0(s0)			### SAVE a0(input) to s0(divisor*)
		addi s0, s0, 4			### move s0(divisor*) 4 bytes forward
		bne t1, t3, loop1		### if t1!=t3, jump to loop
		
		la t0, in_msg2			### t0 = start of in_msg2		
		li t1, 0				### t1 = 1 (to count in the loop)
	loop2:
		addi t1, t1, 1			### start of loop 2, ++t1
		mv a0, t0				
		li a7, 4
		ecall					### print "input remainder"
		mv a0, t1
		li a7, 1
		ecall 					### printInt: 1 or 2 or 3
		mv a0, t2
		li a7, 4
		ecall					### print ": "
		li a7, 5
		ecall					### get input from keyboard
		sw a0, 0(s1)			### save a0(input) to s1(remainder*)
		addi s1, s1, 4			### move s1(remainder*) 4 bytes forward
		bne t1, t3, loop2		### if t1!=t3, jump to loop2
		
	# print output message
		la a0, endl				
		li a7, 4
		ecall					### print "\n"
		la a0, out_msg1
		ecall					### print "magic numbers are "
		
	# calc magic numbers
		la s0, divisor			### s0 = start of divisor
		lw t0, 0(s0)			### t0 = divisor[0]
		lw t1, 4(s0)			### t1 = divisor[1]
		lw t2, 8(s0)			### t2 = divisor[2]
		li t6, 1 				### used to determine if remainder == 1
		
	# magic 1		
		mul t4, t1, t2			### t4 = divisor[1] * divisor[2]
		li t3, 0				### set t3 = 0 (t3 reserved for magic num)
	find1:
		add t3, t3, t4			### t3 += t4
		rem t5, t3, t0			### t5 = t3 % divisor[0]
		bne t5, t6, find1		### if t5!=1, jump to find1
		
		sw t3, 0(s2)			### save t3 to magic[0]
		mv a0, t3				
		li a7, 1
		ecall					### print this magic number
		la a0, space			
		li a7, 4
		ecall					### print a space (comma)
		
	# magic 2
		mul t4, t0, t2			### t4 = divisor[0] * divisor[2]
		li t3, 0				### set t3 = 0 (t3 reserved for magic num)
	find2:
		add t3, t3, t4			### t3 += t4
		rem t5, t3, t1			### t5 = t3 % divisor[1]
		bne t5, t6, find2		### if t5!=1, jump to find2
		
		sw t3, 4(s2)			### save t3 to magic[1]
		mv a0, t3
		li a7, 1
		ecall					### print this magic number
		la a0, space
		li a7, 4
		ecall					### print a space (comma)
		
	# magic 3
		mul t4, t0, t1			### t4 = divisor[0] * divisor[1]
		li t3, 0				### set t3 = 0 (t3 reserved for magic num)
	find3:
		add t3, t3, t4			### t3 += t4
		rem t5, t3, t2			### t5 = t3 % divisor[2]
		bne t5, t6, find3		### if t5!=1, jump to find2
		
		sw t3, 8(s2)			### save t3 to magic[2]
		mv a0, t3
		li a7, 1
		ecall					### print this magic number
		la a0, space
		li a7, 4
		ecall					### print a space (comma)
	
	# magic 4
		mul s3, t0, t1			
		mul s3, s3, t2			### t3 =  divisor[0] * divisor[1] * divisor[2] 
		mv a0, s3				
		li a7, 1
		ecall					### print the last magic number
		
	# calc answer
		la s1, remainder		### s1 = start of remainder array
		li s4, 0				### s4 is reserved for the answer
		li t0, 0				### t0 = 0 (to count the times of loop)
		li t1, 3				### t1 = 3 (the time to stop)
		
	loop3:
		addi t0, t0, 1			### start of loop3
		lw t2, 0(s1)			### t2 = *(remainder)
		lw t3, 0(s2)			### t3 = *(magic)
		mul t4, t2, t3			### t4 = t2 * t3
		add s4, s4, t4			### s4 += t4
		addi s1, s1, 4			### move s1(remainder*) 4 bytes forward
		addi s2, s2, 4			### move s2(magic*) 4 bytes forward
		bne t0, t1, loop3		### if t0!=t1, jump to loop3
		
		rem s4, s4, s3			### s4 %= s3 (The Answer!)
		
	# print answer
		la a0, endl
		li a7, 4
		ecall					### print "\n"
		la, a0, out_msg2
		ecall					### print "answer="
		mv a0, s4
		li a7, 1
		ecall					### print the answer
	
	# exit
		li a7, 10
		ecall					### exit(0)
	
		
		
		
