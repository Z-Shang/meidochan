all:
	gcc -o meidochan meidochan.c `pkg-config --cflags --libs gtk+-2.0` -I/usr/include/lua5.2 -llua5.2
