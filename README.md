# Game2048
<p>
  Recreation of 2048 game made in one day from scratch using c++
</p>
<h2>Compiling</h2>

```
g++ -c src/*.cpp -std=c++14 -O3 -IC:/mingw64/include -Wall -m64 && g++ *.o -o bin/Release/main -LC:/mingw64/lib -mwindows -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -lSDL2_ttf -s && start bin/Release/main
```


<h2>Screenshot</h2>
<img src="Image.PNG">
<img src="lose.PNG">
