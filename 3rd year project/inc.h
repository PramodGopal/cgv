#pragma once
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<GL\glut.h>
using namespace std;
#define PI 3.142857
#define LNW 2

int Gtemp[20][20],edgetemp[20][2];

int costcoord[100][2] = { {45,260},{230,460},{120,350},{120,170},{230,40},{300,330},{450,345},{300,180},{480,170} };

char seq[2];
char buf[256][2];

//linkbreak
int link1, link2;
int ed[20][2], g1[20][20];


//flags
int fps = 100;
float x, y;
int flag = 0;
int fbuf = 0;

int ind = 0;

//linkbreak mode
int lnf = 0;

//buffermode
int pathbuf[100], destbuf, vert[10][2][2] = { {{10,510},{40,510}},{ { 10, 120 },{ 40,120 } }, { {410,510},{ 440,510 }},{ { 280,240 },{ 310,240 } },{ { 440,30 },{ 470,30 } },{ { 550,130 },{ 580,130 } } };
int fragcount=0,sta=1;

//mode of operation
int presentationmode = 1, normalmode = 0, interactivemode = 0, sourcemode = 0, linkbreakmode = 0,buffermode=0,helpmode=0;

int dest, S;

GLubyte linehcolor[3] = { 131,255,43 };
GLubyte srcnodecolor[3] = { 229, 199, 199 };
GLubyte destnodecolor[3] = { 224, 141, 40 };
GLubyte srctextcolor[3] = { 16, 232, 145 };


GLfloat node_rad = 30;
int n;
int cost[100][100];
int mypath[100][100], pathhighlight[100][100];
GLfloat x_packet_size = 25, y_packet_size = 25, h_length = 20;

GLfloat node_cord[10][2] = { { 60, 450 },{ 60, 60 },{ 380, 450 },{ 220, 270 },{ 380, 60 },{ 540, 270 } };
GLfloat packet_cord[20];

int V, edge[20][2], i, j, E = 0;
int G[20][20];

int packet1;
int path[50][50];
int sz[10];
int Bellman_Ford(const int G[20][20], int V, int E, int edge[20][2])
{
	int i, u, v, k, distance[20], parent[20], flag = 1, m = 0, dummy[20], j, size[6] = { 0 };
	for (i = 0; i<V; i++)
		distance[i] = 1000, parent[i] = -1;
	/*cout << "Enter source: ";
	cin >> S;*/
	distance[S - 1] = 0;
	for (i = 0; i<V - 1; i++)
	{
		for (k = 0; k<E; k++)
		{
			u = edge[k][0], v = edge[k][1];
			if (distance[u] + G[u][v] < distance[v])
				distance[v] = distance[u] + G[u][v], parent[v] = u;
		}
	}
	for (k = 0; k<E; k++)
	{
		u = edge[k][0], v = edge[k][1];
		if (distance[u] + G[u][v] < distance[v])
			flag = 0;
	}
	if (flag)
		for (i = 0; i<V; i++)
			printf("Vertex %d -> cost = %d parent = %d\n", i + 1, distance[i], parent[i] + 1);
	for (i = 0; i<V; i++) { dummy[i] = parent[i] + 1; }
	//for(i=0;i<V;i++){printf("\ndummy= %d , ",dummy[i]);}
	for (i = 0; i<V; i++)
	{
		m = 0;
		path[i][m++] = i + 1;
		size[i]++;
		if ((parent[i] + 1) == S)
		{
			path[i][m++] = S; size[i]++;
		}
		else if ((parent[i] + 1) == 0)
		{
			path[i][m++] = 0; size[i]++;
		}
		else {
			while (1)
			{

				path[i][m++] = dummy[i];
				size[i]++;
				if (dummy[i] == S)break;
				dummy[i] = dummy[dummy[i] - 1];
			}
			for (j = 0; j<V; j++) { dummy[i] = parent[i] + 1; }
		}
	}
	for (i = 0; i<V; i++)
	{
		printf("\npath %d:  ", i + 1);
		for (j = 0; j<size[i]; j++)
			printf("%d<---", path[i][j]);
	}
	for (i = 0; i < V; i++)
		sz[i] = size[i];
	m = 0;
	for (i = 0; i<V; i++)
	{
		m = 0;
		for (j = size[i] - 1; j >= 0; j--) {
			mypath[i][m] = path[i][j];
			pathhighlight[i][m++] = path[i][j];
		}
	}
	printf("\n\nMYPATH\n\n");
	for (i = 0; i<V; i++)
	{
		printf("\npath %d size=%d:  ", i + 1, sz[i]);
		for (j = 0; j<size[i]; j++)
			printf("%d\t", mypath[i][j]);
	}
	return flag;
}

/*saved*/
/*glBegin(GL_QUAD_STRIP);
glVertex2fv(packet_cord);
glVertex2f(packet_cord[0], packet_cord[1] + 30);
glColor3ub(37, 94, 186);
glVertex2f(packet_cord[0] + h_length, packet_cord[1]);
glColor3ub(37, 94, 186);
glVertex2f(packet_cord[0] + h_length, packet_cord[1] + y_packet_size);
glColor3ub(37, 94, 186);
glVertex2f(packet_cord[0] + h_length + x_packet_size, packet_cord[1]);
glColor3ub(37, 94, 186);
glVertex2f(packet_cord[0] + h_length + x_packet_size, packet_cord[1] + y_packet_size);
glEnd();*/
/*
switch (S) {
case 1:
switch (dest) {
case 2:
glLineWidth(LNW);
glColor3uv(linehcolor);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 3:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);

break;
case 4:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 5:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 6:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
break;
default:
glColor3ub(255, 0, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
}
break;
case 2:
switch (dest) {
case 1:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 3:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 4:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 5:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 6:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
default:
glColor3ub(255, 0, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
}
break;
case 3:
switch (dest) {
case 1:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 2:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 4:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 5:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 6:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
default:
glColor3ub(255, 0, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
}
break;
case 4:
switch (dest) {
case 1:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 2:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 3:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 5:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 6:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
default:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
}
break;
case 5:
switch (dest) {
case 1:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 2:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 3:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 4:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
case 6:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
default:
glColor3ub(255, 0, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
break;
}
break;
case 6:
switch (dest) {
case 1:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
break;
case 2:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
break;
case 3:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
break;
case 4:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
break;
case 5:
glColor3ub(25, 255, 71);
linehighlight();
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(0, 255, 0);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
default:
glColor3ub(255, 0, 0);
circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
glColor3ub(81, 191, 255);
circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
break;
}
break;
}*/