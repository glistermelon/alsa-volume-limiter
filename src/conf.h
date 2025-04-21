#ifndef CONF_H
#define CONF_H

#include <libconfig.h>
#include <alsa/asoundlib.h>

#define CONFIG_FILE_PATH "/etc/alsa-volume-limiter/config.conf"

extern int max_vol;
extern const char* device_name;
extern const char* channel_name;

extern snd_mixer_t* mixer;
extern snd_mixer_elem_t* mixer_elem;
extern snd_mixer_selem_id_t* mixer_elem_sid;

int read_conf();
int write_conf();

int load_mixer();
int free_mixer();

#endif