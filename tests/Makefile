CC ?= g++

APP ?= launch_tests

SRC = main.cpp \
	unit_test_lifecycle.cpp \
	unit_test_lookup.cpp \
	unit_test_iteration.cpp \
	unit_test_insertion.cpp \
	unit_test_pop.cpp \
	unit_test_removal.cpp

CFLAGS ?= -W -Wall -Werror -ansi -pedantic

LDFLAGS ?= -lgtest -lpthread -L../ -lcircular-linked-list

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJ)
	$(CC) -o $(APP) $^ $(CFLAGS) $(LDFLAGS)

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(APP)

.PHONY: clean fclean re