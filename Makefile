CXX=g++
CXXFLAGS=-Wall -ggdb
RM=rm -f

res : txt_to_morse.o morse_to_tab.o tab_to_txt.o morse_to_txt.o menu.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 

txt_to_morse.o : txt_to_morse.cpp
morse_to_tab.o : morse_to_tab.cpp
tab_to_txt.o : tab_to_txt.cpp morse_to_tab.h
morse_to_txt.o : morse_to_txt.cpp tab_to_txt.h
menu.o : menu.cpp txt_to_morse.h morse_to_txt.h
main.o : main.cpp menu.h

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	$(RM) test.o rpn_calc.o stack.o res