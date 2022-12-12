# Flight-management-system

A flight-ticket management application that can help users search for tickets based on a key combination of the company name and flight number. The application allows users to insert and read information about flight tickets through its interface or an input text file. It also supports deletion of ticket records and other management features. The program is implemented using object-oriented programming principles and appropriate data structures, including Hash Tables with separate chaining to handle collisions.


#Hash Functions performance comparison:

#1. Division method:

Description: The division method is a simple hash function that calculates the hash value of a key by summing the ASCII values of the characters in the key and then taking the remainder when the sum is divided by the size of the table.

Design: To implement the division method, we first initialize a variable hash to 0. We then iterate over each character in the key and add its ASCII value to the hash variable. Finally, we take the remainder of the hash divided by the size of the table and return the result as the hash value of the key.

Evaluation results:
Dataset file 1K: 394
Dataset file 10K: 1767
Dataset file 100K: 1803
Average number of collisions: 1321

#2. Multiplication method:

Description: The multiplication method is a hash function that calculates the hash value of a key by multiplying the ASCII values of the characters in the key together and then taking the remainder when the product is divided by the size of the table.

Design: To implement the multiplication method, we first initialize a variable hash to 1. We then iterate over each character in the key and multiply its ASCII value by the hash variable. Finally, we take the remainder of the hash divided by the size of the table and return the result as the hash value of the key.

Evaluation results:
Dataset file 1K: 807
Dataset file 10K: 2359
Dataset file 100K: 2399
Average number of collisions: 1855

#3. cyclic shift method

Description: The cyclic shift method is a hash function that calculates the hash value of a key by shifting the bits of the sum of the ASCII values to the left and then taking the remainder when the shifted value is divided by the size of the table.
Design: To implement the cyclic shift method, we first initialize a variable hash to 0. We then iterate over each character in the key and add its ASCII value to the hash variable. Next, we shift the bits of hash to the left by 4 places. Finally, we take the remainder of the hash divided by the size of the table and return the result as the hash value of the key.

Evaluation results:
Dataset file 1K: 240
Dataset file 10K: 1190
Dataset file 100K: 1215
Average number of collisions: 881

#4. Summation method:

Description: The summation method is a hash function that calculates the hash value of a key by summing the ASCII values of the characters in the key and then returning the sum itself as the hash value.

Design: To implement the summation method, we first initialize a variable hash to 0. We then iterate over each character in the key and add its ASCII value to the hash variable. Finally, we return the value of hash as the hash value of the key.

Evaluation results:
Dataset file 1K: 396
Dataset file 10K: 1767
Dataset file 100K: 1803
Average number of collisions: 1322

#5. Simple Hash Function using operators

Description: The function takes a string as input and uses a simple mathematical formula to calculate a hash code for the string. The hash code is calculated by iterating over each character in the string and adding a weighted value to a running total. The character's value is first converted to an unsigned integer and then multiplied by 33 before being added to the total. Finally, the value of the character 'a' is subtracted from the total.

Design: The function then returns the calculated hash code as the output. This hash code can be used to quickly identify the unique elements in a dataset by assigning each element a unique numerical value.

Evaluation results:
Dataset file 1K: 371
Dataset file 10K: 1714
Dataset file 100K: 1750
Average number of collisions: 1278

#6. Polynomial method:

Description: The polynomial method is a hash function that calculates the hash value of a key
by treating the key as a polynomial and then evaluating the polynomial at a given point.

Design: To implement the polynomial method, we first need to choose a point x at which the polynomial will be evaluated. This point should be chosen such that it is relatively prime to the size of the table (i.e. the greatest common divisor of x and the size of the table should be 1).
Once we have chosen a value for x, we can implement the polynomial method as follows:

1. Initialize a variable hash to 0.
2. Iterate over each character in the key and add its ASCII value to the hash variable.
3. Raise x to the power of the current index in the key and multiply the result by the value of
the hash.
4. Repeat steps 2 and 3 until all characters in the key have been processed.
5. Take the remainder of the hash divided by the size of the table and return the result as
the hash value of the key.

Evaluation results:
Dataset file 1K: 0
Dataset file 10K: 39
Dataset file 100K: 40
Average number of collisions: 26

In conclusion, the polynomial hash function appears to be better than the other methods evaluated in this study. The polynomial method had the lowest average number of collisions across the dataset files, indicating that it is more effective at generating unique hash values for the keys. Additionally, the polynomial method has the added advantage of being able to handle long keys more efficiently than the other methods. This makes it a good choice for applications where the keys may vary in length.
