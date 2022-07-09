#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
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
    Rom() {
        m_romfile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    }

    virtual void loadRom(const std::string_view filename) {
        try {
            m_romfile.open(filename, std::ios::in | std::ios::binary);
            m_header.resize(INES_HEADER_SIZE);
            m_romfile.read(reinterpret_cast<char*>(m_header.data()), m_header.size());

            if (m_header[0] != MAGIC0 || m_header[1] != MAGIC1 || m_header[2] != MAGIC2 || m_header[3] != MAGIC3) {
                throw std::invalid_argument("Invalid NES rom file");
            }
            m_prg_bank_size = m_header[4];
            if (!m_prg_bank_size) {
                throw std::invalid_argument("No PRG ROM");
            }
        } catch (std::ifstream::failure& e) {
            std::cerr << "Exception opening/reading ROM file: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void setOutfile(std::string_view outfile) {
        m_outfile = outfile;
    }

    virtual ~Rom() {
        m_romfile.close();
    }

    void save() {
        std::ofstream ofile{m_outfile, std::ios::binary | std::ios::out};
        ofile.write(reinterpret_cast<char*>(m_extracted_rom.data()), m_extracted_rom.size());
        ofile.close();

    }

    Rom(const Rom&) = delete;

    Rom& operator=(const Rom&) = delete;

    std::ifstream m_romfile;
    std::vector<uint8_t> m_header;
    std::vector<uint8_t> m_extracted_rom;
    uint8_t m_prg_bank_size{};
private:
    std::string_view m_outfile;
};