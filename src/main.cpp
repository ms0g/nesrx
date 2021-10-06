#include <iostream>
#include "prgrom.hpp"
#include "chrrom.hpp"

enum class State : int {
    PRG_ROM,
    CHR_ROM
};

int main(int argc, char **argv) {
    State state;
    std::string suffix;
    std::string outfn;
    std::string romfn;
    std::unique_ptr<Rom> rom;

    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <file> [OPTIONS]\n" 
                  << "OPTIONS:\n\t-p   PRG ROM\n\t-c   CHR ROM\n\t-o   output file name" << std::endl;
        return EXIT_FAILURE;
    } else {
        for (int i = 1; i < argc; i++) {
            if (!std::strcmp(argv[i], "-p")) {
                state = State::PRG_ROM;
            } else if (!std::strcmp(argv[i], "-c")) {
                state = State::CHR_ROM;
            } else if (!std::strcmp(argv[i], "-o")) {
                outfn = argv[i+1];
                if (state == State::PRG_ROM) {
                    suffix = ".prg";
                } else if (state == State::CHR_ROM) {
                    suffix = ".chr";
                }
                outfn.append(suffix);
            } else {
                if (romfn.empty()) {
                    romfn = argv[i];
                }
            }
        }
    }

    switch (state) {
        case State::PRG_ROM:
            rom = std::make_unique<PRGRom>(romfn, outfn);
            break;
        case State::CHR_ROM:
            rom = std::make_unique<CHRRom>(romfn, outfn);
            break;
        default:
            break;
    }
    rom->save();
    return EXIT_SUCCESS;

}
