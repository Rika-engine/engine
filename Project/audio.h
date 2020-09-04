#pragma once
#pragma once

#include <AL/alc.h>
#include <AL/al.h>
#include <iostream>
using namespace std;
#include <vector>
struct Suono {
	ALuint source;
	const char* name;
	ALuint buffer;
};
vector <Suono> suoni;
ALCdevice* device; ALCcontext* context;

void init() {
	device = alcOpenDevice(NULL);
	if (!device) {
		printf("unable to open default device\n");

	}
	if (alGetError() != AL_NO_ERROR) {
		printf("errore %d", alGetError());
	}
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		printf("errore ");
	}
}
void caricawav(const char* path, float* distanza, const char* soprannome, bool loop) {



	char z[90];
	strcpy(z, "C:\\Users\\moon1\\Desktop\\ogl\\per le mappe\\suoni\\");
	strcat(z, path); printf(" %s  ", z);
	unsigned char* h = 0;
	FILE* f;
	if (f = fopen(z, "rb")) {
		Suono suono;
		suono.name = soprannome;
		int a = 0;
		unsigned char* wave = (unsigned char*)malloc(4 * sizeof(unsigned char));;
		fread(wave, 1, 4, f);
		printf("AUDACE %c", wave[0]);
		if (strcmp((const char*)wave, "RIFF")) {
			h = (unsigned char*)malloc(78 * sizeof(unsigned char));
			fseek(f, 0, SEEK_SET);

			fread(h, 1, 78, f); printf("AUDIO11  ");

			unsigned char chunk;
			unsigned int lenghtfile;
			unsigned short channels;

			short type;
			unsigned int samples;//Hz
			unsigned int samples8;//Hz
			unsigned int sampleinbit;//Hz in bit
			unsigned int monostereo;//Hz
			unsigned short bitpersamples;//Hz
			unsigned int datachunk;//Hz
			unsigned int datasize = 0;//Hz
			char* data = 0;

			fseek(f, 44, SEEK_SET);
			fseek(f, 0, SEEK_END);
			a = ftell(f);
			fseek(f, 78, SEEK_SET);

			datasize = *(unsigned int*)&h[74];
			data = (char*)malloc(datasize * sizeof(char));
			//	data = new char[datasize];
			fread(data, 1, datasize, f);
			type = *(short*)&h[22];
			lenghtfile = *(unsigned int*)&h[16];
			samples = *(unsigned int*)&h[24];
			channels = *(unsigned short*)&h[20];
			bitpersamples = *(unsigned short*)&h[34];
			samples8 = (bitpersamples * samples * channels) / 8;
			monostereo = (channels * bitpersamples) / 8.1;
			chunk = h[73];


			//	wave=(char*)&h[0];
			//	if((wave[0]=='R')&& (wave[1] == 'I')&& (wave[2] == 'F')){ printf("AUDIO3 %s", wave); }


		/*	ALCdevice* device=alcOpenDevice(NULL);
			if (!device) {
				printf( "unable to open default device\n");

			}
			if ( alGetError() != AL_NO_ERROR) {
				printf("errore %d", alGetError());
			}
			ALCcontext *context=alcCreateContext(device,NULL);
			if (!alcMakeContextCurrent(context)) {
				printf("errore " );
			}
			*/
			alListenerf(AL_GAIN, 1);
			alListener3f(AL_POSITION, 0, 0, 0);
			static short b = 1;
			ALuint buffer = 0, source = 0;
			ALenum formato = 0, errore = 0;

			if (channels == 1) {
				if (bitpersamples == 8) {
					formato = AL_FORMAT_MONO8;
				}
			} if (channels == 2) {
				if (bitpersamples == 8) {
					formato = AL_FORMAT_STEREO8;
				}
			} if (channels == 1) {
				if (bitpersamples == 16) {
					formato = AL_FORMAT_MONO16;
				}
			} if (channels == 2) {
				if (bitpersamples == 16) {
					formato = AL_FORMAT_STEREO16;
				}
			}

			printf("tag %c \ncanali: %d \nsamples: %d \n bitpersamples : %d\nformatO: %d\n datasize: %d", chunk, channels, samples, bitpersamples, formato, datasize);
			alGenBuffers(1, &buffer);	printf("AUDIO3 %d", buffer);

			printf("AUDIO3 S %d", b);
			alBufferData(buffer, formato, data, datasize, samples);


			alGenSources(1, &source); suono.source = source;
			suoni.push_back(suono);
			if (errore = alGetError() != AL_NO_ERROR) {
				printf("errore %d", errore);
			}
			float velocity[] = { 0,0,0 };
			float* position = distanza;//serve a farlo sembrare lontano,si potrebbe anche chiamarlo distanza
			printf("AUDIO3 data[0] %c", data[0]);
			data = 0;
			alSourcei(source, AL_BUFFER, buffer);
			alSourcefv(source, AL_POSITION, position);
			alSourcei(source, AL_LOOPING, loop);
			alSourcefv(source, AL_VELOCITY, velocity);
			alSourcef(source, AL_GAIN, 1.0f);//volume multipl
			alSourcef(source, AL_PITCH, 2.0f);//intonazione,cambiano i toni piu 

			alSourcePlay(source);
			ALint stato = AL_PLAYING;
			/*while (stato = AL_PLAYING) {
				alGetSourcei(source, AL_SOURCE_STATE,&stato );
			}*/
			b++;

		}
	}
}
void updatinglistenerpos(float x, float y, float z) {

}

void stopmusic(const char* nome) {
	for (int i = 0; i < suoni.size(); i++) {
		if (strcmp(nome, suoni[i].name) == 0) { alSourceStop(suoni[i].source); }

	}

}
void resumemusic(const char* nome) {
	for (int i = 0; i < suoni.size(); i++) {
		if (strcmp(nome, suoni[i].name) == 0) { alSourcePlay(suoni[i].source); }

	}

}
