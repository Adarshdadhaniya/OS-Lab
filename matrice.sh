#!/bin/bash

declare -A X
declare -A Y
declare -A Z

echo "Enter the elements of the first 3*3 matrix"
for((i=0;i<3;i++))
    do
        for((j=0;j<3;j++))
            do
                read X[$i,$j]
            done
    done

echo "Enter elements of the second 3*3 matrix"
for((i=0;i<3;i++))
    do
        for((j=0;j<3;j++))
            do
                read Y[$i,$j]
            done
    done

echo "The input matrices are:"
for((i=0;i<3;i++))
    do
        for((j=0;j<3;j++))
            do
                echo -ne "${X[$i,$j]} "
            done
        echo
    done
for((i=0;i<3;i++))
    do
        for((j=0;j<3;j++))
            do
                echo -ne "${Y[$i,$j]} "
            done
        echo
    done

echo "The resultant matrix is:"
for((i=0;i<3;i++))
    do
        for((j=0;j<3;j++))
            do
                Z[$i,$j]=$((X[$i,$j]+Y[$i,$j]))
                echo -ne "${Z[$i,$j]} "
            done
        echo
    done












#!/bin/bash
read -p "Enter rows and cols: " m n
declare -A m1
declare -A m2
declare -A res
echo "Enter elements of m1: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    read m1[$i,$j]
  done
done
echo "Enter elements of m2: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    read m2[$i,$j]
  done
done

for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    res[$i,$j]=$((m1[$i,$j]+m2[$i,$j]))
  done
done

echo "Result: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    echo -n "${res[$i,$j]} " 
  done
  echo
done