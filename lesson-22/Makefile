.PHONY: compile_run copy_file

# USAGE: make comile_run FILE=tac.c ARGS="foo bar"
compile_run:
	cc $(FILE) -O2 -Wall -W && ./a.out $(if $(ARGS),$(ARGS))
copy_file:
	cat $(FILE) | pbcopy
