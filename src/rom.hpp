#pragma once

#include <fstream>
#include <string>
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
    Rom():m_err(false) {}

    virtual void loadRom(std::string filename) {
        m_romfile.open(filename, std::ios::in | std::ios::binary);
        if (!m_romfile.is_open()) {
            std::cerr << "Could not open rom file " << filename << std::endl;
            m_err = true;
        }

        m_header.resize(INES_HEADER_SIZE);
        m_romfile.read(reinterpret_cast<char*>(m_header.data()), m_header.size());
            
        if (m_header[0] != MAGIC0 || m_header[1] != MAGIC1 || m_header[2] != MAGIC2 || m_header[3] != MAGIC3) {
            std::cerr << "Invalid NES rom file" << std::endl;
            m_err = true;
        }
        m_prg_bank_size = m_header[4];
        if (!m_prg_bank_size) {
            std::cerr << "No PRG ROM" << std::endl;
            m_err = true;
        }
    }

    void setOutfile(std::string outfilename) {
        m_outfname = std::move(outfilename);
    }
     
    virtual ~Rom(){
        m_romfile.close();
    }

    void save(){
        if (!m_err) {
            std::ofstream ofile{m_outfname, std::ios::binary | std::ios::out};
            ofile.write(reinterpret_cast<char*>(m_ext_rom.data()), m_ext_rom.size());
            ofile.close();
        }   
    }

    Rom(const Rom&) = delete;
    Rom& operator=(const Rom&) = delete;

    std::ifstream m_romfile;
    std::vector<uint8_t> m_header;
    std::vector<uint8_t> m_ext_rom;
    uint8_t m_prg_bank_size;
    bool m_err;
private:
    std::string m_outfname;
};