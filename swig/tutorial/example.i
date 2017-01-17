%module example
%{
/* Put header files here or function declarations like below */
extern double my_variable;
extern int fact(int n);
extern int my_mod(int x, int y);
extern char *get_time();
%}

extern double my_variable;
extern int fact(int n);
extern int my_mod(int x, int y);
extern char *get_time();
