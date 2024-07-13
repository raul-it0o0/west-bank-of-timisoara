# West Bank of Timisoara

The West Bank of Timisoara is a bank management system with which one can create a bank account, and view balances.

### Current features
- Creating an account, in a specific currency, out of 5 currently supported currencies
- Viewing the accounts current balance.
- Data storage in a local database (a CSV file), which is fetched during each login.

### Future Plans
- Better parsing of and writing to files (better database management)
- Better data file structure (*i.e. not everything in one data file*)
- Better memory management (less unnecessary heap allocations)
- Better UI (terminal user interface)
- Other features (account editing, account deletion, transfers between accounts)
- Cross-platform support

## Running Locally

Some **prerequisites** to keep in mind:
1. Have the latest version of **CMake** (at least version `3.27`) installed.
2. Have a **C compiler** (such as `gcc`) and a **build system** (such as GNU `make` or Ninja) installed.
3. A **Windows** operating system. Some functions are OS-dependent.

***

Clone the project.

```bash
git clone https://github.com/raul-it0o0/west-bank-of-timisoara
```

Create a `build` directory for the build files to be generated in, and navigate into that directory.

```bash
mkdir build
cd build
```

Run CMake, pointing it to the parent directory, where the `CMakeLists.txt` file is located.

```bash
cmake ..
```

Build the project.

```bash
cmake --build .
```

The executable `login`, as specified by `CMakeLists.txt` has been created in the `bin` directory of the root directory. Navigate to it.

```bash
cd ../bin
```

Run the executable with two arguments, corresponding to the *first name* and *last name* of the bank account owner to be registered. See the example below:

```bash
./login John Doe
```
From there on, the terminal user interface is simple to use for anything you wish to do.