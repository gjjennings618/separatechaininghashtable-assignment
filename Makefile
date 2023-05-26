hash: hashmain.cc htable.cc
	g++ -Wall -Wextra -pedantic -o hash hashmain.cc htable.cc

clean: 
	rm -f hash