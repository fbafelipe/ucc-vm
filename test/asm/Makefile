ASM=../link

all: test1.vm test2.vm

%.vm: %.asm
	$(ASM) $@ $<

clean:
	rm -f *.vm
