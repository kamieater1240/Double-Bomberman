#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "music.h"

struct AudioData {
	int type;
	MCIDEVICEID deviceID;
	BOOL isRepeatedly;
	char path[MAX_PATH];
};

// Audio
int openAudio(const char name[]) {
	char path[_MAX_PATH] = "Resources/";
	const char midExt[] = ".mid|.midi|.rmi";
	const char wavExt[] = ".wav|.wave";
	const char mp3Ext[] = ".mp3";
	char ext[_MAX_EXT];
	union {
		MCI_WAVE_OPEN_PARMSA	wop;
		MCI_OPEN_PARMSA			op;
	} mci;
	DWORD		cmd;
	AudioData	*data;

	data = (AudioData *)malloc(sizeof(AudioData));
	if (data == NULL) return 0;

	ZeroMemory(data, sizeof(*data));
	ZeroMemory(&mci, sizeof(mci));
	strcat_s(path, name);
	_splitpath_s(path, NULL, NULL, NULL, NULL, NULL, NULL, ext, _MAX_EXT);
	_strlwr_s(ext);
	cmd = MCI_OPEN_TYPE | MCI_OPEN_ELEMENT;

	if (strstr(midExt, ext)) {
		data->type = MCI_DEVTYPE_SEQUENCER;
		lstrcpynA(data->path, path, MAX_PATH);
		mci.op.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_SEQUENCER;
		mci.op.lpstrElementName = data->path;
		cmd |= MCI_OPEN_TYPE_ID;
	}
	else if (strstr(wavExt, ext)) {
		data->type = MCI_DEVTYPE_WAVEFORM_AUDIO;
		lstrcpynA(data->path, path, MAX_PATH);
		mci.wop.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		mci.op.lpstrElementName = data->path;
		cmd |= MCI_OPEN_TYPE_ID;
	}
	else if (strstr(mp3Ext, ext)) {
		data->type = MCI_DEVTYPE_DIGITAL_VIDEO;
		lstrcpynA(data->path, path, MAX_PATH);
		mci.op.lpstrDeviceType = "MPEGVideo";
		mci.op.lpstrElementName = data->path;
	}
	else {
		free(data);
		return 0;
	}

	if (mciSendCommandA(0, MCI_OPEN, cmd, (DWORD)&mci)) {
		free(data);
		return 0;
	}

	data->deviceID = mci.op.wDeviceID;
	return (int)data;
}

void playAudio(int audio, BOOL isRepeatedly) {
	AudioData *data;
	DWORD cmd;
	MCI_PLAY_PARMS mpp;

	if (!audio) return;

	data = (AudioData*)audio;
	if (!data->deviceID) return;

	data->isRepeatedly = isRepeatedly;
	ZeroMemory(&mpp, sizeof(mpp));
	cmd = 0;
	if (isRepeatedly) {
		if (data->type == MCI_DEVTYPE_DIGITAL_VIDEO) {
			cmd |= (MCI_FROM | MCI_DGV_PLAY_REPEAT);
			mpp.dwFrom = 0;
		}
	}
	mciSendCommand(data->deviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
	mciSendCommand(data->deviceID, MCI_PLAY, cmd, (DWORD)&mpp);
}

void stopAudio(int audio) {
	AudioData *data;
	
	if (!audio)
		return;

	data = (AudioData*)audio;

	if (!data->deviceID)
		return;
	data->isRepeatedly = 0;
	mciSendCommand(data->deviceID, MCI_STOP, MCI_WAIT, 0);
	mciSendCommand(data->deviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
}