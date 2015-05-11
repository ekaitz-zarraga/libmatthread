VPATH		= src:include:lib:tests

CC		= gcc
CFLAGS		= -Wall -g

INCLUDE		= include
OBJDIR		= build

TARGETS		= 		# Add more standalones
OBJECTS		= $(addprefix $(OBJDIR)/, )

LIBS		= libmatthread.so	# Library for custom shit
LIB_OBJECTS 	= $(addprefix $(OBJDIR)/, octaveIO.o convolution.o )

TESTS       = convoluciona
TEST_OBJECTS    = $(addprefix $(OBJDIR)/, convoluciona.o)

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

$(TESTS): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJECTS) $(LIBS) -I$(INCLUDE)

$(TEST_OBJECTS): $(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDE)


.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGETS) $(LIBS) $(TESTS)
