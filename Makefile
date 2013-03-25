all:
	gcc -o meidochan meidochan.c `pkg-config --cflags --libs gtk+-2.0`
