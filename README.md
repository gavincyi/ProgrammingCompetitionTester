# Programming Competition Tester

The project is a header-only library of a testing machine of generating randomized arrays.

The objective of the project is to check the values generated from different algorithms.

1. Generate a random vector.
2. Run the algorithms with the provided test cases.
3. Check if all values from algorithms are the same on randomized arrays.

## Why I start this project?

I participated a few programming contests and coding interviews. I find sometimes
it is not an obstacle to write a solution, but to write good test cases to confirm
the solution correct on 

1. Most cases, and
2. The boundary cases.

So I created this project on the way of my coding interview. (But after writing it, I
found I was incorrect on one of the questions in the last 15 minutes. Ironic.) Hope it
can benefit to other developers, especially those participating in coding interview in
Codility. I found most Codility platform coding interviews have only one test case and
you can never ensure you are absolutely correct.

## How to use?

1. First create your own project (quickly during your test/interview/contest/whatever1)
and import the header "TestMachine.hpp".

2. Create the machine by the following initial parameters.

    i) minSize, maxSize - The minimum and maximum size of the randomized arrays

    ii) minRange, maxRange - The minimum and maximum range of each element in the array

3. Insert your test cases by method "InsertTestCase".

4. Insert your algorithm by method "InsertAlgorithm"

5. Call method Run to run it!

## Questions

If you have any feedback (especially thank-you note if you can win an offer), please email me
by gavincyi at gmail dot com. Good luck and have fun! :)