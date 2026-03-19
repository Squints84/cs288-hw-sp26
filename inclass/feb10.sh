#!/bin/bash
ranks=(2 3 4 5 6 7 8 9 10 'jack' 'queen' 'king' 'ace')
suits=('clubs' 'spades' 'diamonds' 'hearts')
rank_length=${#ranks[@]}
suit_length=${#suits[@]}

random_rank=$((RANDOM%rank_length))
random_suit=$((RANDOM%suit_length))

echo "${ranks[random_rank]} of ${suits[random_rank]}"

