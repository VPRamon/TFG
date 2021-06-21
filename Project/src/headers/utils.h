/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: oem
 *
 * Created on May 6, 2021, 5:37 PM
 */

#ifndef UTILS_H
#define UTILS_H

void system_cmd2(char *input, char **output, int size);
char *system_cmd(char *input, int chunk_size);
int valid_input(char input, int max);
char *parse_release(char *release);

#endif /* UTILS_H */

