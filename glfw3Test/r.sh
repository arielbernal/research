make -j8

ANTTWEAKBAR=/home/ajbernal/dev/bat/research/external/vs/AntTweakBar/lib
GLFW3=/home/ajbernal/dev/bat/research/external/linux/glfw-3.1/src

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/$ANTTWEAKBAR:/$GLFW3
export LD_LIBRARY_PATH

./bin/glfw3Test
