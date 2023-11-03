.TEXT

main:
	; for (i = 0; i < 10; ++i)
	set $pr7, 0 ; i = 0
	
	; i < 10
_main_begin_loop:
	set $pr6, 10
	less $pr6, $pr7, $pr6
	brch $pr6, 1
	call _main_end_loop
	
	; save the context
	set $pr0, 8
	sub $sp, $sp, $pr0
	store $pr7, $sp, 8, 0
	
	; grow the stack
	set $pr0, 16
	sub $sp, $sp, $pr0
	
	; push the arguments count
	set $pr0, 0
	store $pr0, $sp, 8, 8
	
	; return addr
	set $pr0, 2
	add $pr0, $pc, $pr0
	store $pr0, $sp, 8, 0
	
	call foo
	
	; remove the parameters from the stack
	set $pr0, 16
	add $sp, $sp, $pr0
	
	; restore the context
	load $pr7, $sp, 8, 0
	set $pr0, 8
	add $sp, $sp, $pr0
	
	; ++i
	set $pr6, 1
	add $pr7, $pr7, $pr6
	
	call _main_begin_loop
	
_main_end_loop:
	
	; return
	load $pr0, $sp, 8, 0
	jr $pr0
