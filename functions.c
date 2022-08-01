#include "functions.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include <unistd.h>
#include "functions.h"
#include <signal.h>

#define N 20
#define P_LENGTH 100



//global variables
void* libHandle;
gazapi_t *p_gaz;//gas library functions object
void* handle;//gas library stages object


List* createList(){
    List* list=(List*)malloc(sizeof(List));
    if(list==NULL){
        printf("error mallocing\n");
        exit(0);
    }
    list->head=list->tail=NULL;
    return list;
}
/*
void handle_sigint(int signal){
    printf("--going to stop--\n");
    sleep(1);
    handler* my_handler=(handler*)handle;
    if(my_handler->is_record_on)
        p_gaz->stop_record((void*)my_handler);


}
*/

void init(List* list){

    libHandle= dlopen("/home/tammar/Desktop/git/build-gas_cam-Desktop-Debug/libgas_cam.so.1.0.0",RTLD_LAZY);
    assert(libHandle);
    p_gaz = (gazapi_t*)dlsym(libHandle,"p_gaz_api");
    insert(list,"func1",func1_cli,func1,"func1 does nothing \n function: func1 <int> <int>");
    insert(list,"func2",func2_cli,func2,"func2 does nothing function");
    insert(list,"func3",func3_cli,func3,"func3 does nothing function");
    insert(list,"start_record",start_record_cli,p_gaz->start_record,"start_record start recording degrees snapshots \n function: start_record");
    insert(list,"stop_record",stop_record_cli,p_gaz->stop_record,"stop_record stop recording degrees snapshots \n function: stop_record");

  /*  if(signal(SIGINT, handle_sigint)==SIG_ERR)
        printf("error\n");*/
}
void insert(List*list, char*name,genericFunc_cli func_cli,genericFunc func,char* help){
    Func* n=(Func*)malloc(sizeof(Func));
    if(n==NULL)
    {   printf("error mallocing\n");
        exit(0);
    }
    n->func_cli=func_cli;
    n->func=func;
    n->help=strdup(help);
    n->name=strdup(name);
    n->next=NULL;

    if(list->head==NULL){
        list->head=list->tail=n;
        return;
    }
    list->tail->next=n;
    list->tail=n;
}
void freeList(List*list){
    Func* f;
    while(list->head!=NULL){
        f=list->head;
        list->head=list->head->next;
        free(f->help);
        free(f->name);
        free(f);
    }
    free(list);
}
int getParams(char* cmd, char** params){

    int len=N, i=0;
    char* token;
    token=strtok(cmd," ");
    while(token!=NULL){
        if(!strcmp(token," ")){
            token=strtok(NULL," ");
            continue;
        }
        if(i==len){
            params=(char**)realloc(params,len*1.5);
            if(params==NULL){
                printf("error mallocing\n");
                exit(0);
            }
            len*=1.5;
        }
        params[i++]=strdup(token);
        token=strtok(NULL," ");
    }
    return i;
}
Func* getFunc(List* list,char* name){

    if(name==NULL)
        return NULL;
    Func* ptr=list->head;

    while(ptr!=NULL){

        char* tmp=ptr->name;
        if(!strcmp(tmp,name))
            return ptr;

        ptr=ptr->next;
    }
    return NULL;
}
void getCommandAndActive(){

    char cmd[N+P_LENGTH+1], **params;
    Func* function;
    int n=-1;

    List* list=createList();
    init(list);


    gets(cmd);

    while(strcmp(cmd,"end")){
        params=(char **)calloc(N,sizeof(char*));
        if(params==NULL){
            printf("error mallocing\n");
            exit(0);
        }
        n=getParams(cmd,params);
        if(!(function=getFunc(list,params[0]))){
            printf("no such a command\n");
        }
        else{
            if(params[1]&&!strcmp(params[1],"-help"))
            {
                puts(function->help);
            }
            else{
                funcs_params funcs;
                int ans=function->func_cli(n-1,params+1,&funcs);
                if(!ans){
                    printf("faild, help:");
                    puts(function->help);
                }
                else{
                    function->func(&funcs);
                }
            }
        }
        for(int i=0;i<n;i++)
            free(params[i]);
        free(params);
        gets(cmd);
    }
    freeList(list);

}


void func1(funcs_params* funcs){
    printf("int func1 x=%d, y=%d \n", funcs->func1.x,funcs->func1.y);
}
void func2(funcs_params* funcs){
    printf("func2\n");
}
void func3(funcs_params* funcs){
    printf("func3\n");
}

int start_record_cli(int n,char** params,funcs_params* funcs){
    if(n!=0){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    handle=p_gaz->init();
    return 1;
}
int stop_record_cli(int n,char** params,funcs_params* funcs){
    if(n!=0){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    p_gaz->free_all(handle);
    return 1;
}
int func1_cli(int n,char** params,funcs_params* funcs){
    if(n!=2){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    int x=0, y=0;
    if(isInt(params[0]))
        x=atoi(params[0]);
    else
    { printf("unexpected type\n");
        return 0;}
    if(isInt(params[1]))
        y=atoi(params[1]);
    else
    {
        printf("unexpected type\n");
        return 0;
    }

    func1_params p={
        .x=x,
        .y=y};//fitten srtuct
    funcs->func1=p;

    return 1;
}
int func2_cli(int n,char** params,funcs_params* funcs){printf("in func2_cli\n");}
int func3_cli(int n,char** params,funcs_params* funcs){printf("in func3_cli\n");}

int isInt(char* params){
    for(int i=0;i<strlen(params);i++){
        if(!isdigit(params[i]))
            return 0;
    }
    return 1;
}
