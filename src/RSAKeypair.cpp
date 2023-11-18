#include "RSAKeypair.h"

CryptoPP::RSA::PrivateKey *RSAKeypair::get_private_key() const {
    return m_private_key;
}

CryptoPP::RSA::PublicKey *RSAKeypair::get_public_key() const {
    return m_public_key;
}

std::vector<uint8_t> RSAKeypair::get_der_encoded_public_key() const {
    std::vector<uint8_t> encodedPublicKey;

    CryptoPP::VectorSink vs(encodedPublicKey);
    get_public_key()->DEREncode(vs);
    vs.MessageEnd();

    return encodedPublicKey;
}
