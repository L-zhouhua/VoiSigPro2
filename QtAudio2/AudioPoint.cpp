#include "AudioPoint.h"


void AudioPoint::save(double *b, int n)
{
	int i;
	FILE *fp;
	//fp1 = fopen("short.dat", "w");
	fp = fopen("double.dat", "w");
	for (i = 0; i < n; i++)
	{
		//fprintf(fp1, "%d\n", (int)b1[i]);
		fprintf(fp, "%f\n", b[i]);
	}
	//fclose(fp1);
	fclose(fp);
}
SF_INFO AudioPoint::getAudioPoint()
{
	SF_INFO sf_info;
	SNDFILE *snd_file;
	double* buf;
	sf_info.format = 0;
	snd_file = sf_open("C:/Users/12860/Desktop/wav/1.wav", SFM_READ, &sf_info);
	printf("Sample Rate : %d\n", sf_info.samplerate);
	printf("Channels : %d\n", sf_info.channels);
	printf("Sections  : %d\n", sf_info.sections);
	printf("Frames   : %d\n", (int)sf_info.frames);

	buf = (double *)malloc(sf_info.frames * sizeof(double));
	sf_seek(snd_file, 0, SEEK_SET);
	sf_read_double(snd_file, buf, sf_info.frames);
	save(buf, sf_info.frames);
	//free(buf);
	sf_close(snd_file);
	return sf_info;
}
AudioPoint::AudioPoint()
{

}


AudioPoint::~AudioPoint()
{
}
