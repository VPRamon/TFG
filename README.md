# TFG
## _Hacking Linux, Kernel Exploitation_

This framework aims to automate the process of exploiting the Linux Kernel, as well as to provide the user with the necessary tools to scan the target and consult already existing exploits.

The project started is not intended as a definitive version, but as a constantly evolving Framework subject to new kernel versions and security features as they emerge. For the time being, it is an open source prototype, with the hope that both those who are most proficient in the area of cyber security, as well as novices who want to enter the world of exploitation, can use the software freely and contribute to its development.

## Features

- Information Gathering
- Module Fuzzing
- Consult exploits
- Create/edit new exploits
 

## Tech

Some of the tools currently being used are:

- [SearchSploit](https://www.exploit-db.com/searchsploit) - Local Exploit-db Database
- [QEMU](https://www.qemu.org/) - Virtual Machine for target fuzzing simulator
- [KASAN](https://www.kernel.org/doc/html/v4.14/dev-tools/kasan.html) - Kernel Address Sanitizer for bug detection

## Installation

It is required [SearachSploit](https://www.exploit-db.com/searchsploit) to query any exploit.
```sh
sudo apt update && sudo apt -y install exploitdb
```

To install the Framework just run the INSTALL.sh file in the 'Project' directory.

```sh
bash TFG/Project/INSTALL.sh
```

Or do the manual compilation...

```sh
cd TFG/Project/src/
make clean
make

cd ../fuzzer_ssh/fuzzer
make
```

then just run the Framework at 'TFG/Project/bin directory'


## Documentation
read the full documentation at the root [documentation.pdf](https://github.com/VPRamon/TFG/blob/main/documentation.pdf)

## Contact
For any doubt or reporting bug, you can contact me by email: vallespuigramon@gmail.com
