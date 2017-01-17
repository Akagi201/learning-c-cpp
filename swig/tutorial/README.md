## Python

```
swig -python example.i
gcc -c -fpic `python-config --cflags` example.c example_wrap.c
gcc -shared example.o example_wrap.o -o _example.so
```

