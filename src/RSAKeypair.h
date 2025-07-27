#ifndef CELERITY_RSAKEYPAIR_H
#define CELERITY_RSAKEYPAIR_H

#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

#define KEY_SIZE 1024

namespace celerity {
class RSAKeypair {
 public:
  RSAKeypair() {
    CryptoPP::AutoSeededRandomPool pool;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(pool, KEY_SIZE);
    m_private_key = new CryptoPP::RSA::PrivateKey(params);
    m_public_key = new CryptoPP::RSA::PublicKey(*m_private_key);
  }

  [[nodiscard]] CryptoPP::RSA::PrivateKey *get_private_key() const;

  [[nodiscard]] CryptoPP::RSA::PublicKey *get_public_key() const;

  [[nodiscard]] std::vector<uint8_t> get_der_encoded_public_key() const;

  [[nodiscard]] std::vector<uint8_t> decrypt(
      const std::vector<uint8_t> &encrypted) const;

 private:
  CryptoPP::RSA::PrivateKey *m_private_key;
  CryptoPP::RSA::PublicKey *m_public_key;
};
}  // namespace celerity

#endif
