CXX=g++
CXXFLAGS= -std=c++11 -g
OUTFILE=raytracer1c
.DEFAULT_GOAL := all
all: $(OUTFILE)

$(OUTFILE): main.o Input.o Output.o RayCast.o Ray.o Sphere.o LightSource.o Face.o Material.o Intersection.o
	make deletePrevious
	$(CXX) $(CXXFLAGS) main.o Input.o Output.o RayCast.o Ray.o Sphere.o LightSource.o Face.o Material.o Intersection.o -o $(OUTFILE) 

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

LightSource.o: src/LightSource.h src/LightSource.cpp
	$(CXX) $(CXXFLAGS) -c src/LightSource.cpp -o LightSource.o 

Face.o: src/Face.h src/Face.cpp
	$(CXX) $(CXXFLAGS) -c src/Face.cpp -o Face.o 

Material.o: src/Material.h src/Material.cpp
	$(CXX) $(CXXFLAGS) -c src/Material.cpp -o Material.o 

Intersection.o: src/Intersection.h src/Intersection.cpp
	$(CXX) $(CXXFLAGS) -c src/Intersection.cpp -o Intersection.o 


.PHONY: all clean

deletePrevious:
	rm -f $(OUTFILE)

postClean:
	rm -f *.o

clean:
	rm -f *.o $(OUTFILE) *.ppm