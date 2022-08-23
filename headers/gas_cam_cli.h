#ifndef GAS_CAM_CLI_H
#define GAS_CAM_CLI_H
#include <stdio.h>
#include <assert.h>
#include <dlfcn.h>
#include "gas_cammera.h"
#include "controller.h"


void init_gas_cam_cli();
void  free_gas_cam_cli();
void status_app();
int start_record_cli(int n,char** params);
int stop_record_cli(int n,char** params);
int do_snapshot_cli(int n,char** params);
int* get_status();

#endif // GAS_CAM_CLI_H
