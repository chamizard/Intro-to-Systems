.orig x3000
and r0, r0, #0
add r0, r0, #15
add r0, r0, #15
add r0, r0, #15
add r0, r0, #3
and r2, r2, #0
add r2, r1, r2
brz #6
out
add r0, r0, #1
not r2, r1
add r2, r2, r1
add r1, r1, r2
brnp #-9
halt