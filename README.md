### README.md
# KONWERTER

Before anything: i've never taken english classes, and i'm open to critics, things may look wonky when reading.

<br>

---

## Purpose, uses & objectives

There's no pratical use to this currently, it's more of a "pipe" to motivate myself in learning about C ( i really like to work out in my foundations like programming logic before moving on to more complex stuff ) alone, currently it doesn't do anything other common libraries wouldn't be able to and *probably* in a less efficient way. One of the main objectives was to use as little libraries as i could, and set my own methods (functions) when needed, i'd guess that would be a huge waste of time in a professional occasion but i do consider it something good when it comes to learning. (hope i'm right, there's also the possibility that there are better things to pour time in than this)

This has also been of great help for me to get used to code editors like VIM ( I **had** no idea why people loved it so much, kinda do now, i'm not a huge fan of using the mouse to navigate) after i've installed Linux. So yeah it's more of a train than a applicable program.

I've stated that there's *"no pratical use to this currently"*, so i am implying that i plan to work it out to the point it becomes somewhat useful, maybe some sort of encoding based on the same idea numeric systems have.

<br>

---
## FUNCTIONS

There was a time i forgot about details in Konwerter functions because i've gotten busy with other stuff ( for a few months ), and it's a great example of how difficult it may get to read through an undocumented code, specially when you've not taken part in it's development.

Should also mention that test.c is only a code to test, prepare and solve code before adding changes to Konwerter, i've decided it's better to do that, mostly because the main code gets harder to test as it gets bigger and bigger.

<br>

---
### cmpStr

>```int cmpStr(char str1[], char str2[]) ```

This method is a not - so - great (does it job though) string comparing tool, better string manipulation functions are listed in string.h library, but as mentioned before i've got reasons to spend my time doing similar methods myself.

* Technical info
  - It returns an integer pointing out if the first string is equal to the second, 0 being true and 1 false (i've only noticed it now that 0 being true and 1 false is completly contradictory, i'll fix that in the future.. sowwy)
  - It compares both strings until the first one reaches it end, defined as '\0', or null, so it's important to highlight (MOLEQUE O ADILson METEU sALIENTAR NA MINHA CABEÇA) that it shouldn't work with integers (as it can't hold NULL value) or char arrays with different end-points.
  - As per above, since the comparing ends at the NULL of the first string, it's possible that it results true even if the second one isn't exactly equal, but only has the same match of characters until the end of the first string (impliying that it's longer)

<br>

---
### scanner

>```void *scanner(char flag[], FILE *stdin)```

This is the newer readInput, not being used (As the konwerter is not compatible with it currently) until it is fully functional, i'm going to refrain to speak about it's technical info since it's bound to change.

It should be able to read from files or keyboard inputs, in a way that it's possible to write down its value in both integer or char pointers.

<br>

---

### Main function

It doesn't need much information, it's simply a function used to start out the program and communicate with the client.

<br>

---
## ARITHMETICS

Simple mathematics that doesn't need much explanation.

<br>

---
### podniesc

>```podniesc(int num, int i)```

Basically a raise function in the mathematical sense, i'm not so sure what the correct translation should be, but it works perfectly with positive and non-floats exponents.

It is possible to make it work with floats, but it's not needed as of now, since there's no need to bother the CPU with datatypes we don't really need.

<br>

---
### lg

>```lg(int base, int num)```

A logarithm function under the same circumstances of the function above, it doesn't work well with floats and always return the logarithm rounded down.

It's used to find out the size of integers by applying the logarithm of ten, but it can also serve other purposes in other types of codes. 

THERE ARE OTHER FUNCTIONS DISPLAYE

