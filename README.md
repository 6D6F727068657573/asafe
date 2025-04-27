# ASafe

Make system upgrades more robust by automatically checking the arch announce mailing list for manual interventions. ASafe is light weight and comes with minimal dependencies.

## How does it work?

ASafe installs a pacman hook to the /etc/pacman.d/hook directory that triggers an automatic check for recent announcements before every installation or upgrade. If an unhandled announdement is found asafe will abort the installation and print a list of all recent announcments. That check can be run manually using the *asafe check* command. To mark all resent issues as resolved run *asafe mark-resolved*. This will ignore all announcements up to that point in time.

ASafe can also be disabled or set to a complain mode in order to not interfere with installs or upgrades. The latter emulates the behavior of the enforce mode but without interfering with the installation process.

## Requirements

ASafe requires only libcurl to work.

## Caveats

If a different directory for the pacmans hooks is used (i.e. by making changes to /etc/pacman.conf) the asafe hook needs to be moved accordingly. Pacman runs it's hooks in alphabetic order. It is therefore crucial that the 00-asafe.hook file does not get renamed. Doing so might interrupt a kernel update before initramfs and vmlinuz files are written to /boot.

Depening on the installation method it is recommended to run *asafe mark-resolved* after installing ASafe. This will set the intial state and make ASafe work right away. Otherwise the state is set `after` the first installation or system upgrade.

## Installation

Compile the source using `cmake`: Just run `make`, `make test` and `make install` in the repository directory.

## Changing Permissions

You can change the permissions of the files in the in /usr/share/asafe to allow various users to run asafe.
