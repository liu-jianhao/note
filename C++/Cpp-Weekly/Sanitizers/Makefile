address:
	g++ address.cpp -Wall -Werror -fsanitize=address

memory:
	clang++ memory.cpp -Wall -Wextra -fsanitize=memory

run:
	MSAN_SYMBOLIZER_PATH=/usr/lib/llvm-4.0/bin/llvm-symbolizer ./a.out

clean:
	rm a.out