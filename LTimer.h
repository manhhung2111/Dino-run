#ifndef L_TIMER_H_
#define L_TIMER_H_

class LTimer
{
public:
    //Initialize
    LTimer();

    //Actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

    void gameOver();

private:
    //The clock time when the timer started
    int mStartTicks;

    //The ticks stored when the timer was paused
    int mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};




#endif // L_TIMER_H_
