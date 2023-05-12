# Glen (openGL ENgine)

The idea is very very simple. Its simple boilerplate to get people started with OpenGL without having to ardously
create shader classes, VBO, EBO, VAO, the whole lot.

So this repository does exactly that, no more, no less.

## Prerequisites 
- A compiler (such as `clang` from LLVM or `gcc`, both are worthy to be used).
- `make` or `ninja` as a buildtool.
- An access to a terminal.

## Getting Started
1. Clone this repository -> `git clone https://github.com/sacreative10/Glen`
> Note:
> At this point you can open the local repository in any editor of your choice, and if your editor already supports CMake (like CLion, which I use), you can open it right there 
2. In the root of the local repository, create a new folder, preferably `build` -> ` mkdir build `
3. In this new folder, run -> ` cmake .. `
4. This has created the build configuration to be compiled, now most likley, `make` has been chosen as your build tool, if it is anything else, you already know what you are doing.
5. Compile -> ` make -j10 ` Note that the flag `j10`, allows the compiler to concurrently compile the program, this speeds compilation time up, change it if you need to.
6. Run! -> `./Glen` 

## Making it your own
So here is where the tutorial ends, and the open world begins. Start by reading `main.cpp` and getting a feel for the asinine 
code style used.

Personally, I would reccommend using videos or books to dip your body into the world of OpenGL. Such as:
- Victor Gordan's series on OpenGL (code from there has been used here as well) -> (https://youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)
- LearnOpenGL book, an excellent choice to learn OpenGL from -> (https://learnopengl.com/)

## Contribuiting
Feel free to add features by creating pull requests, which soon will be merged. If you run into any issues, best bet is to recreate the issue, and if so, also create a issue on this github repo.
