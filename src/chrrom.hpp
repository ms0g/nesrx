#pragma once

#include "rom.hpp"

#define CHR_ROM_SIZE 0x2000

class CHRRom: public Rom {
public:
    CHRRom(): Rom() {}

    void loadRom(const std::string_view& filename) override {
        try {
            Rom::loadRom(filename);
            m_chr_bank_size = m_header[5];
            if (!m_chr_bank_size) {
                throw std::invalid_argument("No CHR ROM");
            }
            std::cout << "8KB CHR-ROM Banks: " << m_chr_bank_size << std::endl;
            auto chr_rom_size = CHR_ROM_SIZE * m_chr_bank_size;
            m_extracted_rom.resize(chr_rom_size);
            m_romfile.seekg(INES_HEADER_SIZE + m_prg_bank_size * PRG_ROM_SIZE);
            m_romfile.read(reinterpret_cast<char *>(m_extracted_rom.data()), chr_rom_size);
        }
        catch (std::ifstream::failure &e) {
            std::cerr << "Reading CHR-ROM file failed: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    CHRRom(const CHRRom&) = delete;
    CHRRom& operator=(const CHRRom&) = delete;
private:
    uint8_t m_chr_bank_size;
    
};