#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PCM_BUF_LENGTH 1024
#define TRUE 1
#define FALSE 0

typedef struct {
	int sec;
	int sample_rate;
	int num_samples;
	float *buffer; 
	float offset;
	float gain;
} s_OBJ;

int init(s_OBJ* obj) 
{
	srand(time(NULL));
	obj->sec = 10; 
	obj->sample_rate = 44100; 
	obj->num_samples = (obj->sec) * (obj->sample_rate); 
	obj->gain = 0.5;
#if 0
	printf("%d\n", obj->num_samples); 
#endif
	obj->buffer = (float*)calloc(sizeof(float), obj->num_samples); 
	if (obj->buffer == NULL) { return FALSE; } 
	else { return TRUE; }
}

void create(s_OBJ* obj) 
{
	float a = 0.0f; 
	float b = 0.0f; 
	for (size_t i = 0; i < obj->num_samples; ++i) { 
#if 1
		a = sqrt(-2.0f * log(rand() / (double)RAND_MAX));
		b = sinf(2.0f * M_PI * (rand() / (double)RAND_MAX));
		obj->buffer[i] = obj->gain * a * b;
		printf("a = %5.5f, b = %5.5f\n", a, b); 
#elif 0
		obj->buffer[i] = obj->gain * sinf(2.0f * M_PI * (rand() / (double)RAND_MAX));
#endif
	} 
}

void output(FILE* fp, s_OBJ* obj) 
{
	for (size_t i = 0; i < obj->num_samples; ++i) { 
		fprintf(fp, "%5.5f\n", obj->buffer[i]); 
#if 0
		printf("buf[%zu] = %5.5f\n", i, obj->buffer[i]); 
#endif
	} 
}

int main(void) 
{
	FILE* fp;
	fp = fopen("./data.txt", "w"); 
	if (fp == NULL) { return 0; }

	s_OBJ obj;
	if (init(&obj) == FALSE) { return 0; }
	create(&obj); 
	output(fp, &obj);

	fclose(fp); 

	free(obj.buffer);
	
	return 0;
}
