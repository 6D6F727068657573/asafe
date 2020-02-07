# ASafe

Make system upgrades more robust by automatically checking the arch announce mailing list for manual interventions. ASafe is light weight and comes with minimal dependencies.

## Getting Started

ASafe creates a pacman hook that queries the arch linux website for manual interventions before each upgrade. By default upgrades are not executed if there is a new announcement since the last system upgrade. To prevent this behavior ASafe can be set to a complain mode or disabled by running:

```
asafe set-mode complain
```
or
```
asafe set-mode disabled
```
respectively. To manually check for recent announcements run 
```
asafe check
```
.

## Requirements

ASafe is made for arch linux using libcurl. Make sure the pacman logs (usually located in /var/log/pacman.log) have the default timestamps like '[2020-20-07T12:28:13+0100] [ALPM] ...'.

## Installation

Install from the AUR or download and compile the source using `cmake`, `make`, `make test` and `make install`.
