
#include "Kalman_Filter.h"

#define SAMPLE_SIZE 250

void Kalman_init(KalmanFilter* kf, float q, float r, float initial_value) 
{
    kf->q = q;
    kf->r = r;
    kf->x = initial_value;
    kf->p = 1.0f;
    kf->k = 0.0f;
}

float Kalman_update(KalmanFilter* kf, float measurement) 
{
    kf->p += kf->q;
    kf->k = kf->p / (kf->p + kf->r);
    kf->x += kf->k * (measurement - kf->x);
    kf->p *= (1.0f - kf->k);
    return kf->x;
}

float compute_mean(float* data, int n) 
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

float compute_variance(float* data, int n, float mean) 
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        float diff = data[i] - mean;
        sum += diff * diff;
    }
    return sum / (n - 1);
}

void kalman_filter_init_with_sample(KalmanFilter* kf)
{
	/*
	ON_LED_SAMPLE_KALMAN;

    float sample_data_accel[SAMPLE_SIZE]; 
	float accel_bias = 0.0f, r = 0.0f, q = 0.0f;

	for(int i = 0; i < SAMPLE_SIZE; i++) {
		// Read sample
		sample_data_accel[i] = ;
		delayUs(1000);
	}
	 
	accel_bias = compute_mean(sample_data_accel, SAMPLE_SIZE);
	r = compute_variance(sample_data_accel, SAMPLE_SIZE, accel_bias);
	q = r * 0.01f;
	Kalman_init(&kf, q, r, 0.0f); 
	OFF_LED_SAMPLE_KALMAN;
	*/
}

