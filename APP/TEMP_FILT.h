

#ifndef TEMP_FILT_H_
#define TEMP_FILT_H_

void TEMP_FilterInit(void);

void TEMP_FilterRunnable(void);     //low execution time 

u16 TEMP_FilterGetter(void);       //no time 

#endif /* TEMP_FILT_H_ */