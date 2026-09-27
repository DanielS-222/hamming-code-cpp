#include <iostream>
#include <string>

using uint8 = unsigned char;

void PrintBits(uint8 value, int bits) {
    for (int i = bits - 1; i >= 0; --i) {
        std::cout << ((value >> i) & 1);
    }
}

// Encode 4 information bits into an 8-bit extended Hamming code word.
uint8 Encode(uint8 x) {
    uint8 x0 = (x >> 3) & 1;
    uint8 x1 = (x >> 2) & 1;
    uint8 x2 = (x >> 1) & 1;
    uint8 x3 = x & 1;

    return (x0 << 5) |
           (x1 << 3) |
           (x2 << 2) |
           (x3 << 1) |
           ((x0 ^ x1 ^ x3) << 7) |
           ((x0 ^ x2 ^ x3) << 6) |
           ((x1 ^ x2 ^ x3) << 4) |
           (x0 ^ x1 ^ x2);
}

// Calculate the Hamming syndrome and overall parity.
uint8 Syndrome(uint8 v) {
    uint8 b0 = (v >> 7) & 1;
    uint8 b1 = (v >> 6) & 1;
    uint8 b2 = (v >> 5) & 1;
    uint8 b3 = (v >> 4) & 1;
    uint8 b4 = (v >> 3) & 1;
    uint8 b5 = (v >> 2) & 1;
    uint8 b6 = (v >> 1) & 1;
    uint8 b7 = v & 1;

    return ((b3 ^ b4 ^ b5 ^ b6) << 3) |
           ((b1 ^ b2 ^ b5 ^ b6) << 2) |
           ((b0 ^ b2 ^ b4 ^ b6) << 1) |
           (b0 ^ b1 ^ b2 ^ b3 ^ b4 ^ b5 ^ b6 ^ b7);
}

enum class DecodeStatus {
    NoError,
    SingleErrorCorrected,
    ParityErrorCorrected,
    DoubleErrorDetected
};

struct DecodeResult {
    uint8 word;
    DecodeStatus status;
};

DecodeResult Decode(uint8 v) {
    uint8 syn = Syndrome(v);

    uint8 errPos = (syn & 0xE) >> 1;
    uint8 parity = syn & 1;

    if (errPos == 0 && parity == 0) {
        return {v, DecodeStatus::NoError};
    }

    if (errPos != 0 && parity == 1) {
        uint8 mask = 1 << (8 - errPos);

        return {
            static_cast<uint8>(v ^ mask),
            DecodeStatus::SingleErrorCorrected
        };
    }

    if (errPos == 0 && parity == 1) {
        return {
            static_cast<uint8>(v ^ 1),
            DecodeStatus::ParityErrorCorrected
        };
    }

    return {
        v,
        DecodeStatus::DoubleErrorDetected
    };
}

// Extract the original 4 information bits.
uint8 Extract(uint8 u) {
    return ((u >> 5) & 1) << 3 |
           ((u >> 3) & 1) << 2 |
           ((u >> 2) & 1) << 1 |
           ((u >> 1) & 1);
}

std::string StatusToString(DecodeStatus status) {
    switch (status) {
        case DecodeStatus::NoError:
            return "No error";

        case DecodeStatus::SingleErrorCorrected:
            return "Single error corrected";

        case DecodeStatus::ParityErrorCorrected:
            return "Parity bit error corrected";

        case DecodeStatus::DoubleErrorDetected:
            return "Double error detected";
    }

    return "Unknown";
}

void RunCase(const std::string& name, uint8 received) {
    DecodeResult result = Decode(received);

    std::cout << "\n--- " << name << " ---\n";

    std::cout << "Received: ";
    PrintBits(received, 8);
    std::cout << "\n";

    std::cout << "Status: "
              << StatusToString(result.status)
              << "\n";

    std::cout << "Result:   ";
    PrintBits(result.word, 8);
    std::cout << "\n";

    if (result.status != DecodeStatus::DoubleErrorDetected) {
        uint8 data = Extract(result.word);

        std::cout << "Data:     ";
        PrintBits(data, 4);
        std::cout << "\n";
    } else {
        std::cout << "Data was not recovered because "
                     "a double error cannot be corrected.\n";
    }
}

int main() {
    uint8 original = 0b1011;
    uint8 encoded = Encode(original);

    std::cout << "Original data: ";
    PrintBits(original, 4);

    std::cout << "\nEncoded word:  ";
    PrintBits(encoded, 8);

    std::cout << "\n";

    // No error.
    RunCase(
        "No error",
        encoded
    );

    // One incorrect bit.
    RunCase(
        "Single-bit error",
        static_cast<uint8>(encoded ^ (1u << 5))
    );

    // Error in the additional parity bit.
    RunCase(
        "Parity-bit error",
        static_cast<uint8>(encoded ^ 1u)
    );

    // Two incorrect bits.
    RunCase(
        "Double-bit error",
        static_cast<uint8>(
            encoded ^
            (1u << 7) ^
            (1u << 6)
        )
    );

    return 0;
}
