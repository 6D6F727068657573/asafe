# ASafe

Make system upgrades more robust by automatically checking the arch announce mailing list for manual interventions. ASafe is light weight and comes with minimal dependencies.

## Getting Started

ASafe queries the arch linux website for manual interventions before each install or upgrade. If a new manual intervention is found the install or upgrade will get aborted and pacman will print a message similar to:

[INSERT MESSAGE].

You can also read the message again by running:

```
asafe check
```

To mark the issue as resolved and continue installing or upgrading, run 

```
asafe mark-resolved
```

This will ignore all messages up to the time the command was run and allow pacman to continue normally.

You can also set ASafe to a complain mode or disable it temporary using the asafe set-mode command.

## Requirements

ASafe is made for arch linux using libcurl. Make sure the pacman logs (usually located in /var/log/pacman.log) have the default timestamps like '[2020-20-07T12:28:13+0100] [ALPM] ...'.

The pacman hook is installed to /etc/pacman.d/hooks. If a different directory is configured that hook needs to be moved manually.

## Installation

Install from the AUR or download and compile the source using `cmake`, `make`, `make test` and `make install`.
