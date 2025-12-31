#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "../image_crypto.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <encrypted_image> <output_image> <password>\n";
        std::cout << "Example: " << argv[0] << " encrypted.png decrypted.png mypassword\n";
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];
    const char* password = argv[3];

    // Read encrypted file
    std::ifstream input(input_path, std::ios::binary);
    if (!input) {
        std::cerr << "Error: Cannot open input file: " << input_path << "\n";
        return 1;
    }

    input.seekg(0, std::ios::end);
    size_t file_size = input.tellg();
    input.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(file_size);
    input.read(reinterpret_cast<char*>(data.data()), file_size);
    input.close();

    // Decrypt
    ImageCrypto crypto(password);
    crypto.decrypt(data.data(), file_size);

    // Write decrypted file
    std::ofstream output(output_path, std::ios::binary);
    if (!output) {
        std::cerr << "Error: Cannot open output file: " << output_path << "\n";
        return 1;
    }

    output.write(reinterpret_cast<const char*>(data.data()), file_size);
    output.close();

    std::cout << "Successfully decrypted " << input_path << " to " << output_path << "\n";
    return 0;
}
