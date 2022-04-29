<div align="center">
  <h1>PogVM</h1>
  A mini Virtual Machine designed to run executable files

  <br>
          ========================== <br>
  🚧 NOTE: THIS PROJECT IS UNDER CONSTRUCTION 🚧 <br>
          ========================== <br>
  </p>
</div>

<!-- NOTE: Add demo of the VM here -->

## FEATURES
- x86-64 assembly interpreter     (WIP)
- Hybrid CISC and RISC processor  (WIP)
- Scalar pipelining architecture  (WIP)
- Executable file analyser        (WIP)
- No external libraries used, just raw C++
- No hypervisor dependency (mostly bc I have no idea how to implement it lol)

## PREREQUESITES
- You must have at least 2 cores in the CPU you're using

## INSTALL
  **Docker**
  ```
  mkdir build
  cd build
  cmake ..
  ```

## OPTIONS
  Command pattern: `pogvm [options] [executable file]`

  Example: `pogvm --info ./test`

  | Option | Description | Alias |
  |---|---|---|
  | --version | Displays PogVM's version | -v |
  | --help | Displays the help menu for all the options | -h |
  | --audit | Displays the compatibility of PogVM on your device | -a |
  | --header | Displays the ELF file header information | -hd |
  | --program | Displays the ELF file program information | -p |
  | --sections | Displays the ELF file section information | -s |
  | --info | Displays all the ELF file information (equivalent to -hd -p -s) | -i |


## CONTRIBUTING


## RESOURCES USED
- https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html
- https://upload.wikimedia.org/wikipedia/commons/e/e4/ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png
- https://wiki.osdev.org/CPU_Registers_x86
- https://blog.yossarian.net/2020/11/30/How-many-registers-does-an-x86-64-cpu-have
- https://en.wikipedia.org/wiki/Executable_and_Linkable_Format