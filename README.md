# DNS forwarder

This is the DNS forwarder implementation for [John Crickett Coding Challenge #44 - DNS Forwarder](https://codingchallenges.substack.com/p/coding-challenge-44-dns-forwarder)

## Compilation

⚠️⚠️ Only works in Linux!

Clone this repo and cd into the project root directory:

```bash
git clone https://github.com/mdhvg/dns-forwarder.git
cd dns-forwarder
```

It requires no other dependencies except build tools:

- `cmake`
- `make` or `ninja`

Compile using cmake:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Compiled binary is placed in the `./bin` directory

From the project root directory, just run `./bin/dns`
