# Project 3 -- Branch Prediction Simulator

**This is an *individual* project.** You may only collaborate with your
classmates according to the [CS Collaboration
Policy](https://sumnerevans.com/teaching/csci564-s21/#collaboration-policy-for-programming-projects-in-cs-courses).
Plagiarism will be punished severely.

## Learning Objectives

* Create a branch prediction simulator.
* Become familiar with static branch predictors.
* Become familiar with last-time and two-bit branch predictors.
* Become familiar with the difference between global and local branch
  prediction.

## Overview

In this project, you will create a branch prediction simulator which can be used
to observe (a) how different branch prediction policies affect branch prediction
accuracy, and (b) how global/local branch prediction affects branch prediction
accuracy.

It is ***highly recommended*** that you develop this project on a Linux system.
If you choose to use a different type of system (such as macOS or Windows), the
instructors and TAs will not be able to assist you with any platform-specific
issues.

### Rubric

This project is worth **150** points, distributed as follows:

| # | Item       | Points     |
| :-: | :--------- | ---------: |
| 1.1 | Always not-taken (ANT) branch predictor* | 5 |
| 1.2 | Always taken (AT) branch predictor* | 5 |
| 1.3 | Backwards taken, forwards not-taken (BTFNT) branch predictor* | 20 |
| 2.1 | Last-time global (LTG) branch predictor* | 25 |
| 2.2 | Last-time local (LTL) branch predictor* | 35 |
| 3.1 | Two-bit global (2BG) branch predictor* | 25 |
| 3.2 | Two-bit local (2BL) branch predictor* | 35 |
| | **TOTAL** | **150** |

\* indicates that the rubric item is auto-graded

**NOTE:** Since your submission will be partially auto-graded on Gradescope, you
will be only be allowed a total of three submissions. Be sure to test your code
before submitting!

## Branch Predictor Simulation

Your simulator must simulate a branch prediction system with a variety of branch
prediction strategies.

### Branch Predictor Behavior

The following describes how the simulation must behave. *Note that some of this
functionality is already implemented by the starer code.*

**Assumptions:**

* At the start of the simulation, all prediction counters are initialized to
  `NOT_TAKEN`
* At the start of the simulation, all global and local history registers are
  initialized to all zeros.
* The branch target buffer (BTB) is infinite. In other words, the branch
  predictor always knows the branch target.
* For global branch predictors:
  * The global history register (GHR) holds 5 bits of history. Thus the PHT
    holds 32 entries.
* For local branch predictors:
  * There are 16 local history registers (LHRs), indexed by the 4
    least-significant bits of the program counter (instruction address).
  * Each local history register (LHR) holds 4 bits of history.
  * Each LHR has its own pattern history table (PHT).

**For each branch:**

1. The branch predictor is called and provides a prediction as to whether the
   branch is taken or not taken.

2. If the branch prediction was correct, then the correct prediction count is
   incremented.

3. The branch predictor gets updated with the actual result of the branch.

### Branch Predictors

You must implement the following branch predictors.

* `ANT` (**A**lways **N**ot **T**aken, item 1.1 in the rubric) --- always
  predict the branch will not be taken.
* `AT` (**A**lways **T**aken, item 1.2 in the rubric) --- always predict the
  branch will be taken.
* `BTFNT` (**B**ackwards **T**aken, **F**orwards **N**o-**T**aken, item 1.3 in
  the rubric) --- predict that backwards branches (where the `target PC <
  instruction PC`) are taken and forwards branches are not taken.
* `LTG` (**L**ast-**T**ime **G**lobal, item 2.1 in the rubric) --- a two-level
  global branch predictor with a pattern history table consisting of 1-bit
  counters.
* `LTL` (**L**ast-**T**ime **L**ocal, item 2.2 in the rubric) --- a two-level
  local branch predictor with a pattern history table consisting of 1-bit
  counters.
* `2BG` (**2**-**B**it **G**lobal, item 3.1 in the rubric) --- a two-level
  global branch predictor with a pattern history table consisting of 2-bit
  counters.
* `2BL` (**2**-**B**it **L**ocal, item 3.2 in the rubric) --- a two-level
  local branch predictor with a pattern history table consisting of 2-bit
  counters.

### Input Format

The branch trace input will be passed via `stdin`. It has two sections: the
branch target metadata and the branch trace.

**Branch Target Metadata:**

The first line of the file contains `N`, the number of unique branch
instructions there are in the trace. The next `N` lines contain metadata about
those unique branch instructions. Each of those lines are formatted as two
space-separated values that indicate the instruction address and the branch
target address, respectively.

**Branch Trace:**

The rest of the file consists of branch traces formatted as two space-separated
values that indicate the instruction address and whether the branch was taken or
not taken, respectively.

You are guaranteed that the instruction addresses in this part of the file have
corresponding entries in the branch target metadata part of the file.

**Example:**

(Note, the text after the `#`s are just for explanation purposes, and are not
actually part of the input.)

```
4               # number of branches
0x004 0x000     # (instruction address) (branch target)
0x040 0x044
0x04c 0x044
0x080 0x044
0x004 TAKEN     # (instruction address) (taken/not-taken)
0x004 TAKEN
0x004 TAKEN
0x004 NOT_TAKEN
```

## Starter Code Overview

The starter code provides a C project that can be compiled using `make`. The
only dependency for compiling the code is [GCC](https://gcc.gnu.org/).

The starter code should compile as-is, however it will not behave correctly. I
recommend that you attempt to build the starter code before starting to make
your own modifications so that you know that you have something that is working.

The starter code provides an easy way to create a properly formatted submission
TAR.GZ file using `make submission`. This calls the `bin/makesubmission.sh`
script. This script requires `sh` and `tar`.

*Note for [Nix package manager](https://nixos.wiki/wiki/Nix) users*: a
`shell.nix` file is provided with the starter code. Running `nix-shell` will
start a shell with the necessary dependencies installed. If you also use
[direnv](https://direnv.net/), running `direnv allow` will add of the
environment variables from the Nix shell to your current environment when you
`cd` to this directory.

### Downloading the Source

If you want to use git on this project, **please use a *private* repo**. Then,
run the following commands to clone the starter code and set the `origin` to
your repo:
```
git clone https://git.sr.ht/~sumner/aca-project3
git remote set-url origin <your-private-repo-url>
```

Alternatively, if you don't want to use Git, you can download a TAR.GZ of the
source from the following URL:
http://git.sr.ht/~sumner/aca-project3/archive/master.tar.gz

### Building and Running

You can build the starter code by running `make` from this directory. This will
create a `branchsim` executable that you can run. See the [Inputs](#inputs)
section for details on what inputs need to be passed in and what the parameters
are.

You can also run the automated test script which includes some of the inputs
that will be run by the grader script by running the following command:

```
$ make grade
```

This will compile your program and then run the grader script. The grader script
requires Python 3 and scipy.

### Top-Level Organization

The following tree shows an overview of the important files and directories in
the starter code repository.
```
/aca-project3                   project root
|-> bin/                        contains some utility shell scripts
|-> expected/                   contains expected outputs
|-> inputs/                     contains a set of sample input trace files
|-> Makefile                    a Makefile for compiling the project
|-> README.md                   this README file
'-> src/                        all of the source code for the project
```

### Source Organization

All of the places where you potentially need to add code are marked with a
`TODO`. All of the TODOs are in `src/branch_predictors.c`.

There are extensive comments at the top of each file explaining what each one
does. There are also comments throughout the code explaining in detail the most
important parts of the codebase.

The `src/util.h` and corresponding `src/util.c` provide a nice binary print
function that prints the `N` least-significant bits of a given integer. This
function will likely be helpful for debugging.

## Full Requirements

*The following requirements are automatically fulfilled by the starter code
(assuming correct usage).* They are included so that if you choose to write your
simulator without using the starter code, your submission will be able to be
graded.

### Compilation and Runtime Environment

Your submission must compile and run on **Ubuntu 18.04** and the execution of
the simulator must not utilize any network resources. The compilation process
may utilize network resources only for downloading any compilers required to
compile your program. Your program must not error on any well-formed inputs, and
must exit with 0 as the exit code. If the input is malformed, the behavior of
the program is undefined.

**If your submission fails to compile or run on Ubuntu 18.04 without using
network resources during execution, *you will receive a score of 0 for this
project.***

### Submission Format

**Failure to follow the submission format described in this section will result
in a score of 0 for this project.**

You must submit a TAR file with *all* of your source code. The TAR file can
optionally be XZ or GZ compressed. The filename of your submission must match
the following regular expression (case is ignored):

```
(\w+)-project3.(tar(.gz|.xz)?)
-----              ---------
  ▲                      ▲
your MultiPass username  |
                         |
                     optional compression of TAR file
```

Your TAR file must contain a `Makefile` in the root of the archive. Running
`make` should compile your code and create an executable file called `branchsim`
in the same directory as the `Makefile`. This executable must be your branch
prediction simulator implementation.

### Inputs

Your program must accept four positional command line arguments:

* **Branch Predictor Type**: this will be one of the following: `ANT`, `AT`,
  `BTFNT`, `LTG`, `2BG`, `LTL`, or `2BL`, representing the branch predictor to
  use in the simulation.

Your program must accept a trace of branches via `stdin` as described in [Input
Format](#input-format).

Example execution with the `LTG` branch predictor and passing the contents of
the `./inputs/trace1` file via `stdin`.

```
$ ./branchsim LTG < ./inputs/trace1
```

### Output

Your program must provide output on `stdout`. **Output to `stderr` or to a file
will not be graded.**

Additionally, *only lines that start with `OUTPUT` will be graded.* This means
that you can output as much as you want to stdout for debugging purposes as long
as those lines don't begin with `OUTPUT`.

#### Statistics Output

The `OUTPUT` lines that are required are the statistics output which should
be printed after the simulation is complete. Specifically, the following
statistics must be output in order:

* Predictions (int): the total number of branch predictions made
* Correct (int): the total number of correct branch predictions
* Incorrect (int): the total number of incorrect branch predictions
* Branch Prediction Rate (float): the ratio of correct predictions to total
  predictions (formatted with 8 decimal places and a leading zero).

Each of the statistics should be its own line, and should be written in all
caps. For example:

```
OUTPUT PREDICTIONS 150
OUTPUT CORRECT 138
OUTPUT INCORRECT 12
OUTPUT BRANCH PREDICTION RATE 0.92000000
```

## Other Instructors

You are free to use or adapt this project for your course. If you are interested
in my solution or autograder code, please email me at `me [at] sumnerevans [dot]
com`.

## Contributing

Contributions to this project description or to the starter code are welcome!

If you find an issue with the project description or to the starter code or want
to suggest an improvement to it, please submit a patch via
[git-send-email](https://git-send-email.io) to the
[~sumner/public-inbox](https://lists.sr.ht/~sumner/public-inbox) mailing list or
send the patch directly to me. You can also send an email to the mailing list to
discuss potential changes.

## Credits

* README and starter code developed by [Sumner Evans](https://sumnerevans.com).
* Thanks to [Adam Sandstedt](https://github.com/AdamSandstedt) for testing the
  assignment and creating most of the input-output pairs.
