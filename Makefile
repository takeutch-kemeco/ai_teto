SRCS = main.c IO_LINUX.c PAD.c BLOCK.c PANEL.c MINO.c GEN_MINO.c AI.c TETO.c
OBJS = $(SRCS:.c=.o)
PROG = ai_teto
LIBS = -lc -lpthread

BIN = /usr/local/bin

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(DEFS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f $(PROG)

install:
	cp $(PROG) $(BIN)

uninstall:
	rm $(BIN)/$(PROG)
