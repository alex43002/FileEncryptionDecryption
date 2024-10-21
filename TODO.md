# TODO: Encryption Tool Enhancements

## General Tasks
- [x] Add a command-line parameter for the encryption key.

## DES Algorithm Implementation
- [ ] Research and understand the structure of DES (Data Encryption Standard).
  - [ ] Implement initial permutation (IP).
  - [ ] Implement the function to divide the data into two halves (left and right).
  - [ ] Implement the 16 rounds of encryption (Feistel structure):
    - [ ] Implement the expansion function (E-box).
    - [ ] Implement the XOR operation with the round key.
    - [ ] Implement the S-box substitution.
    - [ ] Implement the permutation function (P-box).
    - [ ] Swap halves after each round.
  - [ ] Implement the final permutation (inverse of IP).
- [ ] Add DES encryption function to the encryption tool.
- [ ] Add DES decryption function.

## Testing
- [ ] Test DES encryption with various input files.
- [ ] Test DES decryption to ensure the output matches the original file.
- [ ] Ensure proper handling of edge cases (e.g., key length, empty files).

## Documentation
- [x] Update the help output for the new encryption key parameter.
- [ ] Add instructions for using the DES algorithm in the documentation.
