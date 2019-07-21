#pragma once
#include<sndfile.h>
#include<stdlib.h>


class AudioPoint
{
public:
	AudioPoint();
	~AudioPoint();
	SF_INFO getAudioPoint();
private:
	void save(double *b, int n);
};
