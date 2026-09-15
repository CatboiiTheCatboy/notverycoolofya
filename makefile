build:
	cc ./main.c h/fileAccess.h h/graphicsBank.h h/utils.h res/options.h -o main -lX11 -lXpm -lXext
