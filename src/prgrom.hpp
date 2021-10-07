#pragma once

#include "rom.hpp"

class PRGRom: public Rom {
public:
    PRGRom(): Rom() {}

    void loadRom(std::string filename) override {
        Rom::loadRom(filename);
        std::cout << "16KB PRG-ROM Banks: " << +m_prg_bank_size << std::endl;
        m_ext_rom.resize(PRG_ROM_SIZE * m_prg_bank_size);
        m_romfile.seekg(INES_HEADER_SIZE);
        if (!m_romfile.read(reinterpret_cast<char*>(m_ext_rom.data()), PRG_ROM_SIZE * m_prg_bank_size)) {
            std::cerr << "Reading PRG-ROM file failed." << std::endl;
            m_err = true;
        }

    }
    PRGRom(const PRGRom&) = delete;
    PRGRom& operator=(const PRGRom&) = delete;
    
};