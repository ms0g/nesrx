# nesrx
A small tool to extract PRG/CHR rom from NES/Famicom rom file

### Prerequisites
+ [CMake](http://www.cmake.org "CMake project page") (>= 3.17)

### Building
```bash
cd build
./builder.sh
```

### Usage
```bash
➜  ~ ./nesrx -h
Usage:  nesrx [ -<flag> [<val>] | --<name> [<val>] ]... <rom file>

   -p, --prg-rom              PRG ROM
   -c, --chr-rom              CHR ROM
   -o  --outfile              Output rom file
   -h, --help                 display usage information and exit
   -v, --version              display version information and exit
   
➜  ~ ./nesrx -p -o code.prg 
```
