SHELL=cmd
CC=c51 --model-large # Need Added to Path
COMPORT = $(shell type COMPORT.inc)
OBJS=main.obj JDY40.obj global.obj movement_integration.obj inductance.obj speaker.obj

main.hex: $(OBJS)
	$(CC) $(OBJS)
	@del *.asm *.lst *.lkr 2> nul
	@echo Done!

main.obj: main.c JDY40.h
	$(CC) -c main.c
global.obj: global.c global.h
	$(CC) -c global.c

JDY40.obj: JDY40.c JDY40.h inductance.h
	$(CC) -c JDY40.c

movement_integration.obj: movement_integration.c movement_integration.h
	$(CC) -c movement_integration.c

inductance.obj: inductance.c inductance.h
	$(CC) -c inductance.c

speaker.obj: speaker.c speaker.h
	$(CC) -c speaker.c

clean:
	@del $(OBJS) *.asm *.lkr *.lst *.map *.hex *.map 2> nul

LoadFlash:
	@taskkill /im putty.exe /F 2>NUL | wait 500
	..\EFM8_prog\EFM8_prog.exe -ft230 -r main.hex
	cmd /c start putty -serial $(COMPORT) -sercfg 115200,8,n,1,N

putty:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	@cmd /c start putty -serial $(COMPORT) -sercfg 115200,8,n,1,N

Dummy: main.hex main.Map
	@echo Nothing to see here!

explorer:
	cmd /c start explorer .