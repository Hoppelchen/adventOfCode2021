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

day4: src/day3.cpp
	g++ -g -Wall -o aoc src/day4.cpp

day4_2: src/day4_2.cpp
	g++ -g -Wall -o aoc src/day4_2.cpp

clean: 
	$(RM) aoc