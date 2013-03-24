all:
	gcc -o meidochan meidochan.c `pkg-config --cflags --tags gtk+-2.0`
