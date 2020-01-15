#I have commented this file for my basic understanding of make.
# don't indent the comment as it leads to shell to think of it as command to print.
# or use '@' to silence it if one still want to indent it
#To silence the make file use make -s

dir_1 := src
dir_2 := obj
dir_3 := helpers
dir_4 := exe
main = ./exe/main

.PHONY: all $(dir_1) $(dir_2) $(dir_3)
#phony basically tells make which targets are not actually files, 
#such files such as clean,all,directories are called phony files.
all: $(dir_1) LINK RUN
# the order in which these are written, GNU make happens to update them from left to right.
$(dir_1):
	$(MAKE) --directory=$@ $(TARGET)
#--directory says to go into the directory before call the sub-make
# $@ means name of the target

#command to link the objet files. '\' used for break a long command

LINK: $(dir_2) $(dir_4) 
	gcc ./obj/main.o -o ./exe/main
	gcc ./obj/p1.o -o ./exe/main1
	gcc ./obj/p2.o -o ./exe/main2
	gcc ./obj/p3.o -o ./exe/main3
	gcc ./obj/p4.o -o ./exe/main4
	gcc ./obj/p5.o -o ./exe/main5
	gcc ./obj/p6.o -o ./exe/main6

.PHONY: RUN clean no_stats last_modified install
# specific commands

RUN: 
	@echo ".............\nRunning final exectuables\n............." 
	@$(main)


clean:
	@echo "All exe and obj cleared" 
	@rm -f ./obj/* ./exe/*
	@#@ is used to silence the make command/comment

no_stats:
	@make -s

last_modified:
	@echo "last modified $(NUM) files are =>"
	@find . -type f -printf '%T@ %p\n' | sort -k1,1nr | head -$(NUM)

# %T@ with -printf predicate of find will get last modification, %p will print the file names
# sort -k1,1nr will reverse numerically sort
# head -$(NUM) will get us the last modified $(NUM) file names
