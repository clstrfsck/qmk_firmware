ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

testmap:	testmap.c keymap.c
	gcc -O -o testmap -I../../../../quantum -I../../../../tmk_core/common -I../../../../quantum/audio -I../../../../quantum/process_keycode -I../.. testmap.c keymap.c
