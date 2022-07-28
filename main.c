
#include "functions.h"


void main(int argc, char *argv[])
{
   /* void* libHandle= dlopen("/home/tammar/Desktop/git/build-gas_cam-Desktop-Debug/libgas_cam.so.1.0.0",RTLD_LAZY);

    assert(libHandle);
    gazapi_t *p_gaz;
    p_gaz = (gazapi_t*)dlsym(libHandle,"p_gaz_api");



    void* handle=p_gaz->init();
    p_gaz->start_record(handle);

    while(1){
        sleep(20);
    }
*/
   getCommandAndActive();
/*
    p_gaz->stop_record(handle);
    p_gaz->free_all(handle);*/

}

