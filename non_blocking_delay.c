#include "non_blocking_delay.h"

DelayTimerCtrl non_blocking_delay_dtc;

//移植时去除 开始
DelayTimer * DT0_AdiA2bI2cInit;
DelayTimer * DT1_AdiA2bI2cInit;
DelayTimer * DT2_AdiA2bI2cInit;
DelayTimer * DT3_AdiA2bI2cInit;
//结束

void non_blocking_delay_init(){
	non_blocking_delay_dtc.id =0;
	int i;
	for(i=0;i<AUDIO_DT_MAX;i++){
		non_blocking_delay_dtc.dt[i].delay_time = 0;
		non_blocking_delay_dtc.dt[i].flags = 0;
		non_blocking_delay_dtc.dt[i].timeout = 0;
	}
	
	//移植时去除 开始
	DT0_AdiA2bI2cInit = non_blocking_delay_timer_register(&non_blocking_delay_dtc);
	DT1_AdiA2bI2cInit = non_blocking_delay_timer_register(&non_blocking_delay_dtc);
	DT2_AdiA2bI2cInit = non_blocking_delay_timer_register(&non_blocking_delay_dtc);
	DT3_AdiA2bI2cInit = non_blocking_delay_timer_register(&non_blocking_delay_dtc);	
	//结束
}

void non_blocking_delay_timers_service(DelayTimerCtrl *dtc)
{
	int i;
 	for(i=0;i< dtc->id ;i++){
		if((dtc->dt[i].flags & 0x01) ==  TIMER_FLAGS_ALLOC){
			if(dtc->dt[i].delay_time-- == 0){
				dtc->dt[i].timeout = 1;
				dtc->dt[i].flags &=  ~0x01;
			}
		}
	}	
}

DelayTimer* non_blocking_delay_timer_register(DelayTimerCtrl *dtc)
{
	int ind = dtc->id;
	dtc->id++;
	
	if(ind < AUDIO_DT_MAX){
		return &(dtc->dt[ind]);
	}else{
		printf("%s create timer failed!!!!!!\n", __func__);
		return NULL;
	}
}

int non_blocking_delay(DelayTimer* dt, uint32_t delay_time)
{
	if((dt->timeout == 0) && (dt->flags == TIMER_FLAGS_DISABLE))
	{	
		dt->delay_time = delay_time;
		dt->flags |= TIMER_FLAGS_ALLOC;
	}
	return dt->flags;
}

void non_blocking_delay_timer_reset(DelayTimer* dt)
{
	dt->flags = TIMER_FLAGS_DISABLE;
	dt->delay_time =0;
	dt->timeout = 0;
}
