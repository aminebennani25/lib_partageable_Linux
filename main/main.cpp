
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;
	void *handle1;
	void *handle2;
	
	handle1 = dlopen(argv[1], RTLD_LAZY);
	if(!handle1){
		std::cout << stderr << "Error Open Library Composant1.so: " <<dlerror()<<std::endl;
		return EXIT_FAILURE;
	}
	
	handle2 = dlopen(argv[2], RTLD_LAZY);
	if(!handle2){
		std::cout<<stderr<<" Error Open Library Composant2.so: "<<dlerror()<<std::endl;
		return EXIT_FAILURE;
	}
	
	dlerror();
	
	int (*composant1)(int, int) = (int (*)(int, int))dlsym(handle1, "composant1");
	if (!composant1){
		std::cout<<stderr<<" Error Symbol 1: "<<dlerror()<<std::endl;
		dlclose(handle1);
		return  EXIT_FAILURE;
	}
	
	int (*composant2)(int, int) = (int (*)(int, int))dlsym(handle2, "composant2");
	if(!composant2){
		std::cout<<stderr<<" Error Symbol 2: "<<dlerror()<<std::endl;
		dlclose(handle2);
		return EXIT_FAILURE;
	}

	int valeur1;
	int valeur2;
	
	valeur1=composant1(data1,data2);
	valeur2=composant2(data1,data2);
	
	char *(*versionComposant1)(void) = (char *(*)(void))dlsym(handle1, "getComposant1Version");
	if (!versionComposant1){
		std::cout<<stderr<<" Error Symbol Composant1 Version: "<<dlerror()<<std::endl;
		dlclose(handle1);
		return EXIT_FAILURE;
	}

	std::cout << versionComposant1() << std::endl;
	std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;

	dlclose(handle1);
	dlclose(handle2);

}
