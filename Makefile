# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mougnou <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 10:27:14 by mougnou           #+#    #+#              #
#    Updated: 2020/10/24 17:44:39 by mougnou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c
OBJ = *.o


GL = mlx_opengl
AK = AppKit
OGL = OpenGL

all:
	gcc $(SRC) -Wall -Werror -Wextra -o cub3D -L $(GL) -lmlx  -framework $(OGL) -framework $(AK)
clean:
	rm -rf *.o
fclean: clean
	rm ./cub3D
	rm *.gch
