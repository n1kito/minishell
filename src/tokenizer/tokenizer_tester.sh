#!/bin/bash

# Usage: ./tokenizer_tester
# To add more tests, add them to the corresponding sections below.
# BEWARE: This tester needs the tokenizer main and token printer because it uses
# # the associated output format to check tokens.

################################################################################
##                             USEFUL VARIABLES                               ##
################################################################################

EXECUTABLE="tokenizer"
EXECUTABLE_PATH="."

TEST_COUNT=0
TEST_PASSED=0

## RETURNS
################################################################################

OK="[OK]"
KO="❌"

## COLORS
################################################################################

RED='\033[0;31m'
BRED='\033[1;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

################################################################################
##                                  HEADER                                    ##
################################################################################

## DISPLAY TITLE
clear -x # clears screen, equals to CTRL + L in Terminal

echo
echo "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░";
echo
echo "      ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    ";
echo "     ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    ";
echo "     ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    ";
echo "     ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    ";
echo "     ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒";
echo "     ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░";
echo "     ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░";
echo "     ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   ";
echo "            ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░";
printf "                            \e[2m(tester by nikito 🔥)\e[22m"

################################################################################
##                                RUNNING MAKE                                  ##
################################################################################

echo
echo
echo
printf "                      🌈 Running ${YELLOW}make${NC} on Tokenizer...\n"
make

################################################################################
##                                   TESTING                                  ##
################################################################################

echo
printf "${YELLOW}                         ┌┬┐┌─┐┬┌─┌─┐┌┐┌┬┌─┐┌─┐┬─┐   ${NC}\n";
printf "${YELLOW}                      **  │ │ │├┴┐├┤ ││││┌─┘├┤ ├┬┘ **${NC}\n";
printf "${YELLOW}                          ┴ └─┘┴ ┴└─┘┘└┘┴└─┘└─┘┴└─   ${NC}\n";

## Word tests
################################################################################

printf "\n \e[4mWord tokens\e[24m:\n "

TEST_WORD[0]="abc"
EXPECTED_OUTPUT_WORD[0]="[abc]"
TEST_WORD[1]="abc >>> |> <<<sqf vdd "
EXPECTED_OUTPUT_WORD[1]="[abc|>>|>|||>|<<|<|sqf|vdd]"
TEST_WORD[2]="<<< a b c def ||>>> > "
EXPECTED_OUTPUT_WORD[2]="[<<|<|a|b|c|def|||||>>|>|>]"

for i in "${!TEST_WORD[@]}"; # ITERATES THROUGH TESTS UNTIL THERE ARE NONE LEFT
do
  RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST_WORD[$i]}") # SETS TEST RESULT TO VARIABLE $RESULT
   if [ "$RESULT" = "${EXPECTED_OUTPUT_WORD[$i]}" ]; then # COMPARES RESULT WITH CORRESPONDING EXPECTED RESULT
      printf "${GREEN}${OK}${NC} " # IF RESULT MATCHES EXPECTED_OUTPUT, PRINT 'OK'
      (( TEST_PASSED++ ))
      (( TEST_COUNT++ ))
    else
      printf "${RED}${KO}${NC} ${RED}(ran${NC} %s ${RED}expected${NC} %s ${RED}returned${NC} %s${RED})${NC}\n" "${TEST_WORD[$i]}" "${EXPECTED_OUTPUT_WORD[$i]}" "$RESULT" # IF RESULTS DON'T MATCH, PRINT 'KO' ND SHOW TEST, EXPECTED OUTPUT AND RESULT
      (( TEST_COUNT++ ))
   fi
done

echo

## Word tests
################################################################################

printf "\n \e[4mOperator tokens\e[24m:\n "

TEST_OP[0]="abc>>"
EXPECTED_OUTPUT_OP[0]="[abc|>>]"
TEST_OP[1]="abc|>>"
EXPECTED_OUTPUT_OP[1]="[abc|||>>]"
TEST_OP[2]="abc>>> "
EXPECTED_OUTPUT_OP[2]="[abc|>>|>]"
TEST_OP[3]=" <<<<||ab|> > "
EXPECTED_OUTPUT_OP[3]="[<<|<<|||||ab|||>|>]"

