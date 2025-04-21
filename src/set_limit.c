#include "conf.h"

#include <stdio.h>

#define ANSI_BOLD "\033[1m"
#define ANSI_RED "\033[31m"
#define ANSI_CLEAR "\033[0m"

int main(int argc, const char* argv[]) {

    if (read_conf()) {
        printf("%s%s[ERROR]%s Failed to read config file from %s\n", ANSI_RED, ANSI_BOLD, ANSI_CLEAR, CONFIG_FILE_PATH);
        return 1;
    }

    if (load_mixer()) {
        printf("%s%s[ERROR]%s Failed to load mixer\n", ANSI_RED, ANSI_BOLD, ANSI_CLEAR, CONFIG_FILE_PATH);
        return 1;
    }

    printf("Please set your system volume to your desired maximum value.\n");
    printf("%sEnsure that playback of any audio which you do not want to play at that volume is stopped.%s\n", ANSI_BOLD, ANSI_CLEAR);
    printf("Press enter when ready.\n");
    getchar();

    long vol;
    snd_mixer_selem_get_playback_volume(mixer_elem, SND_MIXER_SCHN_MONO, &vol);
    max_vol = (int)vol;

    if (write_conf()) {
        printf("%s%s[ERROR]%s Failed to write config file to %s\n", ANSI_RED, ANSI_BOLD, ANSI_CLEAR, CONFIG_FILE_PATH);
        printf("If you are trying to configure the volume limit, ensure you use sudo.\n");
        return 1;
    }

    printf("Volume limit has been set to (raw value) %s%d%s\n", ANSI_BOLD, max_vol, ANSI_CLEAR);
    printf("Restart the alsa-volume-limiter service for this change to take effect.\n");

}