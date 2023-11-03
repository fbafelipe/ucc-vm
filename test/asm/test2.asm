; counting assembly test

.DATA
{
	"%d\n"
}

.TEXT

main:
	set $pr0, 1
	
	; loop begin
	
	; allocate space in the stack
	set $pr1, 28
	sub $sp, $sp, $pr1
	
	; set the int value
	store $pr0, $sp, 4, 24
	
	; store the address of the string
	copy $pr1, $gp
	store $pr1, $sp, 8, 16
	
	; store the argument count
	set $pr1, 1
	store $pr1, $sp, 8, 8
	
	; store the return address
	set $pr1, 2
	add $pr1, $pc, $pr1
	store $pr1, $sp, 8, 0
	
	call printf
	
	; clean the stack
	set $pr1, 28
	add $sp, $sp, $pr1
	
	; ++$pr0
	set $pr1, 1
	add $pr0, $pr0, $pr1
	
	; if ($pr0 < 10)
	set $pr1, 11
	less $pr1, $pr0, $pr1
	brch $pr1, -18
	
	halt
