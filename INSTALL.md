Installation currently only works with WSL (possibly might work with msys2 or Cygwin).

Follow the instructions at https://github.com/pret/pokeemerald/blob/c28d805/INSTALL.md , but stop at when you need to clone pokeemerald.

Then follow the instructions to install devkitpro https://github.com/pret/pokeemerald/blob/c28d805/INSTALL.md#devkitarms-c-compiler

Then clone the repo and cd into it
```
git clone https://github.com/luckytyphlosion/mmbn6-training-mode
cd mmbn6-training-mode
```

Acquire a copy of Mega Man Battle Network 6 Cybeast Falzar (USA) (SHA1: 0676ecd4d58a976af3346caebb44b9b6489ad099). Copy that file into the same folder as mmbn6-training-mode and rename it to bn6f.gba

Then run make.
```
make
```
