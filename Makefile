CC          = gcc
AR          = ar
CFLAGS      = -O0 -Wall -Werror -Wextra -Wformat=2 -Wshadow -pedantic -Werror=vla

LIBS        = -lm -lpthread
INCLUDES    = -I$(CURDIR)/cmore

ROOT_DIR    = $(CURDIR)
SRC_DIR     = $(ROOT_DIR)/src
TESTS_DIR   = $(SRC_DIR)/tests

CMORE_OBJ_DIR   = $(ROOT_DIR)/obj
CMORE_SHOBJ_DIR = $(ROOT_DIR)/shobj
CMORE_TEST_OBJ_DIR = $(ROOT_DIR)/testobj

SRC         = $(wildcard $(SRC_DIR)/*.c)
TESTS_SRC   = $(wildcard $(TESTS_DIR)/*.c)

OBJ         = $(patsubst $(SRC_DIR)/%.c,$(CMORE_OBJ_DIR)/%.o,$(SRC))
SHOBJ       = $(patsubst $(SRC_DIR)/%.c,$(CMORE_SHOBJ_DIR)/%.o,$(SRC))
TESTS_OBJ   = $(patsubst $(TESTS_DIR)/%.c,$(CMORE_TEST_OBJ_DIR)/%.o,$(TESTS_SRC))

ifeq ($(CMORE_STATIC_LIB),)
CMORE_STATIC_LIB    = $(ROOT_DIR)/cmore.a
endif

ifeq ($(CMORE_STATIC_LIB),)
CMORE_SHARED_LIB    = $(ROOT_DIR)/cmore.so
endif

#$(info $(shell echo $(OBJ) ) )

all: utils $(CMORE_STATIC_LIB) $(CMORE_SHARED_LIB) tests

tests: $(OBJ) $(TESTS_OBJ)
	$(CC) -o $@ $^ $(INCLUDES) $(CFLAGS) $(LIBS)

$(CMORE_STATIC_LIB): $(OBJ)
	$(AR) rcs $@ $^

$(CMORE_SHARED_LIB): $(SHOBJ)
	$(CC) -shared -o $@ $^

.PHONY: utils
utils: $(OBJ)

$(CMORE_SHOBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS) -fPIC

$(CMORE_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS) $(LIBS)

$(CMORE_TEST_OBJ_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS)

.PHONY: clean
clean:
	rm -f -r $(CMORE_OBJ_DIR) $(CMORE_TEST_OBJ_DIR) $(CMORE_SHOBJ_DIR)
	rm -f $(CMORE_STATIC_LIB) $(CMORE_SHARED_LIB) tests

# Make the obj directory
$(shell mkdir -p $(CMORE_OBJ_DIR))
$(shell mkdir -p $(CMORE_TEST_OBJ_DIR))
$(shell mkdir -p $(CMORE_SHOBJ_DIR))