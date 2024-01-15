
#include <iostream>
#include <string>
#include <bitset>

std::string BinaryToHex(std::string binary)
{
    int num = std::bitset<32>(binary).to_ulong();
    std::string hex;
    std::string hexChars = "0123456789ABCDEF";
    while (num != 0)
    {
        int remainder = num % 16;
        hex = hexChars[remainder] + hex;
        num /= 16;
    }
    if (hex.empty())
    {
        hex = "0";
    }
    return hex;
}

int main(int argc, char *argv[])
{
    std::string binaryNumber;
    std::cout << "Enter a binary number: ";
    std::cin >> binaryNumber;
    std::string hexNumber = BinaryToHex(binaryNumber);
    std::cout << "Hexadecimal equivalent: " << hexNumber << std::endl;

	return EXIT_SUCCESS;
}
