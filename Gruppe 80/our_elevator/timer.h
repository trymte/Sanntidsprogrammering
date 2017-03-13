#pragma once


void timer_start(double duration, unsigned int id);

void timer_stop(void);

int timer_timed_out(void);

unsigned int get_timer_id(void);

void set_timer_id(unsigned int id);

