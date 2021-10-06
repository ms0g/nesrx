#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#define MAGIC0 0x4E
#define MAGIC1 0x45
#define MAGIC2 0x53
#define MAGIC3 0x1A

#define INES_HEADER_SIZE 0x10
#define PRG_ROM_SIZE 0x4000

class Rom {
public:
    Rom():err(false) {}

    virtual void loadRom(std::string filename) {
        romfile.open(filename, std::ios::in | std::ios::binary);
        if (!romfile.is_open()) {
            std::cerr << "Could not open rom file " << filename << std::endl;
            err = true;
        }

        header.resize(INES_HEADER_SIZE);
        romfile.read(reinterpret_cast<char*>(header.data()), header.size());
            
        if (header[0] != MAGIC0 || header[1] != MAGIC1 || header[2] != MAGIC2 || header[3] != MAGIC3) {
            std::cerr << "Invalid NES rom file" << std::endl;
            err = true;
        }
        prg_bank_size = header[4];
        if (!prg_bank_size) {
            std::cerr << "No PRG ROM" << std::endl;
            err = true;
        }
    }

    void setOutfile(std::string outfilename) {
        outfname = std::move(outfilename);
    }
     
    ~Rom(){
        romfile.close();
    }

    void save(){
        if (!err) {
            std::ofstream ofile{outfname, std::ios::binary | std::ios::out};
            ofile.write(reinterpret_cast<char*>(ext_rom.data()), ext_rom.size());
            ofile.close();
        }   
    }

    Rom(const Rom&) = delete;
    Rom& operator=(const Rom&) = delete;

    std::ifstream romfile;
    std::vector<uint8_t> header;
    std::vector<uint8_t> ext_rom;
    uint8_t prg_bank_size;
    bool err;
private:
    std::string outfname;
};