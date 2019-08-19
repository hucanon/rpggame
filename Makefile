NAME	= rpg
DATA	= data
SRCS	= srcs/launcher.c srcs/menus.c srcs/rpg.c srcs/gameplay.c srcs/fts.c srcs/sauvegardes.c srcs/affichage.c srcs/map00.c
OBJS	= ${SRCS:.c=.o}
HEADER	= includes/
RM		= rm -f
RMF		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I ${HEADER}

${NAME}	:	${OBJS}
		 	${CC} ${CFLAGS} -o ${NAME} ${OBJS}
			@mkdir data
			@echo "20/20\n7\n3\n4\n4\n1\n0\n3" > fiche_Chrom.rpg
			@echo "12/12\n2\n12\n1\n3\n2\n0\n3" > fiche_Rizel.rpg
			@echo "22/22\n10\n1\n2\n3\n1\n0\n3" > fiche_Uldur.rpg
			@mv *.rpg data/
			@echo "\n\nBonne chance\n"

all 	:	${NAME}

clean	: 
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

reset	:	fclean
			${RMF} ${DATA}

re		:	reset all

.PHONY :	all fclean clean re
