#ifndef IMAGE_CRYPTO_HPP
#define IMAGE_CRYPTO_HPP

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Simple XOR-based encryption with password
class ImageCrypto {
private:
    std::vector<uint8_t> key;
    
    void generate_key(const std::string& password) {
        key.clear();
        if (password.empty()) return;
        
        // Generate 256-byte key from password
        key.resize(256);
        size_t pwd_len = password.length();
        for (size_t i = 0; i < 256; i++) {
            key[i] = password[i % pwd_len] ^ (i & 0xFF);
        }
    }

public:
    ImageCrypto(const std::string& password) {
        generate_key(password);
    }

    // Encrypt image data in-place
    void encrypt(uint8_t* data, size_t size) {
        if (key.empty() || !data) return;
        
        for (size_t i = 0; i < size; i++) {
            data[i] ^= key[i % key.size()];
        }
    }

    // Decrypt image data in-place
    void decrypt(uint8_t* data, size_t size) {
        // XOR encryption is symmetric
        encrypt(data, size);
    }

    // Check if encryption is enabled
    bool is_enabled() const {
        return !key.empty();
    }
};

#endif // IMAGE_CRYPTO_HPP
