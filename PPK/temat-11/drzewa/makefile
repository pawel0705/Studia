
 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=


__ : main
	./main   
	   	   
main : main.o drzewo.o debug_new.o static_mem_pool.o mem_pool_base.o bool_array.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
	            
main.o : main.cpp 
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 
	
drzewo.o : drzewo.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
		
		
	# kompilacja biblioteki wykrywajacej wycieki pamieci		
debug_new.o : ../../memory-leaks/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 
	
static_mem_pool.o : ../../memory-leaks/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

mem_pool_base.o : ../../memory-leaks/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

bool_array.o : ../../memory-leaks/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 	
	
clear :
	rm *.o
	rm main	
	

