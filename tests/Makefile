includes := -I../src/include/
sources := test.c $(wildcard ../src/**/*.c)
objs := $(sources:.c=.o)

all: make_obj

make_obj: $(sources)
	gcc test.c -c $(sources)

compile: $(objs)
	gcc $(objs) $(includes) -o nl_test

test: compile
	./nl_test