i=0
for i in "${!TEST_OP[@]}"; # ITERATES THROUGH TESTS UNTIL THERE ARE NONE LEFT
do
  RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST_OP[$i]}") # SETS TEST RESULT TO VARIABLE $RESULT
   if [ "$RESULT" = "${EXPECTED_OUTPUT_OP[$i]}" ]; then # COMPARES RESULT WITH CORRESPONDING EXPECTED RESULT
      printf "${GREEN}${OK}${NC} " # IF RESULT MATCHES EXPECTED_OUTPUT, PRINT 'OK'
      (( TEST_PASSED++ ))
      (( TEST_COUNT++ ))
    else
      printf "${RED}${KO}${NC} ${RED}(ran${NC} %s ${RED}expected${NC} %s ${RED}returned${NC} %s${RED})${NC}\n" "${TEST_OP[$i]}" "${EXPECTED_OUTPUT_OP[$i]}" "$RESULT" # IF RESULTS DON'T MATCH, PRINT 'KO' ND SHOW TEST, EXPECTED OUTPUT AND RESULT
      (( TEST_COUNT++ ))
   fi
done

echo

## Quote tests
################################################################################

printf "\n \e[4mQuoted tokens\e[24m:\n "

TEST_QUOTES[0]="abc \"coucou\" abc"
EXPECTED_OUTPUT_QUOTES[0]="[abc|coucou|abc]"
TEST_QUOTES[1]="abc 'coucou>>||||||||\"\"pouet'abc"
EXPECTED_OUTPUT_QUOTES[1]="[abc|coucou>>||||||||\"\"pouet|abc]"

i=0
for i in "${!TEST_QUOTES[@]}"; # ITERATES THROUGH TESTS UNTIL THERE ARE NONE LEFT
do
  RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST_QUOTES[$i]}") # SETS TEST RESULT TO VARIABLE $RESULT
   if [ "$RESULT" = "${EXPECTED_OUTPUT_QUOTES[$i]}" ]; then # COMPARES RESULT WITH CORRESPONDING EXPECTED RESULT
      printf "${GREEN}${OK}${NC} " # IF RESULT MATCHES EXPECTED_OUTPUT, PRINT 'OK'
      (( TEST_PASSED++ ))
      (( TEST_COUNT++ ))
    else
      printf "\n${RED}${KO}${NC} ${RED}(ran${NC} %s ${RED}expected${NC} %s ${RED}returned${NC} %s${RED})${NC}\n" "${TEST_QUOTES[$i]}" "${EXPECTED_OUTPUT_QUOTES[$i]}" "$RESULT" # IF RESULTS DON'T MATCH, PRINT 'KO' ND SHOW TEST, EXPECTED OUTPUT AND RESULT
      (( TEST_COUNT++ ))
   fi
done

echo

## Env tests
################################################################################

printf "\n \e[4mEnvironment variable tokens\e[24m:\n "

TEST_ENV[0]="a b c fdfd\$coucou>>> d\"\"'lol'' \$coucou|test"
EXPECTED_OUTPUT_ENV[0]="[a|b|c|fdfd|\$coucou|>>|>|d|lol|\$coucou|||test]"

i=0
for i in "${!TEST_ENV[@]}"; # ITERATES THROUGH TESTS UNTIL THERE ARE NONE LEFT
do
  RESULT=$(${EXECUTABLE_PATH}/${EXECUTABLE} "${TEST_ENV[$i]}") # SETS TEST RESULT TO VARIABLE $RESULT
   if [ "$RESULT" = "${EXPECTED_OUTPUT_ENV[$i]}" ]; then # COMPARES RESULT WITH CORRESPONDING EXPECTED RESULT
      printf "${GREEN}${OK}${NC} " # IF RESULT MATCHES EXPECTED_OUTPUT, PRINT 'OK'
      (( TEST_PASSED++ ))
      (( TEST_COUNT++ ))
    else
      printf "${RED}${KO}${NC} ${RED}(ran${NC} %s ${RED}expected${NC} %s ${RED}returned${NC} %s${RED})${NC}\n" "${TEST_ENV[$i]}" "${EXPECTED_OUTPUT_ENV[$i]}" "$RESULT" # IF RESULTS DON'T MATCH, PRINT 'KO' ND SHOW TEST, EXPECTED OUTPUT AND RESULT
      (( TEST_COUNT++ ))
   fi
done

echo
echo

printf " \e[4mTests passed\e[24m: "
if [ ${TEST_PASSED} -eq ${TEST_COUNT} ]
then
  printf "✅ ${GREEN}${TEST_PASSED}/${TEST_COUNT}${NC}"
else
  printf "💀 ${BRED}${TEST_PASSED}${NC}/${TEST_COUNT}"
fi
echo
echo
echo "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░";
echo
