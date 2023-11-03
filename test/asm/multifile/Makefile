ASM=../../link
CFLAGS=

all: test.vm

test.vm: main.asm foo.asm bar.asm
	$(ASM) test.vm main.asm foo.asm bar.asm

clean:
	rm -f *.vm
