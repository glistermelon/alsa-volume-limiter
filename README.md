## Installation

### Arch

#### Precompiled

Attain a package file from Releases and run `sudo pacman -U [path to package file]`.

#### Manual

Attain `PKGBUILD` from Releases for use with `makepkg`.
Compile the package and install according to [Precompiled](#precompiled).

## Setup

#### Configuration

Some of `/etc/alsa-volume-limiter/config.conf` must be configured manually.

First, you must identify `device_name`. To use an hwid, check the content of `/proc/asound/cards` and identify your device. Set `device_name` to `"hw:[insert hwid here]"`.

For instance, in the following situation, to limit the volume of my headphones, I would use `device_name="hw:2"`.
```bash
$ cat /proc/asound/cards
 0 [PCH            ]: HDA-Intel - HDA Intel PCH
                      HDA Intel PCH at 0x4016220000 irq 197
 1 [NVidia         ]: HDA-Intel - HDA NVidia
                      HDA NVidia at 0x85080000 irq 17
 2 [Gam            ]: USB-Audio - CORSAIR VOID ELITE Wireless Gam
                      Corsair CORSAIR VOID ELITE Wireless Gam at usb-0000:00:14.0-6.2, full speed
 3 [Microphone     ]: USB-Audio - fifine Microphone
                      fifine Microphone at usb-0000:00:14.0-6.3, full speed
```

Secondly, you must identify `channel_name`. With the hwid from before, run `amixer -c [hwid]` and check each "mixer control."

For instance, continuing from the previous example, I would use `channel_name="PCM"`. If you have multiple listings and are unsure which to choose, try changing your volume and observe the `Mono:` line. As you can see, for `PCM` below, according to the line `Mono: Playback 33 [52%] [-31.00dB] [on]`, the volume of my headset is currently 33/52%/-31dB.

```bash
$ amixer -c 2
Simple mixer control 'PCM',0
  Capabilities: pvolume pvolume-joined pswitch pswitch-joined
  Playback channels: Mono
  Limits: Playback 0 - 64
  Mono: Playback 33 [52%] [-31.00dB] [on]
Simple mixer control 'Headset',0
  Capabilities: cvolume cvolume-joined cswitch cswitch-joined
  Capture channels: Mono
  Limits: Capture 0 - 64
  Mono: Capture 64 [100%] [0.00dB] [on]
```

#### Systemd

The `alsa-volume-limiter` service must be running.

#### Setting Maximum Volume

Run `alsa-volume-limiter-config`