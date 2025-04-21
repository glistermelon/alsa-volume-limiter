tar --exclude='alsa-volume-limiter/.vscode' --exclude='alsa-volume-limiter/releases' -cf alsa-volume-limiter.tar alsa-volume-limiter
mv alsa-volume-limiter.tar alsa-volume-limiter/releases/0.1.0/alsa-volume-limiter-0.1.0.tar
cd alsa-volume-limiter/releases/0.1.0
tar -xf alsa-volume-limiter-0.1.0.tar
sha256sum alsa-volume-limiter-0.1.0.tar