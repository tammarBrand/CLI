#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "gas_cam.h"
#include <math.h>
#define LENGTH 5

typedef struct func1_params
{
    int x;
    int y;
}func1_params;

typedef union funcs_params{
    void* handle;
    func1_params func1;
}funcs_params;
typedef int (*genericFunc_cli)(int num,char**,funcs_params*);
typedef int (*genericFunc)(funcs_params*);
typedef struct func{
    char* name;
    genericFunc_cli func_cli;
    genericFunc func;
    char* help;
    struct func* next;
}Func;

typedef struct list{
    Func*head;
    Func* tail;
}List;

void func1(funcs_params* p);
void func2(funcs_params* funcs);
void func3(funcs_params* funcs);


int start_record_cli(int n,char** params,funcs_params* funcs);
int stop_record_cli(int n,char** params,funcs_params* funcs);
int func1_cli(int n,char**,funcs_params*);
int func2_cli(int n,char**,funcs_params*);
int func3_cli(int n,char**,funcs_params*);

List* createList();
void freeList(List*);
void init(List* list);
void insert(List*list, char*name,genericFunc_cli func_cli,genericFunc func,char* help);
int getParams(char* cmd, char** params);
Func* getFunc(List*list,char*name);
void getCommandAndActive();
int isInt(char*);

#endif // FUNCTIONS_H
