#ifndef SHRMEM_H_INCLUDED
#define SHRMEM_H_INCLUDED

int buf_init();
int buf_destroy();
int buf_put(char c);
int buf_get(char *c);

#endif
