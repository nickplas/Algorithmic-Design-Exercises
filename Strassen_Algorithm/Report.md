# Strassen Algorithm exercises

### Exercise 1

In the file called "generalization_strassen.c" in the "src" folder there is the implementation of the Strassen algorithm that works also for rectangular matrices. It converts a rectangular matrix into a square one and uses the "square_strassen" function that computes the product between two square matrices using the Strassen algorithm, to do that it converts any odd-sized square matrix into an even-sized one and computes the multiplication.

### Exercise 2

The function "improved_strassen" reduce the memory allocation by using only two S matrices and P matrices in the Strassen algorithm, results are shown in the following table:

|n	  |strassen 	 |improvement 	 |same |
|:--- | :---:      | :---:         |:---:|
|2^8  |0.017934 	 | 0.016514 	   |1    |
|2^9 	|0.265972 	 |0.102654 	     |1    |
|2^10 |	4.484700 	 |0.713857 	     |1    |
|2^11 |	92.318700  |4.895325 	     |1    |
|2^12 |	948.094965 |34.313622 	   |1    |
