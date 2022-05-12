# Matchsticks puzzle solver
## puzzle

move k matchsticks to new places to get the maximum possible value.

## example

508 could be transformed into 999 by  moving 2 matchsticks.
but if you think you can get 1505 or even 51181. For now solver finds only 999.

## Algorithm

![7segment_display](https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/7_segment_display_labeled.svg/1024px-7_segment_display_labeled.svg.png)

We will represent each digit as vector of 7 values as follows (a, b, c, d, e, f, g) where [a-g] are 0 if segment is turned off and 1 if turned on. We can define distance between 2 digits as number of places with different value. The distance between 2 numbers would be the sum of the distances between corresponding digits.

example:

distance(12, 31) = distance(1, 3) + distance(2, 1) = 3 + 5 = 8 (distances between any digits could be precalculated)

Each move of a matchstick increases distance by 2 (removing it from one place increases distance by 1 and placing it to another place also increases distance by 1). Also the number of matchsticks should remain the same.

So the puzzle can be solved by the following algorithm. We can choose 'min' to be min number with the same number of digits as in n and 'max' as max number with the same number of digits. 

```python
solve(n, k):
  for i in range(max, min-1, -1):
    if(distance(i, n) == k*2 and number_of_mathcsticks(n) == number_of_mathcsticks(i))
      M = i
      break
  return M
```

## build

```
gcc solver.c -o solver
```
## run
```
./solver n k
```

