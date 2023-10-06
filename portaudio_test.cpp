#include "portaudio/include/portaudio.h"
#include "stdio.h"

typedef struct
{
    float left_phase;
    float right_phase;
}   
paTestData;

static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData; 
    float *in = (float*)inputBuffer;
    unsigned int i;
    (void) outputBuffer; /* Prevent unused variable warning. */
    
    float max = 0;
    for( i=0; i<framesPerBuffer; i++ )
    {
        max = in[i] > max ? in[i] : max;
    }
    if(max > 0.1) {
        printf("max: %f\n", max);
    }
    return 0;
}

int main() {
    PaError err;
    err = Pa_Initialize();
    if( err != paNoError ) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    };
    PaStream *stream;
    err = Pa_OpenDefaultStream(
        &stream,
        2, // no input channels
        2, // stereo output
        paFloat32, // 32 bit floating point output
        44100, // sample rate
        256, // frames per buffer
        patestCallback, // callback function
        NULL // no user data
    );
    err = Pa_StartStream(stream);
    if( err != paNoError ) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    };
    Pa_Sleep(10000);
    Pa_Terminate();
    return 0;
}
