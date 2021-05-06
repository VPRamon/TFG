/* 
 * File:   display.h
 * Author: VPRamon
 *
 * Created on May 5, 2021, 7:32 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "infgath.h"

#define SYS_INFO 0
#define FUZZER 1
#define DEBUGGER 2
#define EXPLOIT 3

void display_sys_info(struct sys_inf *system_info);
void display_network_info();
void display_device(struct device dev);
void display_devices(list *devices);

#endif /* DISPLAY_H */

