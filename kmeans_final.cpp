#include "windows.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <stdexcept> // std::runtime_error

using namespace std;

#define square(x) ((x)*(x))

struct point2d {
public: 
	double x,y;
	int cluster; 	// clusters
};


struct color{
public: 
	float r,g,b;	//colores para graficar
};

int k;
point2d * centroide;
point2d * circumcenter;
color* clustercolor;
point2d * set;
int n;
int *nb, *nbc;


void init()
{
	int i;
	///Número de registros(filas) que se trabajaran
	n=99998;		
	///Array de todos las filas del Dataset
	set=new point2d[n];
	
	k=10;
	centroide=new point2d[k];
	clustercolor=new color[k];
	nb=new int[k];
	nbc=new int[k];
	
	ifstream infile("sample2.txt");
	//cout<<"Abriendo el archivo csv"<<endl;
	
	if(!infile.is_open()) throw std::runtime_error("Could not open file");
	
	vector<string> row; 
	string line, word, temp;
	long long cont = 0;
	double start_lon, start_lat;
	string str_row, str_col;
	vector<pair<float,float>> dataset(n);
	for(int i = 0; getline(infile, str_row); ++i){
		stringstream ss(str_row);
		//cout<<str_row<<endl;
		cont++;
		for(int j = 0; getline(ss,str_col,','); ++j){
			if(j == 0){
				start_lon = stod(str_col);
			}
			if(j == 1){
				start_lat = stod(str_col);
			}
			//cout<<str_col<<endl;	
		}
		pair<float,float> pair_xd(start_lon,start_lat);
		//p.first = start_lon;
		//p.second = start_lat;
		//cout<<"D: "<<start_lon<<" "<<start_lat<<endl;
		dataset[i]= pair_xd;
	}	
	//cout<<"SET: "<<set[0].x<<" "<<set[0].y<<endl;
	//cout<<"SET: "<<set[99996].x<<" "<<set[99996].y<<endl;
	//cout<<"DATASET: "<<dataset[0].first<<" "<<dataset[0].second<<endl;

	
	// Uniform distribution
	for(i=0;i<n;i++)
	{
		//set[i].x=(float)rand()/(float)RAND_MAX;
		//set[i].y=(float)rand()/(float)RAND_MAX;
		//set[i].x = fabs(dataset[i].first);
		//set[i].y = fabs(dataset[i].second);
		set[i].x = dataset[i].first;
		set[i].y = dataset[i].second;
		//cout<<"FA: "<<fabs(dataset[i].first)<<"-"<<fabs(dataset[i].second)<<endl;
		set[i].cluster=0;
	}
	
	
	for(i=0;i<k;i++)
	{
		centroide[i]=set[rand()%n];
		clustercolor[i].r=(float)rand()/(float)RAND_MAX;
		clustercolor[i].g=(float)rand()/(float)RAND_MAX;
		clustercolor[i].b=(float)rand()/(float)RAND_MAX;
	}
	infile.close();
	//cout<<"GA TERMINO PE GA y en total hay "<<cont<<" filas"<<endl;
}
void init_aleatorios(int cantidad_n, int cantidad_c)
{
	int i;
	n=cantidad_n;
	set=new point2d[n];
	k=cantidad_c;
	centroide=new point2d[k];
	clustercolor=new color[k];
	nb=new int[k];
	nbc=new int[k];
	
	for(i=0;i<n;i++) {
		set[i].x=(float)rand()/(float)RAND_MAX;
		set[i].y=(float)rand()/(float)RAND_MAX;
		set[i].cluster=0;
	}
	
	for(i=0;i<k;i++) {
		centroide[i]=set[rand()%n];
		clustercolor[i].r=(float)rand()/(float)RAND_MAX;
		clustercolor[i].g=(float)rand()/(float)RAND_MAX;
		clustercolor[i].b=(float)rand()/(float)RAND_MAX;
	}
}
void KMeansAssign() {
	int i,j,winner;
	double dist,distmin;
	for(i=0;i<n;i++) {
		distmin=1.0e8;
		for(j=0;j<k;j++) {
			dist=sqrt(square(set[i].x-centroide[j].x)+square(set[i].y-centroide[j].y));
			if (dist<distmin) {distmin=dist; winner=j;}
		}
		set[i].cluster=winner;
	}
	
}

