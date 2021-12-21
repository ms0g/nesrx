#pragma once

#include "rom.hpp"

class PRGRom: public Rom {
public:
    PRGRom(): Rom() {}

    void loadRom(std::string_view filename) override {
        try {
            Rom::loadRom(filename);
            std::cout << "16KB PRG-ROM Banks: " << m_prg_bank_size << std::endl;
            auto prg_rom_size = PRG_ROM_SIZE * m_prg_bank_size;
            m_extracted_rom.resize(prg_rom_size);
            m_romfile.seekg(INES_HEADER_SIZE);
            m_romfile.read(reinterpret_cast<char*>(m_extracted_rom.data()), prg_rom_size);
        }
        catch (std::ifstream::failure &e) {
            std::cerr << "Reading PRG-ROM file failed: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        } catch (std::exception &e) {
            exit(EXIT_FAILURE);
        }
    }
    PRGRom(const PRGRom&) = delete;
    PRGRom& operator=(const PRGRom&) = delete;
    
};