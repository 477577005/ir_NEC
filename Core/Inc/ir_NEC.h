#ifndef  __ir_NEC_H
#define  __ir_NEC_H
#include "stdio.h"

void ir_recorded_data(unsigned int *falling_edge_time,unsigned int time_couter);
void ir_data_analysis( unsigned char *value,unsigned int *falling_edge_time);

#endif
