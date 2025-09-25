# A simple Apple I emulator made in C
## Download 
```bash
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
### CPU test mode
If you want to run [Klaus Dormann's 6502 functional tests](https://github.com/Klaus2m5/6502_65C02_functional_tests), run this:
```bash
$ ./apple1 -t
```
### Log mode
If you want to run the emulator in log mode, run this instead:
```bash
$ ./apple1 -l
```
If you are in test or log mode, the log will be saved to `log.txt` file.

---

## Apple BASIC 
To run Apple BASIC, type this into the ROM monitor:
```
E000R
```

### Resources I recommend
- [pagetable.com](https://www.pagetable.com/c64ref/6502/?tab=2)
- [masswerk.at](https://www.masswerk.at/6502/6502_instruction_set.html)
- [The Apple 1 manual](https://mirrors.apple2.org.za/ftp.apple.asimov.net/documentation/apple1/apple1manual_alt.pdf)
