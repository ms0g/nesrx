#include <memory>
#include <string_view>
#include "prgrom.hpp"
#include "chrrom.hpp"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_MICRO 0

#define STRINGIFY0(s) # s
#define STRINGIFY(s) STRINGIFY0(s)

#define VERSION STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_MICRO)


int main(int argc, char **argv) {
    std::string_view romfn;
    std::string_view outfn;
    std::unique_ptr<Rom> rom;

    static const char *usage = "Usage:  nesrx [ -<flag> [<val>] | --<name> [<val>] ]... <rom file>\n\n   "
                                "-p, --prg-rom              PRG ROM\n   "
                                "-c, --chr-rom              CHR ROM\n   "
                                "-o  --outfile              Output rom file\n   "
                                "-h, --help                 display usage information and exit\n   "
                                "-v, --version              display version information and exit\n";

    if (argc < 5) {
        if (argc == 2 && (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help"))) {
            std::cout << usage << std::endl;
            return EXIT_SUCCESS;
        } else if (argc == 2 && (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version"))) {
            std::cout << "nesrx version " << VERSION << std::endl;
            return EXIT_SUCCESS;
        }
        std::cout << usage << std::endl;
        return EXIT_FAILURE;
    }
    
    for (int i = 1; i < argc; i++) {
        if (!std::strcmp(argv[i], "-p") || !std::strcmp(argv[i], "--prg-rom")) {
            rom = std::make_unique<PRGRom>();
        } else if (!std::strcmp(argv[i], "-c") || !std::strcmp(argv[i], "--chr-rom")) {
            rom = std::make_unique<CHRRom>();
        } else if (!std::strcmp(argv[i], "-o") || !std::strcmp(argv[i], "--outfile")) {
            outfn = argv[++i];
        } else {
            if (romfn.empty())
                romfn = argv[i];
        }
    }

    try {
        rom->setOutfile(outfn);
        rom->loadRom(romfn);
        rom->save();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
  
    return EXIT_SUCCESS;

}
