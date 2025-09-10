#!/bin/bash
# Program to find the largest of the given array of numbers

echo "Enter the size of the array: "
read n
declare -A arr
echo "Enter the elements of the array: "
for ((i=0; i<n; i++))
do
    read arr[$i]
done
max=${arr[0]}
for ((i=1; i<n; i++))
do
    if [[ $max < ${arr[$i]} ]]
    then
            max=${arr[$i]}
    fi
done

echo "The largest of the given numbers is $max"







#!/bin/bash
echo -n "Enter number of elements: "
read n
echo -n "Enter $n elements: "
for ((i=0;i<n;i++))
do
  read numbers[$i]
done
largest=${numbers[0]}
for num in ${numbers[@]}
do
  if [ $num -gt $largest ]
  then
    largest=$num
  fi
done
echo "$largest"




echo "Enter the size of the array: "
read n
echo "Enter the elements of the array: "
for ((i=0; i<n; i++))
do
    read arr[$i]
done

max=${arr[0]}
for ((i=1; i<n; i++))
do
    if [ ${arr[$i]} -gt $max ]   # ✅ numeric comparison
    then
        max=${arr[$i]}
    fi
done

echo "The largest of the given numbers is $max"
