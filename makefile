# build 
day1: src/day1.cpp
	g++ -g -Wall -o aoc src/day1.cpp

day1_2: src/day1_2.cpp
	g++ -g -Wall -o aoc src/day1_2.cpp

day2: src/day2.cpp
	g++ -g -Wall -o aoc src/day2.cpp

day2_2: src/day2_2.cpp
	g++ -g -Wall -o aoc src/day2_2.cpp

day3: src/day3.cpp
	g++ -g -Wall -o aoc src/day3.cpp

day3_2: src/day3_2.cpp
	g++ -g -Wall -o aoc src/day3_2.cpp

day4: src/day4.cpp
	g++ -g -Wall -o aoc src/day4.cpp

day4_2: src/day4_2.cpp
	g++ -g -Wall -o aoc src/day4_2.cpp

day5: src/day5.cpp
	g++ -g -Wall -o aoc src/day5.cpp

day5_2: src/day5_2.cpp
	g++ -g -Wall -o aoc src/day5_2.cpp

day6: src/day6.cpp
	g++ -g -Wall -o aoc src/day6.cpp

day6_2: src/day6_2.cpp
	g++ -g -Wall -o aoc src/day6_2.cpp

day7: src/day7.cpp
	g++ -g -Wall -o aoc src/day7.cpp

day7_2: src/day7_2.cpp
	g++ -g -Wall -o aoc src/day7_2.cpp

day8: src/day8.cpp
	g++ -g -Wall -o aoc src/day8.cpp

day8_2: src/day8_2.cpp
	g++ -g -Wall -o aoc src/day8_2.cpp

day9: src/day9.cpp
	g++ -g -Wall -o aoc src/day9.cpp

day9_2: src/day9_2.cpp
	g++ -g -Wall -o aoc src/day9_2.cpp

day10: src/day10.cpp
	g++ -g -Wall -o aoc src/day10.cpp

day10_2: src/day10_2.cpp
	g++ -g -Wall -o aoc src/day10_2.cpp

clean: 
	$(RM) aoc