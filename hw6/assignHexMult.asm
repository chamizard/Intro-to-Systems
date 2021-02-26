.orig x3000
jsr get4h
jsr get4h
halt

gethd
			st r1, gethd_sr1
			st r2, gethd_sr2
			st r7, gethd_sr7
		cdn	getc
			ld r1, ascii_offset2 ;57
			not r1, r1
			add r1, r1, #1
			add r2, r1, r0
			brp br1 ;if input is greater than 9 branch to next
			ld r1, ascii_offset
			ld r2, ascii_offset 
			not r2, r2
			add r2, r2, #1
			add r2, r2, r0
			brzp ext ;if input is equal or greater than 0 branch to exit
			brn cdn ;if input is less than 0 reenter input
		br1	ld r1, ascii_offset4 ;70
			not r1, r1
			add r1, r1, #1
			add r2, r1, r0
			brp br2 ;if input is greater than F than branch to next
			ld r1, ascii_offset7 ;55
			ld r2, ascii_offset3 ;65
			not r2, r2
			add r2, r2, #1
			add r2, r2, r0
			brzp ext ;if input is equal or greater than A branch to exit
			brn cdn ;if input is less than A reenter input
		br2	ld r1, ascii_offset6 ;102
			not r1, r1
			add r1, r1, #1
			add r1, r1, r0
			brp cdn ;if input is greater than f reenter input
			ld r1, ascii_offset8 ;87
			ld r2, ascii_offset5 ;97
			not r2, r2
			add r2, r2, #1
			add r2, r2, r0
			brn cdn ;if input is less than a reenter input
		ext	out
			not r1, r1
			add r1, r1, #1
			add r0, r0, r1
			ld r1, gethd_sr1
			ld r2, gethd_sr2
			ld r7, gethd_sr7
		ret
		
mult
			st r1, mult_sr1
			st r2, mult_sr2
			st r7, mult_sr7
			and r0, r0, #0 ;clear r0 first
			add r1, r1, #0 ;test if the first number is zero and if it is branch to the end
			brz zee
			add r2, r2, #0 ;test if the second number is zero and if it is branch to the end
			brz zee
			add r0, r1, #0 
			not r0, r0
			add r0, r0, #1
			add r0, r0, r2
			brnz fsr
			add r0, r1, #0
			and r1, r1, #0 ;swap the numbers if r2 is bigger than r1
			add r1, r2, #0
			add r2, r0, #0
		fsr and r0, r0, #0
		top	add r0, r1, r0 ;start of the multiplication loop
			not r2, r2
			add r2, r2, #1
			not r2, r2
			brnp top
		zee	ld r1, mult_sr1
			ld r2, mult_sr2
			ld r7, mult_sr7
		ret
		
get4h
			st r1, get4h_sr1
			st r2, get4h_sr2
			st r7, get4h_sr7
			jsr gethd
			ld r1, hex_col1
			add r2, r0, #0
			jsr mult
			st r0, temp
			jsr gethd
			ld r1, hex_col2
			add r2, r0, #0
			jsr mult
			ld r1, temp
			add r0, r1, r0
			st r0, temp
			jsr gethd
			ld r1, hex_col3
			add r2, r0, #0
			jsr mult
			ld r1, temp
			add r0, r1, r0
			st r0, temp
			jsr gethd
			ld r1, hex_col4
			add r2, r0, #0
			jsr mult
			add r2, r0, #0
			ld r0, newline
			out
			ld r1, temp
			add r0, r1, r2
			ld r1, get4h_sr1
			ld r2, get4h_sr2
			ld r7, get4h_sr7
		ret
gethd_sr1 .fill 0
gethd_sr2 .fill 0
gethd_sr7 .fill 0
mult_sr1 .fill 0
mult_sr2 .fill 0
mult_sr7 .fill 0
get4h_sr1 .fill 0
get4h_sr2 .fill 0
get4h_sr7 .fill 0
ascii_offset .fill 48 ;0
ascii_offset2 .fill 57 ;9
ascii_offset3 .fill 65 ;A
ascii_offset4 .fill 70 ;F
ascii_offset5 .fill 97 ;a
ascii_offset6 .fill 102 ;f
ascii_offset7 .fill 55 ;converts A-F to decimal
ascii_offset8 .fill 87 ;converts a-f to decimal
hex_col1 .fill 4096
hex_col2 .fill 256
hex_col3 .fill 16
hex_col4 .fill 1
temp .fill 0
newline .fill 10
.end