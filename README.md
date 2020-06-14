# tolocal
A real time character set conversion filter. This is useful to allow programs like telnet to display ANSI graphics using characters from code page 437 (the IBM DOS character set) on screens setup to display UTF8 characters. It can also be used with programs like Nethack to allow it to display extended characters on a UTF-8 console. It requires libiconv, which most ix systems have installed as default. So far I have tested this on Linux and Mac, but it should build on Windows also using cygwin.

To build, copy either Makefile.macosx or Makefile.linux to Makefile and then type "make", then to install type "make install".
