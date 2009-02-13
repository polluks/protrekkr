// ------------------------------------------------------
// Protrekkr
// Written by Franck Charlet
// Based on the work of Juan Antonio Arguelles Rius 
// ------------------------------------------------------

#ifndef _TIMER_H_
#define _TIMER_H_

// ------------------------------------------------------
// Class
class PtkTimer
{
    public:

        PtkTimer();

        void Set_Frames_Counter(void);
        float Get_Frames_Delay(void);
    
    private:
        float Ref_Ticks;
};

#endif
