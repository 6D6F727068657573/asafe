#include <iostream>
#include <exception>

#include "control.h"
#include "logging.h"

int main(int argc, char* argv[]) {
    using namespace arch_safeguard;
    using namespace arch_safeguard::logging;

    try {
        if(argc == 2 && strcmp("check", argv[1]) == 0) {
            return check();
        }

        if(argc == 2 && strcmp("mark-resolved", argv[1]) == 0) {
            return mark_resolved();
	}

        if(argc == 3 && strcmp("set-mode", argv[1]) == 0) {
            return set_mode(argv[2]);
        }

        return help();

    } catch(const std::exception& e) {
        std::cerr << "An error has occured: '" << e.what() << "'.";
        log(level::ERROR) << e.what() << "\n";
        return EXIT_FAILURE;
    }
}

