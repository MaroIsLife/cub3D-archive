SRC = arg_check.c bitmap.c bitmap2.c cast.c cast2.c color.c colors2.c cub3d.c cub3d_utils.c errors.c errors2.c errors3.c file_read.c file_read2.c ft_atoi.c ft_calloc.c ft_memcpy.c ft_split.c  get_next_line.c get_next_line_utils.c init_texture.c keys.c map.c raycast.c raycast2.c reso.c sprite.c sprite_utils.c sprite2.c texture.c ft_strtrim2.c ft_putstr.c
OBJ = arg_check.o bitmap.o bitmap2.o cast.o cast2.o color.o colors2.o cub3d.o cub3d_utils.o errors.o errors2.o errors3.o file_read.o file_read2.o ft_atoi.o ft_calloc.o ft_memcpy.o ft_split.o  get_next_line.o get_next_line_utils.o init_texture.o keys.o map.o raycast.o raycast2.o reso.o Sprite.o sprite_utils.o sprite2.o texture.o ft_strtrim2.o ft_putstr.o

GL = mlx_opengl
AK = AppKit
OGL = OpenGL

all: cub3D

cub3D:
	gcc $(SRC) -o cub3D -L $(GL) -lmlx -framework $(OGL) -framework $(AK)
clean:
	rm -rf *.o
fclean: clean
	rm -f ./cub3D
re : fclean all
