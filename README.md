Word Reverser
=============

This is a small and simple program to reverse the words in a string. For example, the phrase "there are words everywhere" becomes "everywhere words are there". It supports a couple different reversal algorithms, as well as demonstrations of each algorithm.

An example of the program in action:

![Wordreverse in action (archive image here: http://nacr.us/media/pics/wordreverse_anim10_imagemagick.gif)](http://i.imgur.com/MJ5z5Gs.gif)


Building the Project
--------------------

To build the project, run `make` in this directory. This will build an executable called `word_reverse` in the `build/` directory. Copy that to wherever it is you put your executables.


Why?
----

This spawned from an exercise posed somewhere to write a C program to to reverse the words in a sentence, then to write another program that reverses the words in the string in place.


Project Structure
-----------------

Regarding the structure of this project, it is loosely based on the structure outlined in Zed Shaw's "Learn C the Hard Way". That is:

- `include/` contains the `.h` header files for the program
- `src/` contains the corresponding `.c` files
- `tests/` contains `.c` files that run tests on the modules in the `src/` folder
- The starting point of the ultimate program is found in the `src/main.c` source file


Additional Developer Notes
--------------------------

Because of how the `Makefile` for this project works, there are some conventions that must be followed for things such building the project or automated tests to work:

1. Automated tests
	- There is up to one automated test file per module in the `src/` folder.
	- The name of the test file must be `<module name>_test.c`. For example, if there where a file `src/foo.c` then the automated test for that module would be `tests/foo_tests.c`.
	- Automated tests must make use of the `include/minunit.h` file as their automated testing framework. Further elaboration on using the testing framework [can be found here](http://c.learncodethehardway.org/book/ex30.html).
2. Module and include file names
	- A module has two files, it's header and it's source. They must both have the exact same name, except the include file has a `.h` file extension while the source file has a `.c` file extension. The include file goes in the `include/` directory and the source file goes in the `src/` directory. If their names differ, the project may compile, but further breakages may ensue.
3. Makefile
	- Alongside the bare `make` directive, there are other things you can make:
		1. `make dev` will build the final executable with debugging on and extra compiler warnings. Useful for developers.
		2. `make tests` will create and run a test executable for each automated test in the `tests/` folder.
