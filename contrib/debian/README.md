
Debian
====================
This directory contains files used to package odexd/odex-qt
for Debian-based Linux systems. If you compile odexd/odex-qt yourself, there are some useful files here.

## odex: URI support ##


odex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install odex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your odexqt binary to `/usr/bin`
and the `../../share/pixmaps/odex128.png` to `/usr/share/pixmaps`

odex-qt.protocol (KDE)

