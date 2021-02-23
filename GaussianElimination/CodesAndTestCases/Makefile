.PHONY: test run

TEST_SIZE=32
DIFF=diff --side-by-side --suppress-common-lines

test: gauss
	./gauss $(TEST_SIZE) 1 2> gauss.$(TEST_SIZE).out
	$(DIFF) gauss.$(TEST_SIZE).out gauss.$(TEST_SIZE).good

run: test
	@./gauss 512 1 2> gauss.512_1.out
	@$(DIFF) gauss.512_1.out gauss.512.good | head
	@./gauss 512 2 2> gauss.512_2.out
	@$(DIFF) gauss.512_2.out gauss.512.good | head
	@./gauss 512 4 2> gauss.512_4.out
	@$(DIFF) gauss.512_4.out gauss.512.good | head
	@./gauss 512 8 2> gauss.512_8.out
	@$(DIFF) gauss.512_8.out gauss.512.good | head
	@./gauss 1024 1 2> gauss.1024_1.out
	@$(DIFF) gauss.1024_1.out gauss.1024.good | head
	@./gauss 1024 2 2> gauss.1024_2.out
	@$(DIFF) gauss.1024_2.out gauss.1024.good | head
	@./gauss 1024 4 2> gauss.1024_4.out
	@$(DIFF) gauss.1024_4.out gauss.1024.good | head
	@./gauss 1024 8 2> gauss.1024_8.out
	@$(DIFF) gauss.1024_8.out gauss.1024.good | head

gauss: gauss.c
	gcc -o gauss gauss.c

clean:
	rm gauss *.out
