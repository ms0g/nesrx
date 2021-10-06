#pragma once

#include "rom.hpp"

class PRGRom: public Rom {
public:
    PRGRom(): Rom() {}

    void loadRom(std::string filename) override {
        Rom::loadRom(filename);
        std::cout << "16KB PRG-ROM Banks: " << +prg_bank_size << std::endl;
        ext_rom.resize(PRG_ROM_SIZE * prg_bank_size);
        romfile.seekg(INES_HEADER_SIZE);
        if (!romfile.read(reinterpret_cast<char*>(ext_rom.data()), PRG_ROM_SIZE * prg_bank_size)) {
            std::cerr << "Reading PRG-ROM file failed." << std::endl;
            err = true;
        }

    }
    PRGRom(const PRGRom&) = delete;
    PRGRom& operator=(const PRGRom&) = delete;
    
};