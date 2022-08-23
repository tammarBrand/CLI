#include "../headers/gas_cam_cli.h"

gazapi_t *p_gaz;//gas library functions object
void* handle;//gas library stages object

void init_gas_cam_cli(){
    void* libHandle= dlopen("/home/tammar/sambashare/build-gas_cammera-Desktop-Debug/libgas_cammera.so.1.0.0",RTLD_LAZY);
    assert(libHandle);
    p_gaz = (gazapi_t*)dlsym(libHandle,"p_gaz_api");
    handle=p_gaz->create_gas_handler();

}
void  free_gas_cam_cli(){

    p_gaz->free_handler(handle);
}
void status_app(){
    pthread_t controller;
    int* status=p_gaz->get_status(handle);

   // pthread_create(&controller,NULL,contoller_fun,(void*)status);
   // p_gaz->start_record(handle);
   // sleep(5);
    p_gaz->do_snapshot(handle);
    sleep(60);
   // p_gaz->stop_record(handle);
   // pthread_join(controller,NULL);
}


//client gas_csam functions
int start_record_cli(int n,char** params){
    if(n!=0){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    /*send client request...*/
    p_gaz->start_record(handle);
    return 1;
}
int stop_record_cli(int n,char** params){
    if(n!=0){
        printf("error not fiten number of arguments\n");
        return 0;
    }

    p_gaz->stop_record(handle);
    return 1;
}
int do_snapshot_cli(int n,char** params){
    if(n!=0){
        printf("error not fiten number of arguments\n");
        return 0;
    }
    p_gaz->do_snapshot(handle);
    return 1;
}
int* get_status(){
    return p_gaz->get_status(handle);

}
