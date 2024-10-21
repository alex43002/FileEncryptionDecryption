# FileEncryptionDecryption

FileEncryptionDecryption is a versatile tool designed for encrypting and decrypting files using various encryption techniques. The project currently supports a **command-line interface (CLI)**, with plans to add a graphical user interface (GUI) in future versions.

## Functionality

This tool allows users to:
- Encrypt and decrypt text or binary files.
- Choose from multiple encryption algorithms, such as **DES** (with more to be added, e.g., AES, RSA).
- Provide custom encryption keys for security.
- (WIP) Support for encrypting entire directories.
- (WIP) Save and load encryption settings.

## How to Use the CLI Tool

Once you have built the executable for the CLI version, you can use it as follows:

### 1. **Encrypting a File**
   The tool supports the following usage pattern for encryption:
   ```bash
   encryption_tool.exe --encrypt <encryption_method> <encryption_key> <input_file> <output_file>
   ```
   Example:
   ```bash
   encryption_tool.exe --encrypt DES my_secret_key input.txt encrypted_output.txt
   ```

### 2. **Decrypting a File**
   The tool supports the following usage pattern for decryption:
   ```bash
   encryption_tool.exe --decrypt <encryption_method> <encryption_key> <input_file> <output_file>
   ```
   Example:
   ```bash
   encryption_tool.exe --decrypt DES my_secret_key encrypted_output.txt decrypted_output.txt
   ```

### 3. **Command-line Options**:
   - `--encrypt`: Encrypt the specified input file using the chosen algorithm and save it to the output file.
   - `--decrypt`: Decrypt the specified input file using the chosen algorithm and save it to the output file.
   - `<encryption_method>`: Choose the encryption algorithm (e.g., `DES`). More methods will be added (e.g., AES, RSA).
   - `<encryption_key>`: Provide a custom encryption key for encryption or decryption.
   - `<input_file>`: The file to encrypt or decrypt.
   - `<output_file>`: The file where the encrypted or decrypted result will be saved.

### Example Usages:
1. **Encrypting with DES**:
   ```bash
   encryption_tool.exe --encrypt DES my_secret_key input.txt output_encrypted.txt
   ```
2. **Decrypting with DES**:
   ```bash
   encryption_tool.exe --decrypt DES my_secret_key output_encrypted.txt output_decrypted.txt
   ```

### 4. **(WIP) Encryption of Directories**:
   Placeholder for when directory encryption is implemented.

## Building the Executables

### Prerequisites

Before building the project, ensure that you have the following installed:
- C++ compiler (e.g., GCC or MSVC)

### Windows: Using `build.bat`

For Windows users, you can use the provided `build.bat` script to compile the project.

1. Clone the repository:
    ```bash
    git clone https://github.com/alex43002/FileEncryptionDecryption.git
    cd FileEncryptionDecryption
    ```

2. Run the `build.bat` script:
    ```bash
    build.bat
    ```

3. Once the build is complete, you can run the executable:
    ```bash
    encryption_tool.exe --help
    ```

### Linux: Using `build.sh`

For Linux users, you can use the provided `build.sh` script to compile the project.

1. Clone the repository:
    ```bash
    git clone https://github.com/alex43002/FileEncryptionDecryption.git
    cd FileEncryptionDecryption
    ```

2. Make the script executable:
    ```bash
    chmod +x build.sh
    ```

3. Run the script:
    ```bash
    ./build.sh
    ```

4. Once the build is complete, you can run the executable:
    ```bash
    ./encryption_tool --help
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