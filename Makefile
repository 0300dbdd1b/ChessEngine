SRCDIR		=	./srcs/
INCDIR		=	./includes/
SRCNAME		= 	Pieces.cpp		\
				Board.cpp		\
				Game.cpp		\
				main.cpp		\


SRCS		= 	${addprefix ${SRCDIR}, ${SRCNAME}}

OBJS		= 	${SRCS:.cpp=.o}

CC			= 	g++ 
CFLAGS 		=	-std=c++11 -Wall -Wextra 



DEFINES     =   -D PIECES='" PRNBQKprnbqk"'

CXXFLAGS	= ${CFLAGS} ${DEFINES}

.cpp.o        :	${SRCS}
				${CC} ${CXXFLAGS} -c -I ${INCDIR} $< -o ${<:.cpp=.o}


NAME		= 	chess

$(NAME) 	: 	${OBJS} 
				$(CC) $(CXXFLAGS) -o $(NAME) -I $(INCDIR) $(OBJS) 



all:		${NAME}					## Cree la base de la Bibliotheque Statique "libft.a

clean:								## Supprime tout les .o inclus dans la bibliotheque "libft.a
			rm -f ${OBJS}


fclean:								## Supprime la Bibliotheque Statique et ses fichiers objet
			rm -f ${OBJS} 
			rm -f ${NAME}


re:			fclean all   			## Supprime et recompile la Bibliotheque Statique avec ses fichiers objets

x:			all clean

help:								## Liste toutes les commandes
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'


.PHONY	= 	all clean fclean re x
