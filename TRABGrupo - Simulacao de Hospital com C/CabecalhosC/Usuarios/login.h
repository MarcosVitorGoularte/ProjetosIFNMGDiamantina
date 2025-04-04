#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

typedef struct {
char usuario[20];
char senha[10];
} login;

int VerificarLogin();

void CadastrarNovoUsuario();

#endif // LOGIN_H_INCLUDED
