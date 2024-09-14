#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-w
CFLAGS+=-O2

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -r $(NOM) $(OBJ) 2>/dev/null
	@ranlib $(NOM)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.m
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all
