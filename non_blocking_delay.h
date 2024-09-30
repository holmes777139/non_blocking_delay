#ifndef _NON_BLOCKING_DELAY_H_
#define _NON_BLOCKING_DELAY_H_

#include <stdio.h>
#include "r_cg_macrodriver.h"
#define AUDIO_DT_MAX 32
#define TIMER_FLAGS_DISABLE 0
#define TIMER_FLAGS_ALLOC 	1
#define TIMER_FLAGS_USING 	2

typedef struct{
	int id;
	int delay_time;
	int timeout;
	int flags;
}DelayTimer;

typedef struct __DelayTimerCtrl{
	int id;
	DelayTimer dt[AUDIO_DT_MAX];
}DelayTimerCtrl;

extern DelayTimerCtrl non_blocking_delay_dtc;

//移植时去除 开始
extern DelayTimer * DT0_AdiA2bI2cInit;
extern DelayTimer * DT1_AdiA2bI2cInit;
extern DelayTimer * DT2_AdiA2bI2cInit;
extern DelayTimer * DT3_AdiA2bI2cInit;
//end

#define FSM_GET()   (__LINE__ - 1);
#define FSM_SET(bp)   fsm_state= bp; return;
#define FSM_RESET()   fsm_state = 0; return;
#define FSM_START()  static int fsm_state = 0; switch(fsm_state) { case 0:
#define FSM_NEXT()   fsm_state = __LINE__; return; case __LINE__:
#define FSM_STOP()   fsm_state = 0; return;}

#define NON_BLOCKING_DELAY_VOID(dt, ms)  do {  							\
    if(non_blocking_delay(dt, ms) == 1) {                       				\
        return;                                                 				\
    }else{                                                           				\
	non_blocking_delay_timer_reset(dt);		                       			\
    }												\
} while(0)


#define NON_BLOCKING_RESET_VOID(dt)  do {                 					\
    non_blocking_delay_timer_reset(dt);                       					\
} while(0)

void non_blocking_delay_init(); 
void non_blocking_delay_timers_service(DelayTimerCtrl *dtc);
DelayTimer* non_blocking_delay_timer_register(DelayTimerCtrl *dtc);
int non_blocking_delay(DelayTimer* dt, uint32_t delay_time);
void non_blocking_delay_timer_reset(DelayTimer* dt);
#endif
