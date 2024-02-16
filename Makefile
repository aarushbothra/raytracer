CXX=g++
CXXFLAGS= -std=c++11 -g

.DEFAULT_GOAL := all
all: raytracer1a

raytracer1a: main.o Input.o Output.o RayCast.o Ray.o Sphere.o
	make deletePrevious
	$(CXX) $(CXXFLAGS) main.o Input.o Output.o RayCast.o Ray.o Sphere.o -o raytracer1a 

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o 
	
Ray.o: src/Ray.cpp src/Ray.h
	$(CXX) $(CXXFLAGS) -c src/Ray.cpp -o Ray.o 

Output.o: src/Output.cpp src/Output.h
	$(CXX) $(CXXFLAGS) -c src/Output.cpp -o Output.o 

Input.o: src/Input.cpp src/Input.h
	$(CXX) $(CXXFLAGS) -c src/Input.cpp -o Input.o 

RayCast.o: src/RayCast.cpp src/RayCast.h
	$(CXX) $(CXXFLAGS) -c src/RayCast.cpp -o RayCast.o 

Sphere.o: src/Sphere.h src/Sphere.cpp
	$(CXX) $(CXXFLAGS) -c src/Sphere.cpp -o Sphere.o 



	

.PHONY: all clean

deletePrevious:
	rm -f raytracer1a

postClean:
	rm -f *.o

clean:
	rm -f *.o raytracer1a *.ppm