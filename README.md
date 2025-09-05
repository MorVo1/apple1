# A simple Apple I emulator made in C
## Download 
```bash
$ cd
$ git clone https://github.com/morvo1/apple1
$ cd apple1
```

## Build
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make -j$(nproc)
```

## Run
```bash
$ ./apple1
```
To run wozbasic, type:
```
E000R
```

### Resources I recommend
- [pagetable.com](https://www.pagetable.com/c64ref/6502/?tab=2)
- [masswerk.at](https://www.masswerk.at/6502/6502_instruction_set.html)
- [The Apple 1 manual](https://mirrors.apple2.org.za/ftp.apple.asimov.net/documentation/apple1/apple1manual_alt.pdf)
