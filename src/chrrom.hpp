#pragma once

#include "rom.hpp"

#define CHR_ROM_SIZE 0x2000

class CHRRom: public Rom {
public:
    CHRRom(): Rom() {}

    void loadRom(std::string filename) override {
        Rom::loadRom(filename);
        m_chr_bank_size = m_header[5];
        if (!m_chr_bank_size) {
            std::cerr << "No CHR ROM" << std::endl;
            m_err = true;
        }
        std::cout << "8KB CHR-ROM Banks: " << +m_chr_bank_size << std::endl;
        m_ext_rom.resize(CHR_ROM_SIZE * m_chr_bank_size);
        m_romfile.seekg(INES_HEADER_SIZE + m_prg_bank_size * PRG_ROM_SIZE);
        if (!m_romfile.read(reinterpret_cast<char*>(m_ext_rom.data()), CHR_ROM_SIZE * m_chr_bank_size)) {
            std::cerr << "Reading CHR-ROM file failed." << std::endl;
            m_err = true;
        }

    }

    CHRRom(const CHRRom&) = delete;
    CHRRom& operator=(const CHRRom&) = delete;
private:
    uint8_t m_chr_bank_size;
    
};