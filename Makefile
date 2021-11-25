CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
EX_CFLAG = -no-pie

OBJ_DIR = ref
MY_DIR = Tu

OBJECTS = $(OBJ_DIR)/kex.o 	$(OBJ_DIR)/kem.o     $(OBJ_DIR)/indcpa.o \
	  $(OBJ_DIR)/polyvec.o  $(OBJ_DIR)/poly.o    $(OBJ_DIR)/ntt.o \
	  $(OBJ_DIR)/cbd.o 	$(OBJ_DIR)/reduce.o  $(OBJ_DIR)/verify.o \
	  $(OBJ_DIR)/fips202.o  $(OBJ_DIR)/symmetric-shake.o \
	  $(OBJ_DIR)/randombytes.o

HEADERS = $(OBJ_DIR)/params.h   $(OBJ_DIR)/kex.h       $(OBJ_DIR)/kem.h \
	  $(OBJ_DIR)/indcpa.h   $(OBJ_DIR)/polyvec.h   $(OBJ_DIR)/poly.h \
	  $(OBJ_DIR)/ntt.h      $(OBJ_DIR)/cbd.h       $(OBJ_DIR)/reduce.c \
	  $(OBJ_DIR)/verify.h   $(OBJ_DIR)/symmetric.h $(OBJ_DIR)/fips202.h \

#test_kyber512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kyber.c randombytes.c $(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_kyber.c -o test_kyber512S

ENCAPS_OBJ = $(MY_DIR)/api_encaps.o
DECAPS_OBJ = $(MY_DIR)/api_decaps.o
KEYGEN_OBJ = $(MY_DIR)/api_keygen.o
VERIFY_OBJ = $(MY_DIR)/verify.o

ENCAPS = encaps
DECAPS = decaps
KEYGEN = keygen
VERIFY = verify

all: encaps decaps keygen

encaps: $(ENCAPS)

$(ENCAPS): $(OBJECTS) $(ENCAPS_OBJ)
	$(CC) $(CFLAGS) $(EX_CFLAGS) -o $@ $^

decaps: $(DECAPS)

$(DECAPS): $(OBJECTS) $(DECAPS_OBJ)
	$(CC) $(CFLAGS) $(EX_CFLAGS) -o $@ $^

keygen: $(KEYGEN)

$(KEYGEN): $(OBJECTS) $(KEYGEN_OBJ)
	$(CC) $(CFLAGS) $(EX_CFLAGS) -o $@ $^


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJECTS) $(ENCAPS_OBJ) $(DECAPS_OBJ) $(KEYGEN_OBJ) 
