#!/bin/bash

ranks=(2 3 4 5 6 7 8 9 10 "jack" "queen" "king" "ace")
suits=("clubs" "spades" "diamonds" "hearts")

# to get random element of array first have to get random index
# and then access the element at the index

rank_length=${#ranks[@]}
suit_length=${#suits[@]}

rank_index=$(($RANDOM % rank_length))
suit_index=$(($RANDOM % suit_length))

echo ${ranks[rank_index]} of ${suits[suit_index]} 
