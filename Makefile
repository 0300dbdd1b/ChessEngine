SRCDIR		=	./srcs/
INCDIR		=	./includes/
SRCNAME		= 	Pieces.cpp		\
				utils.cpp 		\
				Board.cpp		\
				main.cpp		\


SRCS		= 	${addprefix ${SRCDIR}, ${SRCNAME}}

OBJS		= 	${SRCS:.cpp=.o}

CC			= 	g++ 
CFLAGS 		=	-Wall  -Wextra

.cpp.o        :	${SRCS}
				${CC} ${CFLAGS} -c -I ${INCDIR} $< -o ${<:.cpp=.o}


NAME		= 	chess

$(NAME) 	: 	${OBJS} 
				$(CC) $(CFLAGS) -o $(NAME) -I $(INCDIR) $(OBJS) 



all:		${NAME}					## Cree la base de la Bibliotheque Statique "libft.a

clean:								## Supprime tout les .o inclus dans la bibliotheque "libft.a
			rm -f ${OBJS}


fclean:								## Supprime la Bibliotheque Statique et ses fichiers objet
			rm -f ${OBJS} 
			rm -f ${NAME}


re:			fclean all   			## Supprime et recompile la Bibliotheque Smaketatique avec ses fichiers objets

x:			all clean

help:								## Liste toutes les commandes
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'


.PHONY	= 	all clean fclean re x