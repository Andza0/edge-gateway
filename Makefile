SRC_DIR=./src
SRCS=$(SRC_DIR)/main.c $(SRC_DIR)/parse.c

build:
	gcc $(SRCS) -o edge-gateway -Wall -Werror -pedantic

clean:
	rm -f edge-gateway

all: clean build