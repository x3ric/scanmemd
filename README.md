<div align="center">

### Overview

The **ScanMem Daemon** provides a simple way to execute `scanmem` commands without requiring root privileges.

### Dependencies

This daemon relies on the `scanmem` tool for its functionality. Ensure that `scanmem` is installed on your system before using this daemon. You can install `scanmem` using your package manager or by downloading it from the official source.

### Installation

<pre>
git clone https://github.com/x3ric/scanmemd
cd scanmemd
make install
</pre>

### Usage

Once installed, follow these steps to use the daemon:

Echo your desired `scanmem` command into the daemon's input:

<pre>
echo "\"&lt;pid&gt;\" \"&lt;command&gt;\"" | $HOME/.cache/scanmem
</pre>

Retrieve the output of the executed command from the deamon:

<pre>
journalctl -u scanmemd.service -f | awk -F':' '{print $4}'
</pre>
   
</p><a href="https://archlinux.org"><img alt="Arch Linux" src="https://img.shields.io/badge/Arch_Linux-1793D1?style=for-the-badge&logo=arch-linux&logoColor=D9E0EE&color=000000&labelColor=97A4E2"/></a><br>
