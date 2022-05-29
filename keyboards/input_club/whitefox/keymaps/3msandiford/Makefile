# Makefile for the smallest possible zip interpreter I could make
CC = gcc

OPTIMIZE = -std=c99 -Os -Wall -Wextra -Wno-unused-parameter -Werror -g
CFLAGS = $(OPTIMIZE)

# -------------------------------------------------------------------
# YOU SHOULD NOT NEED TO MODIFY BELOW HERE
# -------------------------------------------------------------------

INC = ztypes.h jzip.h

OBJS = jzip.o control.o extern.o fakefileio.o input.o interpre.o \
	math.o memory.o object.o operand.o osdepend.o property.o \
	screen.o text.o variable.o minio.o platform.o

all  : jzip

jzip : $(OBJS) ztypes.h jzip.h
	$(CC) -o $@ $(CFLAGS) $(OBJS)

clean :
	-rm -f *.o

realclean :
	-rm -f *.o jzip

DATE = `date +%m%d%Y`
FULLDATE = `date '+%a, %b %d %Y'`
stamp:
	-echo "#define JZIPVER \"Jzip V2.1\"" > ./jzip.h
	-echo "#define JZIPRELDATE \"$(FULLDATE)\"" >> ./jzip.h
archive:
	-tar cvf jzip21-$(DATE).tar *.[c,h] *.txt *.1 *.mak Makefile > /dev/null 2>&1
	-gzip --force jzip21-$(DATE).tar
