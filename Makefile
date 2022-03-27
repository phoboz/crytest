include Makefile.config

PROJECT=crytest
SRCC=main.c
SRCS=data.s
SRCH=
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)
DATA=original.png hl.png
EXTRAS=original.cry hl.cry
RMVLIBS=display.o interrupt.o sound.o rmvlib.a

include Makefile.example

original.cry: original.png
	$(CONVERTER) --binary -cry --overwrite $<

hl.cry: hl.png
	$(CONVERTER) --binary -cry --overwrite $<

data.s: original.cry hl.cry
