SHELL=cmd
CC=c51 # Need Added to Path
COMPORT = $(shell type COMPORT.inc)
OBJS=main.obj JDY40.obj

main.hex: $(OBJS)
	$(CC) $(OBJS)
	@del *.asm *.lst *.lkr 2> nul
	@echo Done!

main.obj: main.c JDY40.h
	$(CC) -c main.c

JDY40.obj: JDY40.c JDY40.h
	$(CC) -c JDY40.c

clean:
	@del $(OBJS) *.asm *.lkr *.lst *.map *.hex *.map 2> nul

LoadFlash:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	EFM8_prog.exe -ft230 -r main.hex
	cmd /c start putty -serial $(COMPORT) -sercfg 115200,8,n,1,N

putty:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	cmd /c start putty -serial $(COMPORT) -sercfg 115200,8,n,1,N

Dummy: main.hex main.Map
	@echo Nothing to see here!

explorer:
	cmd /c start explorer .