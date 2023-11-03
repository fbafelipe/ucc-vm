; hello world assembly test

.DATA
{
	"Hello World!\n"
}

.TEXT

main:
	set $pr0, 24
	sub $sp, $sp, $pr0
	
	; pointer to the string
	copy $pr0, $gp
	store $pr0, $sp, 8, 16
	
	; push the arguments count
	set $pr0, 1
	store $pr0, $sp, 8, 8
	
	; return addr
	la $pr0, return
	store $pr0, $sp, 8, 0
	
	call printf
	
	; return
return: nop
	
	; remove the parameters from the stack
	set $pr0, 24
	add $sp, $sp, $pr0
	
	halt