void KMeansCluster() {
	int i,j,cl;
	
	for(j=0;j<k;j++)
	{
		nb[j]=0;
		centroide[j].x=centroide[j].y=0;
	}
	
	for(i=0;i<n;i++)
	{
		cl=set[i].cluster;
		centroide[cl].x+=set[i].x;
		centroide[cl].y+=set[i].y;
		nb[cl]++;
	}
	
	nbc[0]=0;
	for(j=0;j<k;j++)
	{
		if (j>0) {nbc[j]=nbc[j-1]+nb[j];}
		if (nb[j]>0) {centroide[j].x/=nb[j];centroide[j].y/=nb[j];}
		cout <<"Class "<<j<<" "<<nb[j]<<" "<<centroide[j].x<<" "<<centroide[j].y<<" ["<<nbc[j]<<"]"<<endl;
		nb[j]=0;
	}
	
}

void disp( void ) {
	glClearColor(1 , 1 , 1 , 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0f);
	//glPointSize(18.0f);
	
	
	glBegin(GL_POINTS);
	
	for(int i=0;i<n;i++)
	{
		int cl=set[i].cluster;
		glColor3f(clustercolor[cl].r,clustercolor[cl].g,clustercolor[cl].b);
		glVertex2f(set[i].x,set[i].y);
	}
	glEnd();
	
	// centroides
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for(int i=0;i<k;i++)
	{
		glColor3f(clustercolor[i].r,clustercolor[i].g,clustercolor[i].b);
		glVertex2f(centroide[i].x,centroide[i].y);
	}
	glEnd();
	
	glFlush();
	glutSwapBuffers();
	
	
}


void key(unsigned char key , int x , int y) {
	printf("Key = %c\n" , key);
	
	if (key==' ') {
		KMeansAssign();
		KMeansCluster();
		disp();
	 }
}



int main(int argc, CHAR* argv[])
{
	cout<<"K-means clustering."<<endl;	
	glutInit(&argc , argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1500, 800);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("k-Means clustering. ");
	glutDisplayFunc(disp);
	glutKeyboardFunc(key);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 , 1 , 0 , 1 , -1 , 1);
	//glOrtho(0.000 , 1.000 , 0.000 , 1.000 , -1.000 , 1.000);
	glMatrixMode(GL_MODELVIEW);
	
	cout<<"                                                  "<<endl;
	cout<<" | |   _   o       _    _   _  o   _|   _    _|   "<<endl;
	cout<<" |_|  | |  |  |/  (/_  |   _>  |  (_|  (_|  (_|   "<<endl;
	cout<<"  _                                               "<<endl;
	cout<<" /    _.  _|_   _/  |  o   _   _                  "<<endl;
	cout<<" |_  (_|   |_  (_)  |  |  (_  (_|                 "<<endl;
	cout<<"  __               _                              "<<endl;
	cout<<" (_    _    _     |_)   _   |_   |   _            "<<endl;
	cout<<" __)  (_|  | |    |    (_|  |_)  |  (_)           "<<endl;
	cout<<"                                                  "<<endl;
	
	cout<<"Eliga alguna de las siguientes opciones"<<endl;
	cout<<"Opcion 1: K-Means a partir del dataset .csv como entrada"<<endl;
	cout<<"          que son 10000 puntos con 10 centroides.       "<<endl;
	cout<<"Opción 2: K-Means a partir de números aleatorios con una"<<endl;
	cout<<"          determinada cantidad de puntos y centroides.  "<<endl;
	cout<<"Ingrese la opcion: ";
	int choice;
	cin >> choice;
	switch(choice){
	case 1: 
		init();
		break;
	case 2:
		int c1,c2;
		cout<<"Ingrese la cantidad de numeros aleatorios:";
		cin>>c1;
		cout<<"Ingrese la cantidad de Centroides:";
		cin>>c2;
		init_aleatorios(c1,c2);
		break;
	default:
		cout<<"No se ha seleccionado una opcion correcta, por favor compilar de nuevo el codigo"<<endl;
	}
	//init();
	KMeansAssign();
	
	glutMainLoop();
	
	return 0;
}


