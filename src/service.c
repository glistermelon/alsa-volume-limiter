#include "conf.h"

void clamp_volume(snd_mixer_t *mixer, snd_mixer_elem_t *elem) {

    long vol;
    snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &vol);
    long max_vol_l = (long)max_vol;
    if (vol > max_vol_l) snd_mixer_selem_set_playback_volume(elem, SND_MIXER_SCHN_MONO, max_vol_l);

}

int main() {

    struct pollfd fds[1];
    int nfds = snd_mixer_poll_descriptors(mixer, fds, 1);

    if (nfds <= 0) {
        fprintf(stderr, "Failed to get poll descriptor\n");
        return 1;
    }

    while (1) {
        int poll_ret = poll(fds, nfds, -1);
        if (poll_ret > 0) {
            snd_mixer_handle_events(mixer);
            clamp_volume(mixer, mixer_elem);
        } else break;
    }

    perror("poll");
    free_mixer();
    return 1;

}