#ifndef MCCPP_RSAKEYPAIR_H
#define MCCPP_RSAKEYPAIR_H


#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>

#define KEY_SIZE 1024

class RSAKeypair {
public:
    RSAKeypair() {
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::InvertibleRSAFunction params;
        params.GenerateRandomWithKeySize(rng, KEY_SIZE);
        m_private_key = new CryptoPP::RSA::PrivateKey(params);
        m_public_key = new CryptoPP::RSA::PublicKey(*m_private_key);
    }

    [[nodiscard]] CryptoPP::RSA::PrivateKey *get_private_key() const;

    [[nodiscard]] CryptoPP::RSA::PublicKey *get_public_key() const;

    [[nodiscard]] std::vector<uint8_t> get_der_encoded_public_key() const;
private:
    CryptoPP::RSA::PrivateKey *m_private_key;
    CryptoPP::RSA::PublicKey *m_public_key;
};


#endif
