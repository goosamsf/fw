### fw(Frequency of Word) 
fw is a program that can count each word present in a file or a set of files. 
It counts the word in a file and order them in descenting order by word's
frequency and if tie occurs, the word with alphabet coming later takes the
precedence. For example, when 10 apple is compared with 10 banana, "10 banana"
takes the priority.

### Usage
```
fw [-n num ] [ file1 file2 ... ]
    --- ---
    where num is number that represent top-n and file1,2 ... are file name.
    --- ---
``` 
fw can be executed in one of followings.
1. fw -n 10 file1.txt
2. fw file1.txt
3. fw -n 10
4. fw 

It's mainly when "-n num" is specified and it isn't. And when file name is
specified and it isn't.
    - When "-n num" is specified, it means list only top-num words out of all
words that was counted by fw.
    - When "-n num" is not specified, top-num is set to 10.
    - When file name is specified, it opens and read using those file names.
    - When file name is NOT specified, it takes standard input from user.

### How would you test this program with? 
- In another word, how can you trust this program? how can you make sure fw
count the frequency of word RIGHT? 

- We are testing with a linux utility program that has been known as
"Trustworthy". Consider following. Let's say we ran our program with a
larg text file called "large_text.txt" The way I get reference output is
following.

```bash 

tr -cs 'A-Za-z' '\n' < large_text.txt | tr 'A-Z' 'a-z' | sort | uniq -c | sort -nr > ref_output.txt

```
And for "n-specific" use case, you can use another utility called "head -n num".
By comparing many ref_output*.txt. fw's overall quality becomes PERFECT.

### Way of generating TEXT file
I am thinking of way of generating really large sized text file.
This is another side project for me. My goal is to test fw with very very large
text file. Because the program written in C is pretty fast regardless of how
efficiently being written. My goal is to increase the size of text file, making
it take about 5 ~ 10 seconds and then gives some optimization. From the
computation that takes about 1 second to the computation that takes 0.5 second
is huge improvement but I feel like it is not impressive thing to do.

##### Options of generating TEXT file
1. Fortune
The easiest way to do this is to use bash's for loop and well-known utility
program called Fortune. Fortune generates random joke, quote etc from its'
precompiled database.

```
    for ((i = 0; i <= 10000; i++)); do
      echo "$i th generation..."
      fortune >> ~/bigtext.txt 
    done
```
The problem is this method is extreamly slow. Taking more than a minute to
execute 10000 iterations. 





