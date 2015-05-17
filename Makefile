VPATH		= src:libmatthread:tests

CC		= gcc
CFLAGS		= -Wall -g

INCLUDE     = libmatthread
OBJDIR		= build

TARGETS		= 		# Add more standalones
OBJECTS		= $(addprefix $(OBJDIR)/, )

LIBS		= libmatthread.so	# Library for custom shit
LIB_OBJECTS 	= $(addprefix $(OBJDIR)/, common.o signals.o octaveIO.o matrices.o)

TESTS       = convoluciona join crazy_test multiply

all: $(TARGETS) $(LIBS)

$(TARGETS): $(LIBS) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS) -I$(INCLUDE)

$(OBJECTS): $(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDE)



$(LIBS): $(LIB_OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ $(LIB_OBJECTS)

$(LIB_OBJECTS): $(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -o $@ -c $< -I$(INCLUDE)



tests: $(LIBS) $(TESTS)

$(TESTS): %: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDE)


.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGETS) $(LIBS) $(TESTS)
