# FileEncryptionDecryption

FileEncryptionDecryption is a versatile tool designed for encrypting and decrypting files using various encryption techniques. The project supports both a command-line interface (CLI) and a graphical user interface (GUI) to provide flexibility for different users. 

## Functionality

This tool allows users to:
- Encrypt and decrypt text or binary files.
- Choose from multiple encryption methods (e.g., Caesar Cipher, XOR encryption, etc.).
- Specify custom encryption keys.
- (WIP) Advanced encryption algorithms such as AES and RSA.
- (WIP) Support for encrypting entire directories.
- (WIP) Save and load encryption settings.

## How to Use the CLI Tool

Once you have built the executable for the CLI version, you can use it as follows:

1. **Encrypting a File**
    ```bash
    ./fileencrypt --encrypt --file <file_path> --method <encryption_method> --key <encryption_key>
    ```
    Example:
    ```bash
    ./fileencrypt --encrypt --file myfile.txt --method XOR --key 12345
    ```

2. **Decrypting a File**
    ```bash
    ./fileencrypt --decrypt --file <file_path> --method <encryption_method> --key <decryption_key>
    ```
    Example:
    ```bash
    ./fileencrypt --decrypt --file myfile_encrypted.txt --method XOR --key 12345
    ```

3. **Command-line Options**:
    - `--encrypt`: Encrypt the specified file.
    - `--decrypt`: Decrypt the specified file.
    - `--file <file_path>`: The file to encrypt or decrypt.
    - `--method <encryption_method>`: Choose the encryption method (e.g., Caesar, XOR).
    - `--key <key>`: Provide a custom encryption key.
  
4. **(WIP) Encryption of Directories**:
    Placeholder for when directory encryption is implemented.

## Building the Executables

### Prerequisites

Before building the project, ensure that you have the following installed:
- C++ compiler (e.g., GCC or MSVC)
- (Optional) A GUI framework if you are building the GUI version

### Building the CLI Tool

To build the command-line executable:

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/FileEncryptionDecryption.git
    cd FileEncryptionDecryption
    ```

2. Compile the CLI tool:
    ```bash
    g++ -o fileencrypt cli.cpp encryption.cpp -std=c++11
    ```

3. Run the executable:
    ```bash
    ./fileencrypt --help
    ```

### Building the GUI Tool (WIP)

Instructions for building the GUI will be provided once the GUI implementation is complete.

## Features (WIP)

- [ ] Advanced encryption algorithms (AES, RSA)
- [ ] Directory encryption support
- [ ] GUI interface

---

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests for features, bug fixes, or improvements.

## License

This project is licensed under the APACHE License.
