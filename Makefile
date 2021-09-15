FILESVR = server.c

FILECLT = client.c

CFLAGS = -Wall -Wextra -Werror

SFLAGS = -D_POSIX_C_SOURCE=199309L

NAMESVR = server

NAMECLT = client

all: $(NAMESVR) $(NAMECLT)

$(NAMESVR): $(FILESVR)
	gcc $(CFLAGS) $(FILESVR) $(SFLAGS) -o $(NAMESVR)

$(NAMECLT): $(FILECLT)
	gcc $(CFLAGS) $(FILECLT) -o $(NAMECLT)

clean:
	rm $(NAMESVR) $(NAMECLT)

fclean: clean

bonus: all

norma:
	norminette $(FILECLT) $(FILESVR)

re: clean all
