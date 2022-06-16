#include <memory>
#include <string_view>
#include "prgrom.hpp"
#include "chrrom.hpp"


int main(int argc, char **argv) {
    std::string suffix;
    std::string outfn;
    std::string_view romfn;
    std::unique_ptr<Rom> rom;

    static const char *usage = "Usage: nesrx <file> [OPTIONS]\n"
                                "OPTIONS:\n\t-p   PRG ROM\n\t-c   CHR ROM\n\t-o   output file name";

    if (argc < 4) {
        std::cout << usage << std::endl;
        return EXIT_FAILURE;
    } else {
        for (int i = 1; i < argc; i++) {
            if (!std::strcmp(argv[i], "-p")) {
                rom = std::make_unique<PRGRom>();
            } else if (!std::strcmp(argv[i], "-h")) {
                std::cout << usage << std::endl;
                return EXIT_SUCCESS;
            } else if (!std::strcmp(argv[i], "-c")) {
                rom = std::make_unique<CHRRom>();
            } else if (!std::strcmp(argv[i], "-o")) {
                outfn = argv[++i];
                if (dynamic_cast<PRGRom *>(rom.get())) {
                    suffix = ".prg";
                } else {
                    suffix = ".chr";
                }
                outfn.append(suffix);
                rom->setOutfile(outfn);
            } else {
                if (romfn.empty()) {
                    romfn = argv[i];
                }
            }
        }
    }
    
    try {
        rom->loadRom(romfn);
        rom->save();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
  
    return EXIT_SUCCESS;

}
