cipher: cipher.o
	gcc cipher.o -o cipher
cipher.o: cipher.c

test: test1 test2
test1: 
	./cipher 1 5 SmallInital.txt Small.out
test2: 
	./cipher 1 7 LargeInital.txt Large.out

breaker:
	gcc CaesarCipherBreaker.c -o breaker

testing: test3 test4
test3:
	./breaker LetFreq.txt Small.out
test4:
	./breaker LetFreq.txt Large.out

dif: dif1 dif2
dif1:
	diff -s SmallInital.txt Small.out.txt
dif2:
	diff -s LargeInital.txt Large.out.txt
