.orig x3000
jsr getnum
jsr getnum
halt

getnum
			st r1, gn_sr1
			st r2, gn_sr2
			st r7, gn_sr7
		cdn	getc
			ld r1, ascii_offset
			not r1, r1
			add r1, r1, #1
			add r2, r1, r0
			brn cdn
			ld r2, ascii_offset2
			not r2, r2
			add r2, r2, #1
			add r2, r2, r0
			brp cdn
			add r0, r0, r1
			ld r1, gn_sr1
			ld r2, gn_sr2
			ld r7, gn_sr7
		ret
gn_sr1 .fill 0
gn_sr2 .fill 0
gn_sr7 .fill 0
ascii_offset .fill 48
ascii_offset2 .fill 57
.end