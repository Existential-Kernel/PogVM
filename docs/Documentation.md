<h1 align="center">KAA Year 12 Programming Project</h1>

- [Introduction](#Introduction)
  - [What is it?](#what-is-it)
- [Planning](#Planning)
  - [Explaining my choices in depth](#explaining-my-choices-in-depth)
  - [My choices](#my-choices)
- [How it works](#how-it-works)
- [Linux environment compatibility](#Linux-environment-compatibility)
- [Difficulties](#difficulties)
  - [Assembly in itself](#assembly-in-itself)
  - [Challenges of creating a VM](#challenges-of-creating-a-vm)
  - [Absence of libraries](#not-using-any-external-libraries)
- [Flowchart](#flowchart)
- [Conclusion](#conclusion)

---


## Introduction
  #### What is it? (rewriting needed)
  - PogVM (note to myself: think of an acronym for the name) is a virtual machine written in C++. It's a CISC processor (or VCISC technically speaking), and it's designed to run executable files from a cross platform perspective and emulate a modern x86-64 CPU as accurately as possible. 


## Planning
  #### Explaining my choices in depth
  - My project choice
    - I had a few project ideas I've already had in my head even before the school project started, but creating a VM stood out to me the most (VM will stand as Virtual Machine from now on). I enjoy taking on complicated challenges even if it would take me months, and I'm the type of person who has a keen interest in complex systems. I could've chosen a far more simpler project, but I chose a VM because it's incredibly hard to make one, and I've learned that small virtual machines designed for executable files have not yet been built while I was searching on GitHub, so I figured this would be a useful project that's not only for my school programming project, but it could be used as a utility tool by other people while making a very small contribution to the open source ecosystem.  

  - language choice
    - The reason why I used C++ is because I figured it would be the best language for something as complex as a virtual machine. Although I'm also fluent in JavaScript, C++ offers many features that are really useful when it comes to bulky system programs, and compiled languages are far better suited for a virtual machine than an interpreted language such as the aforementioned JavaScript, mainly because interpreted languages are generally slow (around 100x or 200x slower compared to a language like C or other system level languages). Although the slow nature of interpreted languages aren't usually visible with the naked eye at first glance, I've experienced the major drawbacks I've faced with creating large projects in the past due to how slow it has gradually become, even with optimisations. Because of this, I thought C++ would be the best choice before I started writing any code, and looking back after finishing the project, I believe that was the best decision I could've made.

  - Initial Intentions
    - When I started this project, I didn't have a clear goal in mind in terms of the logic that operates the entire core of the project. Initially, I wanted to create a Virtual CPU because I thought it would be a fun project for myself (the project was previously named "PogCPU", this can be seen in older commits in the repository). As the structure of the CPU gbecame more and more organised and clear, I figured it would be best to turn it into a VM for the KAA programming project.

  - Assembly
    - Although it may be obvious that creating a VM without knowing any


## How it works (rewriting needed)
  #### Overview
    - The project has over 2200 lines of code as of now.
  
  #### Options
    -

  #### Compiler and interpreter mode
    -


## Linux environment compatibility
  #### Compatibility to other Operating Systems
    - The entire project has been made on Linux, and it was also designed to be ran on Linux because that's the OS that I personally use on my desktop computer (specifically Fedora 35). I've tried my best to try and make it as compatible as possible with Windows (which was a bit of a challenge in itself) but I think it doesn't have any major bugs. However, I am not 100% confident that it's bug-proof, so I used what's known as Docker. Docker is a small VM that's designed to run a simplified version of Operating systems in an isolated environment to run software, usually used to run them on a standardised OS that's supported by the program. It's a bit similar to my own project, but my VM is mostly designed to analyse executable files and disect it in a safe environment. Meanwhile, Docker is used to runt software in VMs for the purpose of software compatibility. 

    The OS I'm using for docker is called Alpine Linux. The reason for this choice is because Alpine is an incredibly lightweight OS, and it's very small compared to others out there. It's a great choice for a lot of software because of how reliable it is, so I chose it for the aforementioned reasons.

## Difficulties
  #### Assembly in itself
    - x86-64 assembly is notoriously hard to work with in any kind of situation ro project. It's completely different from the simplified syntax of assembly that we've covered in CS classes (mainly the Little Man Computer instruction set). The main problem in trying to emulate an x86-64 CPU is that it has around a thousand instructions with each one having a varying level of complexity. Also, it's a convoluted and incredibly complicated mess (at least from my perspective). This is mainly because x86-64 does not work as how we might imagine when thinking about assembly in general: most of the instructions have multiple opcodes rather than having a single one if there are slight changes to the instruction. For example:

    ```

    (give example here when i have time)
  
    ``` 

    And this is only one of the major caveats I've faced with x86-64. There are many problems I've faced and I've spent countless hours of trying to understand every small detail about the instruction set with very slow progress. In fact, the sheer complexity of it nearly made me quit the project entirely due to how dauntingly and ungodly complicated it was. In reality, I still do not understand most of x86-64 as of writing this. I would never claim I have any form of expertise in that subject with its layers upon layers of weird and strict rules associated with it.

  #### Challenges of creating a VM


  #### Absence of libraries
    - Most high level languages that offers a package-based system to import code and other functionalities (python, javascript, etc...) are incredibly useful. But in C++, there's not an official package manager that's officially supported by the language. Although there's a collection of C++ libraries called [Boost](https://www.boost.org/), it is arguably clunky and it has many problems surrounding it. However, it does have useful functionalities, especially if a program gets more and more complicated. Contrary to what most people would do in this scenario, I have decided to NOT use any libraries because I wanted to keep my code as clean as possible, and as fast as possible at the same time. Boost in itself is a massive collection of libraries and I figured it would most likely slow down my VM's performance, so I sacrificed utility over efficiency by not using any external libraries which could've made my project easier for myself in exchange for performance. 

## Flowchart
  #### Image
    - create a flowchart image in photoshop or something idk
    - explain the flowchart

## Conclusion