![Built with love](http://forthebadge.com/images/badges/built-with-love.svg)
![Made with C++](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)
# The Super Tiny Parser

Inspired by [The Super Tiny Compiler](https://github.com/jamiebuilds/the-super-tiny-compiler).  
  
A tiny recursive-descent parser which uses syntax-directed translation to convert arithmetic infix expressions (+,-,*,/) into postfix notation, with friendly error messages.

---

Please refer to the comments in `parser.hpp` for further understanding.
  
### Prerequisites
- g++

### Installation
```
git clone https://github.com/coderick14/TheSuperTinyParser.git
cd TheSuperTinyParser
g++ -std=c++14 parser.hpp main.cpp -o parser
./parser
```
