#include <QCoreApplication>
#include <dlfcn.h>
#include "gas_cam.h"
#include <unistd.h>
#include <signal.h>
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

void handle_sigint(int signal){
    printf("--going to stop--\n");
    sleep(1);
    exit(1);

}

int main(int argc, char *argv[])
{
    void* libHandle= dlopen("/home/tammar/sambashare/build-gas_cam-Desktop-Debug/libgas_cam.so.1.0.0",RTLD_LAZY);

    assert(libHandle);
    gazapi_t *p_gaz;
    p_gaz = (gazapi_t*)dlsym(libHandle,"p_gaz_api");
    void* handle=p_gaz->init();

    p_gaz->start_record(handle);

    if(signal(SIGINT, handle_sigint)==SIG_ERR)
        printf("error\n");
    raise(SIGINT);
   p_gaz->do_snapshot(handle);

    while(1){
        sleep(20);
    }

   //getCommandAndActive();

    p_gaz->stop_record(handle);
    p_gaz->free_all(handle);
    exit(1);

}

