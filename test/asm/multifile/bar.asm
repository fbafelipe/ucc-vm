.DATA
{
	"bar\n"
}

.TEXT

bar:
	; grow the stack
	set $pr0, 24
	sub $sp, $sp, $pr0
	
	; pointer to the string
	*set $pr0, 0
	add $pr0, $gp, $pr0
	store $pr0, $sp, 8, 16
	
	; push the arguments count
	set $pr0, 1
	store $pr0, $sp, 8, 8
	
	; return addr
	set $pr0, 2
	add $pr0, $pc, $pr0
	store $pr0, $sp, 8, 0
	
	call printf
	
	; remove the parameters from the stack and printf's return value
	set $pr0, 28
	add $sp, $sp, $pr0
	
	; return
	load $pr0, $sp, 8, 0
	jr $pr0
