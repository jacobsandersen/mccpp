#include <iostream>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include "MinecraftServer.h"

int main() {
    try {
        std::cout << "Generating RSA keypair. Please wait...";
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::InvertibleRSAFunction params;
        params.GenerateRandomWithKeySize(rng, 1024);
        CryptoPP::RSA::PrivateKey privateKey(params);
        CryptoPP::RSA::PublicKey  publicKey(privateKey);
        std::string encoded;
        CryptoPP::StringSink ss(encoded);
        publicKey.DEREncode(ss);
        ss.MessageEnd();
        std::cout << "Keypair generated." << std::endl;

        std::cout << "Starting network thread...";
        std::thread([publicKey, privateKey](){
            MinecraftServer server(120, publicKey, privateKey);
            server.start();
        }).detach();
        std::cout << "Network thread started. Initialization finished." << std::endl;

        while(true) {}
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}