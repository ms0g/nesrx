#pragma once

#include "rom.hpp"

#define CHR_ROM_SIZE 0x2000

class CHRRom: public Rom {
public:
    CHRRom(): Rom() {}

    void loadRom(std::string filename) override {
        Rom::loadRom(filename);
        chr_bank_size = header[5];
        if (!chr_bank_size) {
            std::cerr << "No CHR ROM" << std::endl;
            err = true;
        }
        std::cout << "8KB CHR-ROM Banks: " << +chr_bank_size << std::endl;
        ext_rom.resize(CHR_ROM_SIZE * chr_bank_size);
        romfile.seekg(INES_HEADER_SIZE + prg_bank_size * PRG_ROM_SIZE);
        if (!romfile.read(reinterpret_cast<char*>(ext_rom.data()), CHR_ROM_SIZE * chr_bank_size)) {
            std::cerr << "Reading CHR-ROM file failed." << std::endl;
            err = true;
        }

    }

    CHRRom(const CHRRom&) = delete;
    CHRRom& operator=(const CHRRom&) = delete;
private:
    uint8_t chr_bank_size;
    
};