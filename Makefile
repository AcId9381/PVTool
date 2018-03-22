IDIR=include
SDIR=src

all: pvtool pwks2wktool wctl2wktool

wctl2wktool: wctl2wktool.o wctl.o wctl.driver.o wctl.scanner.o wctl.parser.o
	g++ -std=c++17 -o wctl2wktool wctl2wktool.o wctl.o wctl.driver.o wctl.parser.o wctl.scanner.o

wctl2wktool.o: $(SDIR)/wctl/wctl2wktool.cpp $(IDIR)/wctl.hpp $(IDIR)/wctl.driver.hpp $(IDIR)/wctl.scanner.hpp
	g++ -std=c++17 -c $(SDIR)/wctl/wctl2wktool.cpp -I$(IDIR) -I$(SDIR)/wctl

pwks2wktool: pwks2wktool.o pwks.o pwks.driver.o pwks.scanner.o pwks.parser.o
	g++ -std=c++17 -o pwks2wktool pwks2wktool.o pwks.o pwks.driver.o pwks.parser.o pwks.scanner.o

pwks2wktool.o: $(SDIR)/pwks/pwks2wktool.cpp $(IDIR)/pwks.hpp $(IDIR)/pwks.driver.hpp $(IDIR)/pwks.scanner.hpp
	g++ -std=c++17 -c $(SDIR)/pwks/pwks2wktool.cpp -I$(IDIR) -I$(SDIR)/pwks

pvtool: main.o wctl.o wctl.scanner.o wctl.parser.o wctl.driver.o \
	pwks.o pwks.scanner.o pwks.parser.o pwks.driver.o epdg.o \
	assignment.o fpsolver.o
	g++ -std=c++17 -o pvtool main.o wctl.o wctl.scanner.o wctl.parser.o \
	wctl.driver.o pwks.o pwks.scanner.o pwks.parser.o pwks.driver.o \
	epdg.o assignment.o fpsolver.o

main.o : main.cpp $(IDIR)/wctl.driver.hpp $(IDIR)/pwks.driver.hpp $(IDIR)/epdg.hpp $(IDIR)/fpsolver.hpp \
	$(IDIR)/assignment.hpp $(IDIR)/pwks.hpp $(IDIR)/epdg.hpp
	g++ -std=c++17 -c main.cpp -I$(IDIR) -Isrc/wctl -Isrc/pwks

wctl.o : $(SDIR)/wctl/wctl.cpp $(IDIR)/wctl.hpp
	g++ -std=c++17 -c $(SDIR)/wctl/wctl.cpp  -I$(IDIR)

wctl.scanner.o : $(SDIR)/wctl/wctl.scanner.cc $(IDIR)/wctl.scanner.hpp
	g++ -std=c++17 -c $(SDIR)/wctl/wctl.scanner.cc  -I$(IDIR) -I$(SDIR)/wctl

wctl.parser.o : $(SDIR)/wctl/wctl.parser.cc $(SDIR)/wctl/wctl.parser.hh
	g++ -std=c++17 -c $(SDIR)/wctl/wctl.parser.cc  -I$(IDIR) -I$(SDIR)/wctl

wctl.driver.o : $(SDIR)/wctl/wctl.driver.cpp $(IDIR)/wctl.driver.hpp \
		$(IDIR)/wctl.hpp
	g++ -std=c++17 -c $(SDIR)/wctl/wctl.driver.cpp  -I$(IDIR) -I$(SDIR)/wctl

pwks.o : $(SDIR)/pwks/pwks.cpp $(IDIR)/pwks.hpp
	g++ -std=c++17 -c $(SDIR)/pwks/pwks.cpp  -I$(IDIR) -I$(SDIR)/pwks

pwks.scanner.o : $(SDIR)/pwks/pwks.scanner.cc $(IDIR)/pwks.scanner.hpp
	g++ -std=c++17 -c $(SDIR)/pwks/pwks.scanner.cc  -I$(IDIR) -I$(SDIR)/pwks

pwks.parser.o : $(SDIR)/pwks/pwks.parser.cc $(SDIR)/pwks/pwks.parser.hh
	g++ -std=c++17 -c $(SDIR)/pwks/pwks.parser.cc  -I$(IDIR) -I$(SDIR)/pwks

pwks.driver.o : $(SDIR)/pwks/pwks.driver.cpp $(IDIR)/pwks.driver.hpp
	g++ -std=c++17 -c $(SDIR)/pwks/pwks.driver.cpp  -I$(IDIR) -I$(SDIR)/pwks

epdg.o : $(SDIR)/epdg/epdg.cpp $(IDIR)/epdg.hpp $(IDIR)/pwks.hpp $(IDIR)/wctl.hpp
	g++ -std=c++17 -c $(SDIR)/epdg/epdg.cpp  -I$(IDIR)

assignment.o : $(SDIR)/epdg/assignment.cpp $(IDIR)/assignment.hpp
	g++ -std=c++17 -c $(SDIR)/epdg/assignment.cpp  -I$(IDIR)

fpsolver.o : $(SDIR)/epdg/fpsolver.cpp $(IDIR)/fpsolver.hpp \
	     $(IDIR)/assignment.hpp $(IDIR)/epdg.hpp
	g++ -std=c++17 -c $(SDIR)/epdg/fpsolver.cpp  -I$(IDIR)
