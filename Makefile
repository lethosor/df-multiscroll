DFHACKVER ?= 0.34.11
DFHACKREL ?= r5

DFMAJOR = `echo $(DFHACKVER) | sed s/\\\\.//g`

DF ?= /Users/vit/Desktop/df-r5
DH ?= /Users/vit/Downloads/dfhack-$(DFHACKREL)

SRC = multiscroll.mm
DEP = 

ifneq (,$(findstring 0.40,$(DFHACKVER)))
	EXT = dylib
else
	EXT = so
endif
OUT = dist/$(DFHACKVER)-$(DFHACKREL)/multiscroll.plug.$(EXT)

INC = -I"$(DH)/library/include" -I"$(DH)/library/proto" -I"$(DH)/depends/protobuf" -I"$(DH)/depends/lua/include"
LIB = -L"$(DH)/build/library" -ldfhack

CFLAGS = $(INC) -m32 -DLINUX_BUILD -O3
LDFLAGS = $(LIB) -shared 

ifeq ($(shell uname -s), Darwin)
	CXX = c++ -std=gnu++0x -stdlib=libstdc++
	CFLAGS += -Wno-tautological-compare
	LDFLAGS += -framework AppKit -mmacosx-version-min=10.6
else
endif


all: $(OUT)

$(OUT): $(SRC) $(DEP)
	-@mkdir -p `dirname $(OUT)`
	$(CXX) $(SRC) -o $(OUT) -DDFHACK_VERSION=\"$(DFHACKVER)-$(DFHACKREL)\" -DDFHACK_$(DFHACKREL) -DDF_$(DFMAJOR) $(CFLAGS) $(LDFLAGS)

inst: $(OUT)
	cp $(OUT) "$(DF)/hack/plugins/"

clean:
	-rm $(OUT)
