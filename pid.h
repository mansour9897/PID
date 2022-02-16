#ifndef _pid_included_
#define _pid_included_

float kp, ki, kd;
float pid_setpoint;
float pid_maxout;
float pid_minout;
float pid_last_input;
float pid_output_sum;


float pid_compute(float input);
void pid_set_output_limits(float min, float max);
void pid_initialize(float sp, float P, float I, float D);

float pid_compute(float input)
{
    //return pid output
    float output;    
    float error = pid_setpoint - input;
    float dInput = (input - pid_last_input);

    pid_output_sum += (ki * error);

    if(pid_output_sum > pid_maxout ) pid_output_sum = pid_maxout;
    else if(pid_output_sum < pid_minout) pid_output_sum = pid_minout;

    output = kp * error + pid_output_sum - kd * dInput;

    if(output > pid_maxout) output = pid_maxout;
    else if(output < pid_minout) output = pid_minout;

    pid_last_input = input;
    
    return output;
}

void pid_set_output_limits(float min,float max)
{
    if(!(min < max)) return;

    pid_maxout = max;
    pid_minout = min;

    if(pid_output_sum > pid_maxout) pid_output_sum = pid_maxout;
    else if(pid_output_sum < pid_minout) pid_output_sum = pid_minout;

}

void pid_initialize(float sp, float P, float I, float D)
{
    pid_last_input = 0;
    pid_output_sum = 0;
    pid_setpoint = sp;
    kp = P;
    ki = I;
    kd = D;
}
#endif