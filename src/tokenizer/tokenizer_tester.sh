#!/bin/bash

# Usage: ./tokenizer_tester
# To add more tests, update test variables below

################################################################################
##                             USEFUL VARIABLES                               ##
################################################################################

EXECUTABLE="tokenizer"
EXECUTABLE_PATH="."

TEST_COUNT=0
TEST_PASSED=0

## COLORS
################################################################################

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

## TITLE
################################################################################

TITLE="
🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥

🔥                                 MINI(s)HELL                                🔥

🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥 🔥
                                \e[2m(tester by nikito)\e[22m
"

################################################################################
##                                   TESTS                                    ##
################################################################################

# Tests are double arrays.
# First element of each array is the test ran, second element is expected output.
#
#TEST[0]="abc"
#RESULT[0]="[abc]"

################################################################################
##                                  HEADER                                    ##
################################################################################

# CHECK IF PROGRAM EXISTS, RUN MAKE IF IT DOES NOT
#if ! command -v ${PROGRAM_PATH}/${PROGRAM} >/dev/null;
#then
#  printf "push_swap not found in parent folder.\nCompiling push_swap...
#fi

## DISPLAY TITLE
clear -x # clears screen, equals to CTRL + L in Terminal
printf "${TITLE}"

echo
echo 🌈 Running make...
make

printf "
******************
* Starting tests *
******************
"

################################################################################
##                                   TESTING                                  ##
################################################################################

printf "\n\e[4mWord tokens\e[24m\n"

OUTPUT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "abc")
EXPECTED_OUTPUT="[abc]"
if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
  printf "${GREEN}OK${NC} "
 else
  printf "${RED}KO${NC} (Test returned <%s>)" "$OUTPUT"
fi

OUTPUT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "abc >>> |> <<<sqf vdd ")
EXPECTED_OUTPUT="[abc|>>|>|||>|<<|<|sqf|vdd]"
if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
   printf "${GREEN}OK${NC} "
 else
   printf "${RED}KO${NC} (${RED}Expected${NC} %s ${RED}returned${NC} %s)\n" "$EXPECTED_OUTPUT" "$OUTPUT"
fi

OUTPUT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "<<< a b c def ||>>> > ")
EXPECTED_OUTPUT="[<<|<|a|b|c|def|||||>>|>|>]"
if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
   printf "${GREEN}OK${NC} "
 else
   printf "${RED}KO${NC} (${RED}Expected${NC} %s ${RED}returned${NC} %s)\n" "$EXPECTED_OUTPUT" "$OUTPUT"
fi

echo
printf "\n\e[4mOperator tokens\e[24m\n"
echo No tests yet

printf "\n\e[4mQuoted tokens\e[24m\n"
OUTPUT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "abc \"coucou\" abc")
EXPECTED_OUTPUT="[abc|coucou|abc]"
if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
   printf "${GREEN}OK${NC} "
 else
   printf "${RED}KO${NC} (${RED}Expected${NC} %s ${RED}returned${NC} %s)\n" "$EXPECTED_OUTPUT" "$OUTPUT"
fi

echo
echo

#
#TEST_RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST[$i]}")
#  echo ${TEST_RESULT}

#for i in "${!TEST[@]}"
#do
#  TEST_RESULT=${${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST[$i]}"}
#  echo ${TEST_RESULT}
#    if [ "$TEST_RESULT" == "$RESULT[$i]" ]
#    then
#          printf "${GREEN}OK${NC} " # IF VARIABLE IS EMPTY, MEANS PROGRAM DID NOT RETURN ANYTHING AND IS OK
#         (( TEST_PASSED++ ))
#         (( TEST_COUNT++ ))
#    else
##          printf "${RED}Error${NC} (Test %s <%s> returned <%s>) " "$j" "${TEST_RETURNS_OPERATIONS[$j]}" "${RESULT}" # IF PROGRAM RETURNED SOMETHING, TEST FAILS AND SHOWS WHAT WAS TESTED
#          printf KO
#         (( TEST_COUNT++ ))
#    fi
#done
