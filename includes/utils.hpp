#ifndef __UTIL__
# define __UTIL__

# include <iostream>

typedef struct s_move
{
	const unsigned char *from;
	const unsigned char *to;

	operator int(){ return 0;}
}t_move;

char* substr(const char *src, int start, int stop);

#endif