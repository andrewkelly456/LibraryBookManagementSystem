# Project 4 Video Script — Library Book Management System

Target length: 6–12 minutes. Read directly from this, adjust wording to sound natural as you go.

---

## 1. Intro (~20 seconds)

"Hi, my name is Andrew Kelly, and this is my Project 4 submission for CSCI 350 — a Library Book Management System written in C++. In this video, I'll walk through my source code, demonstrate the menu-driven program, and then discuss C++'s paradigms, expressions and statements, function features, and its strengths and weaknesses."

---

## 2. Code Walkthrough (~4–5 minutes)

### a) The Book struct and global collection

"I started by defining a `Book` struct to hold each book's data — its ID, title, author, publication year, and number of copies available. Since we weren't allowed to use classes for this project, I stored all books in a global `vector` of `Book` structs, called `library`. Every function in this program reads from and modifies this one shared vector."

### b) Input validation helper

"Before getting into the menu operations, I want to point out one function I added: `getValidInt`. Early on, I noticed that if someone typed letters instead of a number, the program would break. So I wrote one function that asks for a number, and if the person types something that isn't a number, it just prints an error and asks again, until it gets a real number. Every place in my program that needs a number uses this same function, so I only had to write that fix once."

### c) Add Book — function overloading #1

"Next is `addBook`. I have two versions of this function sharing the same name — this is function overloading. The first version takes the book's fields individually — ID, title, author, year, and copies. The second version takes an already-built `Book` struct directly and just forwards its fields into the first version. Both versions check the existing collection for a duplicate ID before adding, and reject the operation if one is found."

### d) Display Books — function overloading #2

"`displayBooks` is overloaded three ways. Calling it with no arguments prints every book in the library. Calling it with an integer prints just the one book matching that ID. Calling it with a string searches by author instead. The compiler tells these apart purely by the parameter list, which is the core idea behind overloading."

### e) Update and Delete

"`updateBooks` takes a book ID plus new title, author, and year, searches the vector for a matching ID, and updates that entry in place. `deleteBook` does a similar search, and uses the vector's `erase` function to remove the matching entry. Both handle the case where the ID doesn't exist by printing an error instead of silently doing nothing."

### f) Search — pass-by-reference

"`searchBook` demonstrates passing a parameter by reference. It takes a book ID and a `bool` called `found`. Since `found` is passed by reference, whatever this function sets it to actually changes the variable back in `main`, not just a copy of it. So the function returns the book itself, and also uses `found` to tell the caller whether that book actually exists."

### g) Borrow and Return — default parameters

"Finally, `borrowBook` and `returnBook` both take a book ID and a `copies` parameter that defaults to 1. This is C++'s default parameter feature — if the caller only passes a book ID, the function assumes they mean one copy. If they pass a second argument, that value is used instead. I also added a check so a zero or negative number of copies gets rejected instead of corrupting the book's copy count."

### h) The menu loop

"All of this is tied together in `main`, which uses a `do-while` loop so the menu always displays at least once, and a `switch` statement to dispatch to the right operation based on the user's numeric choice. The loop keeps running until the user enters 0 to quit."

---

## 3. Live Demo (~2–3 minutes)

Walk through these live in the terminal, narrating as you go:

1. Compile and run the program.
2. **Add a book** (option 1) — show it succeed.
3. **Try adding the same ID again** — show the duplicate-ID rejection.
4. **Display all books** (option 2 → 1).
5. **Display by ID** and **display by author** (option 2 → 2 and 2 → 3).
6. **Update the book** (option 3) — show the fields change.
7. **Search for the book** (option 4) — show it returns correctly. Optionally search a nonexistent ID to show the "not found" case.
8. **Borrow a copy** (option 6) — show copies decrease. Try borrowing more copies than available to show that guard.
9. **Return a copy** (option 7) — show copies increase.
10. **Delete the book** (option 5) — show it's removed.
11. **Quit** (option 0).

---

## 4. Research and Discussion (~3–4 minutes)

### Paradigms

"C++ is a multi-paradigm language — it supports procedural programming, object-oriented programming, and even generic and some functional-style programming. For this project, I used it purely procedurally, since we weren't allowed to use classes. This meant organizing the program entirely around functions that operate on a shared global data structure, rather than bundling data and behavior together. It works fine at this scale, but as a program grows, keeping data and the functions that touch it separate can get harder to manage — which is part of the motivation for object-oriented programming."

### Expressions and Statements

"C++ gave me a wide set of statements to work with — if/else, switch, for loops, while loops, and do-while loops, along with the usual arithmetic, relational, and logical expressions. The switch statement was a perfect fit for the menu-driven design this project asked for. I don't think there's much that would've drastically simplified this project, though range-based for-loops could have made a couple of my loops slightly shorter. As for classes — yes, I think using classes and objects would have made this easier. I could have bundled each book's data with its own functions, avoided passing so many parameters around manually, and enforced validation automatically whenever a book's data changed."

### Functions, Parameters, and Overloading

"C++ gave me pass-by-value, pass-by-reference, default parameters, and function overloading, and all four were genuinely useful in this project. Overloading let me use the same function name — like `addBook` or `displayBooks` — for related operations that differ only in what they accept. Pass-by-reference let my `searchBook` function report back whether a book was found without needing a second return value. Default parameters simplified borrowing and returning a single copy without forcing the user to always specify a number. One feature from other languages that might have helped here is optional or named parameters, like Python has — that would let me skip specifying earlier parameters instead of needing a full default-parameter chain."

### Strengths and Weaknesses

"Based on writing this project, I'd say C++'s biggest strengths are performance and control — it gives you very direct control over memory and program behavior, and it's fast. It also has a massive ecosystem and decades of community support. The weaknesses I ran into firsthand were mostly around how manual everything is — for example, I had to build my own input validation from scratch to prevent bad input from crashing the program, something that just isn't an issue in higher-level languages. It's also easier to introduce subtle bugs in C++, like the infinite loop I hit early on from not resetting a failed input stream. Overall, I'd say C++ trades convenience for control and performance."

---

## 5. Closing (~10 seconds)

"That covers my Library Book Management System, the C++ concepts I used to build it, and my thoughts on the language overall. Thanks for watching."
