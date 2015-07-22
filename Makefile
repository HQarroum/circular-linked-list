CC ?= gcc

LIB_NAME ?= circular-linked-list

# Shared library extension
LIB_SHARED_EXT = .so

# Static library extension
LIB_STATIC_EXT = .a

# Shared library output name
LIB_SHARED_NAME = lib$(LIB_NAME)$(LIB_SHARED_EXT)

# Static library output name
LIB_STATIC_NAME = lib$(LIB_NAME)$(LIB_STATIC_EXT)

SRC = linked-list.c

CFLAGS ?= -std=c99 -W -Wall -Werror

LDFLAGS ?= -shared

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(OBJ)
	ar -rcs $(LIB_STATIC_NAME) $^
	$(CC) $(LDFLAGS) -o $(LIB_SHARED_NAME) $^ 

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(LIB_SHARED_NAME) $(LIB_STATIC_NAME)

.PHONY: clean fclean re