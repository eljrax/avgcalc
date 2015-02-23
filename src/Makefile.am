AM_CFLAGS = --pedantic -Wall -O2  --std=c89
AM_LDFLAGS = -lm $(LIBINTL)
avgcalc_LDADD = -lm $(LIBINTL)
LDADD = -lm $(LIBINTL)

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# # the previous manual Makefile
bin_PROGRAMS = avgcalc
avgcalc_SOURCES = mode.c sort.c main.c main.h parse_args.c init.c output.c getline.c nls.c
DEFS=-DLOCALEDIR=\"$(localedir)\"
