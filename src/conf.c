#include "conf.h"

int max_vol = 100;
const char* device_name = 0;
const char* channel_name = 0;

snd_mixer_t* mixer = 0;
snd_mixer_elem_t* mixer_elem = 0;
snd_mixer_selem_id_t* mixer_elem_sid = 0;

#define MAX_VOL_KEY "max_volume"
#define DEVICE_NAME_KEY "device_name"
#define CHANNEL_NAME_KEY "channel_name"

int read_conf() {

    config_t config;
    config_init(&config);

    int success = 0;

    do {
        if (config_read_file(&config, CONFIG_FILE_PATH) == CONFIG_FALSE) break;
        if (config_lookup_int(&config, MAX_VOL_KEY, &max_vol) == CONFIG_FALSE) break;
        if (config_lookup_string(&config, DEVICE_NAME_KEY, &device_name) == CONFIG_FALSE) break;
        if (config_lookup_string(&config, CHANNEL_NAME_KEY, &channel_name) == CONFIG_FALSE) break;
        success = 1;
    } while (0);

    if (!success) {
        fprintf(stderr, "Failed to read config file: %s\n", config_error_text(&config));
        config_destroy(&config);
        return 1;
    }

    return 0;

}

int write_conf() {

    config_t config;
    config_init(&config);

    config_setting_t* root = config_root_setting(&config);

    int success = 0;

    do {

        config_setting_t* s;

        if ((s = config_setting_add(root, MAX_VOL_KEY, CONFIG_TYPE_INT)) == CONFIG_FALSE) break;
        config_setting_set_int(s, max_vol);

        if ((s = config_setting_add(root, DEVICE_NAME_KEY, CONFIG_TYPE_STRING)) == CONFIG_FALSE) break;
        config_setting_set_string(s, device_name);

        if ((s = config_setting_add(root, CHANNEL_NAME_KEY, CONFIG_TYPE_STRING)) == CONFIG_FALSE) break;
        config_setting_set_string(s, channel_name);

        if (config_write_file(&config, CONFIG_FILE_PATH) == CONFIG_FALSE) break;

        success = 1;

    } while (0);

    if (!success) {
        fprintf(stderr, "Failed to write config file: %s\n", config_error_text(&config));
        config_destroy(&config);
        return 1;
    }

    return 0;
}

int load_mixer() {

    if (snd_mixer_open(&mixer, 0)) {
        fprintf(stderr, "Failed to open mixer\n");
        return 1;
    }

    if (snd_mixer_attach(mixer, device_name)) {
        fprintf(stderr, "Failed to get attach hctl to mixer\n");
        return 1;
    }

    if (snd_mixer_selem_register(mixer, 0, 0)) {
        fprintf(stderr, "Failed to register mixer selem\n");
        return 1;
    }

    if (snd_mixer_load(mixer)) {
        fprintf(stderr, "Failed to load mixer elems\n");
        return 1;
    }

    if (snd_mixer_selem_id_malloc(&mixer_elem_sid)) {
        fprintf(stderr, "Failed to allocate mixer s-elem-id\n");
        return 1;
    }

    snd_mixer_selem_id_set_index(mixer_elem_sid, 0);
    snd_mixer_selem_id_set_name(mixer_elem_sid, channel_name);

    mixer_elem = snd_mixer_find_selem(mixer, mixer_elem_sid);

    if (!mixer_elem) {
        fprintf(stderr, "Failed to find mixer elem\n");
        return 1;
    }

    return 0;

}

int free_mixer() {

    snd_mixer_close(mixer);
    snd_mixer_selem_id_free(mixer_elem_sid);
    
}