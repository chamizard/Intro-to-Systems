.orig x3000
getc
add r1, r0, #0
getc
not r2, r1
add r2, r2, #1
add r3, r0, #0
add r2, r3, r2
brnz #4
out
add r0, r1, #0
out
brnzp #5
add r2, r0, #0
add r0, r1, #0
out
add r0, r2, #0
out
halt