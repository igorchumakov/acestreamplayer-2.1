Ace Stream Player
-----------------

Tested with VLC version **2.1.4**

**Cross compile for Windows:**

Reqiured:

mingw-w64 gcc-mingw-w64-i686 g++-mingw-w64-i686 mingw-w64-tools lua5.1 libtool automake autoconf autopoint make gettext pkg-config qt4-dev-tools

`./bootstrap.sh`

`./configure.sh` or `./configure.sh ts` for torrentstream

`cd build-ace` or `cd build-ts` for torrentstream

`make`

`make install package-win-strip`

Known problems:

*Error: "Failed to download contribs"* - [download] contribs manually and put into vlc-{version}/contrib folder.

[download]:https://bitbucket.org/AceStream/acestreamplayer/downloads/i686-w64-mingw32.tar.gz