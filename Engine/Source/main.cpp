#include "EngineMacros.h"

int main() {
    const char* testString = "ad";
    // Load the DLL
    HMODULE hDLL = LoadLibraryA("Sandbox.dll");

    if (hDLL == nullptr) {
        std::cerr << "Failed to load the DLL using LoadLibrary" << std::endl;
    }
    else {


        // Free the DLL module
        FreeLibrary(hDLL);
    }

    return 0;
}