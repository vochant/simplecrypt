# Simplecrypt
SIMPLECRYPT (Mirekintoc's LLAR) is a C++ based LLAR solution. LLAR is a definition for custom archives, not a project. Everyone can make himself's code and formatting for it. Simplecrypt is the first project of LLAR, and its code is 0x00000000.

The structure of LLAR is just like this:
```
4 Bytes  | String "LLAR"
4 Bytes  | DWORD Code, from 0x00000000 to 0xffffffff
1 Byte   | Length of the name of the solution
Not fixed| The name of the solution

8 Bytes  | The length of filename #1
Not fixed| Filename #1
8 Bytes  | The length of the main part of the data of file #1
8 Bytes  | The length of filename #2
...
8 Bytes  | The length of the main part of the data of file #N-1
8 Bytes  | The length of filename #N
Not fixed| Filename #N
8 Bytes  | The length of the main part of the data of file #N

1 Byte   | 0x7F
Not fixed| The data of file #1
Not fixed| The data of file #2
...
Not fixed| The data of file #N
```

As for SIMPLECRYPT, the archive's size will be `The count of files` \* 272 + `The sum of lengths of the names of files` + 20.

Because of the size of classes in the source code, you must give enough stack size to the program. Use this command:
```shell
g++ -O2 llarm.cpp -Wl,--stack=256000000 -o llarm.exe
g++ -O2 simpllar.cpp -Wl,--stack=256000000 -o simpllar.exe
```
Or use compile.bat (Only for Windows).

Use `llarm <archive> [d|e] <optional: file list>` to process an archive.

 - `llarm <archive> e` will make an empty archive.
 - `llarm <archive> e <file1> <file2> ...` will make an archive with file1, file2, ...
 - `llarm <archive> d` will extract all the files from the archive.
 - `llarm <archive> d <file1> <file2> ...` will extract file1, file2, ... from the file.

 - `simpllar <file>` will make an archive with single file. (The extension name of the archive cannot be `.llar`)
 - `simpllar <file1> <file2>` will make an archive with file1, file2, ...
 - `simpllar <archive>` will extract all the files from the archive. (The extension name of the archive must be `.llar`)
