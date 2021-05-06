/* 
 * File:   display.h
 * Author: VPRamon
 *
 * Created on May 5, 2021, 7:32 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "infgath.h"

#define MENU_OPTIONS 7
#define EXIT_MENU -1
#define INVALID_INPUT -2

#define SYS_INFO 0
#define NET_INFO 1
#define RUNNING_MODULES 2
#define RUNNING_DEVICES 3
#define FUZZER 4
#define DEBUGGER 5
#define EXPLOIT 6



void display_sys_info(struct sys_inf *system_info);
void display_network_info();
void display_device(struct device dev);
void display_devices(list *devices);

#endif /* DISPLAY_H */

