#include "inc.h"
float xm = 10, ym = 20, xmm = 300, ymm = 65;

/*
0 3 2 5 0 0
3 0 0 1 4 0
2 0 0 2 0 3
5 1 2 0 3 0
0 4 0 3 0 2
0 0 3 0 2 0
*/

/*
0 9 4 6 0 0
9 0 0 1 2 0
4 0 0 2 0 1
6 1 2 0 1 0
0 2 0 1 0 3
0 0 1 0 3 0
*/

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	/*packet1 = glGenLists(1);
	glNewList(packet1, GL_COMPILE);
	glColor3ub(222, 229, 239);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(60, 460);
	glVertex2f(60, 490);
	glColor3ub(37, 94, 186);
	glVertex2f(80, 460);
	glVertex2f(80, 460 + y_packet_size);
	glVertex2f(80 + x_packet_size, 460);
	glVertex2f(80 + x_packet_size, 460 + y_packet_size);
	glEnd();
	glEndList();*/

}

void stroke(float p, float q, char* scre, float siz, float lw)
{
	glLineWidth(lw);
	glPushMatrix();
	glTranslatef(p, q, 0);
	glScalef(siz, siz, siz);
	for (int c = 0; scre[c] != 0; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, scre[c]);
	glPopMatrix();
	glLineWidth(1);
}

//link break
void link()
{
	g1[link1][link2] = 0;
	g1[link2][link1] = 0;
	for (int i1 = 0; i1<18; i1++)
	{
		if (edge[i1][0] == link1&&edge[i1][1] == link2)
			continue;
		else if (edge[i1][0] == link2&&edge[i1][1] == link1)
			continue;
		else {
			ed[i1][0] = edge[i1][0];
			ed[i1][1] = edge[i1][1];
		}
	}
	Bellman_Ford(g1, V, E - 2, ed);
}


//for path calcultion (visualization)
void calc()
{

	int br = 1, l, q;
	cout << flag << "----" << ind << endl;
	if (flag == 0)
	{

		for (l = 0; l < 6; l++)
		{
			for (q = 0; q < sz[l] - 1; q++)
			{
				if (l + 1 == S)
				{
					break;
				}
				else if (mypath[l][q] == 0)
				{
					continue;
				}
				else
				{
					flag = mypath[l][q] * 10 + mypath[l][q + 1];
					mypath[l][q] = 0;
					br = 0;
					dest = path[l][0];
					ind = l;
					break;
				}
			}
			if (br == 0)
			{
				break;
			}
		}
		/*if (mypath[l][sz[l] - 2] == 0)
			sta = 0;*/
	}
}

//to print the cost
void costmatrix()
{
	int a, b;
	int i=0;
	for (a = 0; a < 5; a++)
	{
		for (b = a+1; b < 6; b++)
		{
			if (G[a][b] != 0)
			{
				sprintf_s(buf[i++], "%d", G[a][b]);
			}
		}
	}
}

//packet
void packet(int i)
{
	i--;
	packet_cord[0] = node_cord[i][0];  //x
	packet_cord[1] = node_cord[i][1];  //y

									   //packet1 = glGenLists(1);
									   //glNewList(packet1, GL_COMPILE_AND_EXECUTE);
	glColor3ub(222, 229, 239);
	glBegin(GL_QUADS);
	glVertex2fv(packet_cord);
	glVertex2f(packet_cord[0], packet_cord[1] + y_packet_size);
	glColor3ub(37, 94, 186);
	glVertex2f(packet_cord[0] + h_length, packet_cord[1] + y_packet_size);
	glColor3ub(37, 94, 186);
	glVertex2f(packet_cord[0] + h_length, packet_cord[1]);
	glEnd();
	//glEndList();
}

//animation (line equation)
void timer(int val)
{

	glutTimerFunc(1000 / fps, timer, 100);

	//1--->3 (path movement)
	if (flag == 13 || flag == 25) {
		if (x <= node_cord[2][0] - x_packet_size - 25 - node_cord[0][0])
		{
			x += 1;
			y = 0;
		}
		else
		{
			flag = 0;
			x = 0;
			y = 0;

		}
	}

	//3--->1
	if (flag == 31 || flag == 52) {
		if (abs(x) <= node_cord[2][0] - node_cord[0][0])
		{
			x -= 1;
			y = 0;
		}
		else
		{
			flag = 0;
			x = 0;
			y = 0;


		}
	}

	//1--->4
	if (flag == 14)
	{
		if (x <= node_cord[3][0] - node_cord[0][0])
		{
			x += 1;
			y = ((-9 * (x + node_cord[0][0]) / 8) + (1035 / 2)) - node_cord[0][1];
		}
		else
		{
			flag = 0;
			x = 0;
			y = 0;

		}
	}

	//4--->1
	if (flag == 41)
	{
		if (abs(x) <= node_cord[3][0] - node_cord[0][0])
		{
			x -= 1;
			y = ((-9 * (x + node_cord[0][0]) / 8) + (1035 / 2)) - node_cord[0][1];
		}
		else
		{
			flag = 0;
			x = 0;
			y = 0;

		}
	}

	//1--->2
	if (flag == 12)
	{
		if (abs(y) <= node_cord[0][1] - node_cord[1][1])
		{
			y -= 1;
			x = 0;
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//2--->1
	if (flag == 21)
	{
		if (y <= node_cord[0][1] - node_cord[1][1])
		{
			y += 1;
			x = 0;
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//2--->4
	if (flag == 24)
	{
		if (x <= node_cord[3][0] - node_cord[1][0])
		{
			x += 1;
			y = ((21 * (x + node_cord[1][0]) / 16) - (75 / 4)) - node_cord[1][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//4--->2
	if (flag == 42)
	{
		if (abs(x) <= node_cord[3][0] - node_cord[1][0])
		{
			x -= 1;
			y = ((21 * (x + node_cord[1][0]) / 16) - (75 / 4)) - node_cord[1][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//3--->4
	if (flag == 34)
	{
		if (abs(x) <= node_cord[2][0] - node_cord[3][0])
		{
			x -= 1;
			y = ((9 * (x + node_cord[2][0]) / 8) + (45 / 2)) - node_cord[2][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//4--->3
	if (flag == 43)
	{
		if (abs(x) <= node_cord[2][0] - node_cord[3][0])
		{
			x += 1;
			y = ((9 * (x + node_cord[3][0]) / 8) + (45 / 2)) - node_cord[3][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//4--->5
	if (flag == 45)
	{
		if (abs(x) <= node_cord[4][0] - node_cord[3][0])
		{
			x += 1;
			y = ((-21 * (x + node_cord[3][0]) / 16) + (2235 / 4)) - node_cord[3][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//5--->4
	if (flag == 54)
	{
		if (abs(x) <= node_cord[4][0] - node_cord[3][0])
		{
			x -= 1;
			y = ((-21 * (x + node_cord[4][0]) / 16) + (2235 / 4)) - node_cord[4][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//3--->6
	/*if (flag == 36) {
	if (abs(x) <= node_cord[5][0] - node_cord[2][0])
	{
	x += 1;
	y = ((-9 * (x + node_cord[2][0]) / 8) + (1755 / 2)) - node_cord[2][1];
	}
	else
	{
	x = 0;
	y = 0;
	flag = 0;

	}
	}
	*/
	//6--->3
	if (flag == 63) {
		if (abs(x) <= node_cord[5][0] - node_cord[2][0])
		{
			x -= 1;
			y = ((-9 * (x + node_cord[5][0]) / 8) + (1755 / 2)) - node_cord[5][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//3--->6
	if (flag == 36) {
		if (abs(x) <= node_cord[5][0] - node_cord[2][0])
		{
			x += 1;
			y = ((-9 * (x + node_cord[2][0]) / 8) + (1755 / 2)) - node_cord[2][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//5--->6
	if (flag == 56) {
		if (abs(x) <= node_cord[5][0] - node_cord[4][0])
		{
			x += 1;
			y = ((21 * (x + node_cord[4][0]) / 16) - (1755 / 4)) - node_cord[4][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}

	//6--->5
	if (flag == 65) {
		if (abs(x) <= node_cord[5][0] - node_cord[4][0])
		{
			x -= 1;
			y = ((21 * (x + node_cord[5][0]) / 16) - (1755 / 4)) - node_cord[5][1];
		}
		else
		{
			x = 0;
			y = 0;
			flag = 0;

		}
	}
	glutPostRedisplay();
}

void mouse(int b, int s, int x, int y2)
{
	if (interactivemode == 1) {
		if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		{
			cout << "x=" << x << endl << "y=" << y2 << endl;
			if (x > 0 && x < 101 && y2>0 && y2 < 58)
				exit(0);

			if (x > 383 && x < 1126 && y2>193 && y2 < 258)
			{
				sourcemode = 1;
				interactivemode = 0;
			}
			if (x > 383 && x < 1126 && y2>335 && y2 < 402)
			{
				normalmode = 1;
				interactivemode = 0;
			}
			if (x > 383 && x < 1126 && y2>480 && y2 < 546)
			{
				linkbreakmode = 1;
				interactivemode = 0;
			}
			if (x > 383 && x < 1126 && y2>625 && y2 < 690)
			{
				buffermode = 1;
				interactivemode = 0;
			}
		}
	}
	glutPostRedisplay();
}



void mykey(unsigned char key, int x, int y)
{
//	int k;
	if (sourcemode == 1)
	{
		switch (key)
		{
		case '1': S = 1;
			sourcemode = 0;
			interactivemode = 1;
			break;
		case '2': S = 2;
			sourcemode = 0;
			interactivemode = 1;
			break;
		case '3': S = 3;
			sourcemode = 0;
			interactivemode = 1;
			break;
		case '4': S = 4;
			sourcemode = 0;
			interactivemode = 1;
			break;
		case '5': S = 5;
			sourcemode = 0;
			interactivemode = 1;
			break;
		case '6': S = 6;
			sourcemode = 0;
			interactivemode = 1;
			break;
		}
		link1 = 0;
		link2 = 0;
		fbuf = 0;
		fragcount=0;
		sta = 1;
		
		for (int i1 = 0; i1<V; i1++)
			for (int j1 = 0; j1<V; j1++)
			{
				G[i1][j1] = Gtemp[i1][j1];
			}
		for (int i1 = 0; i1 < 18; i1++)
		{
			edge[i1][0] = edgetemp[i1][0];
			edge[i1][1] = edgetemp[i1][1];
		}
		for (int i1 = 0; i1<V; i1++)
			for (int j1 = 0; j1<V; j1++)
			{
				g1[i1][j1] = G[i1][j1];
			}
		Bellman_Ford(G, V, E, edge);

	}
	else if (presentationmode == 1) {
		switch (key)
		{
		case 'e':	interactivemode = 1;
			presentationmode = 0;
			break;

		default:break;
		}
	}
	else if (interactivemode == 1)
	{
		switch (key)
		{
		case '1': sourcemode = 1;
			
			break;
		case '2': normalmode = 1;
			
			break;
		case '3':linkbreakmode = 1;
			break;
		case '4':buffermode = 1;
			break;
		case 'e':exit(0);
		case 'h':helpmode = 1;
			break;
		default: break;
		}
		interactivemode = 0;
	}
	else if (normalmode == 1)
	{
		switch (key)
		{
		case 'i': interactivemode = 1;
			normalmode = 0;
			flag = 0;
			dest = 0;
			break;
		default: break;
		}
		flag = 0;
	}
	else if (linkbreakmode == 1)
	{
		switch (key)
		{
		case 'i':interactivemode = 1;
			linkbreakmode = 0;
			lnf = 0;
			break;
		case '1': link1 = 0;
			link2 = 1;
			link();
			lnf = 1;
			break;
		case '2': link1 = 0;
			link2 = 2;
			link();
			lnf = 1;
			break;
		case '3': link1 = 0;
			link2 = 3;
			link();
			lnf = 1;
			break;
		case '4': link1 = 1;
			link2 = 3;
			link();
			lnf = 1;
			break;
		case '5': link1 = 1;
			link2 = 4;
			link();
			lnf = 1;
			break;
		case '6': link1 = 2;
			link2 = 3;
			link();
			lnf = 1;
			break;
		case '7': link1 = 2;
			link2 = 5;
			link();
			lnf = 1;
			break;
		case '8': link1 = 3;
			link2 = 4;
			link();
			lnf = 1;
			break;
		case '9': link1 = 4;
			link2 = 5;
			link();
			lnf = 1;
			break;
		default:break;
		}
	}
	else if (buffermode == 1)
	{
		switch (key)
		{
		case 'i':interactivemode = 1;
			buffermode = 0;
			break;
		case '1':destbuf = 1;
			break;
		case '2':destbuf = 2;
			break;
		case '3':destbuf = 3;
			break;
		case '4':destbuf = 4;
			break;
		case '5':destbuf = 5;
			break;
		case '6':destbuf = 6;
			break;
		case 's':
			fragcount++;
			sta = 1;
			for (int l = 0; l < sz[destbuf - 1]; l++)
			{
				pathbuf[l] = mypath[destbuf - 1][l];
				pathhighlight[0][l] = mypath[destbuf - 1][l];
			}
			ind = 0;
			flag = 0;
			break;
		}
		fbuf = 1;
		flag = 0;
	}else if(helpmode==1)
	{
		switch (key)
		{
		case 'i':interactivemode = 1;
			helpmode = 0;
		}
	}
	glutPostRedisplay();
}



//node
void circle_draw(GLfloat x, GLfloat y, GLfloat radius) {
	int i1;
	int triangleAmount = 100; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x + (radius * cos(i1 *  twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glEnd();
}

//text display
void drawtext(float x, float y, char *s, int size)
{
	int i;
	if (size == 2)
	{
		glRasterPos2f(x, y);
		for (i = 0; s[i] != '\0'; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
	}
	else
	{
		glRasterPos2f(x, y);
		for (i = 0; s[i] != '\0'; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
		}
	}
}

//line highlighting
void linehighlight()
{
	glLineWidth(10);
	switch (ind)
	{
	case 0:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[0][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[0][i1 + 1] - 1]);
			glEnd();
		}
		break;
	case 1:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[1][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[1][i1 + 1] - 1]);
			glEnd();
		}
		break;
	case 2:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[2][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[2][i1 + 1] - 1]);
			glEnd();
		}
		break;
	case 3:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[3][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[3][i1 + 1] - 1]);
			glEnd();
		}
		break;
	case 4:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[4][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[4][i1 + 1] - 1]);
			glEnd();
		}
		break;
	case 5:
		for (int i1 = 0; i1 < sz[ind] - 1; i1++)
		{
			glBegin(GL_LINES);//1-3
			glVertex2fv(node_cord[pathhighlight[5][i1] - 1]);
			glVertex2fv(node_cord[pathhighlight[5][i1 + 1] - 1]);
			glEnd();
		}
		break;

	}
	glLineWidth(1);
}

//packet movement(path is given by flag)
void disppk()
{
	/*if (nodef==0) {
	glColor3ubv(srcnodecolor);
	circle_draw(node_cord[S - 1][0], node_cord[S - 1][1], node_rad);
	char number[2];
	_itoa_s(S, number, 5);
	drawtext(node_cord[S-1][0], node_cord[S-1][1], number);
	nodef = 1;

	}*/
	if (flag == 54 || flag == 52 || flag == 56)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(5);
		glPopMatrix();

	}

	if (flag == 12 || flag == 14 || flag == 13)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(1);
		glPopMatrix();

	}

	if (flag == 21 || flag == 24 || flag == 25)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(2);
		glPopMatrix();

	}

	if (flag == 31 || flag == 34 || flag == 36)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(3);
		glPopMatrix();

	}

	if (flag == 63 || flag == 65)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(6);
		glPopMatrix();

	}

	if (flag == 41 || flag == 42 || flag == 43 || flag == 45)
	{

		glPushMatrix();

		glTranslatef(x, y, 0.0);
		packet(4);
		glPopMatrix();

	}


	/*if(flag==0)
	{
	glPushMatrix();

	glTranslatef(x, y, 0.0);
	packet(2);
	glPopMatrix();
	}*/
}

//graph
void disp()
{

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);//1-3
	glVertex2f(60, 450);
	glVertex2f(380, 450);
	glEnd();
	glBegin(GL_LINE_STRIP);//1-4
	glVertex2f(60, 450);
	glVertex2f(220, 270);
	glEnd();
	glBegin(GL_LINE_STRIP);//1-2
	glVertex2f(60, 450);
	glVertex2f(60, 60);
	glEnd();
	glBegin(GL_LINE_STRIP);//4-3
	glVertex2f(220, 270);
	glVertex2f(380, 450);
	glEnd();
	glBegin(GL_LINE_STRIP);//2-4
	glVertex2f(60, 60);
	glVertex2f(220, 270);
	glEnd();
	glBegin(GL_LINE_STRIP);//4-5
	glVertex2f(220, 270);
	glVertex2f(380, 60);
	glEnd();
	glBegin(GL_LINE_STRIP);//2-5
	glVertex2f(60, 60);
	glVertex2f(380, 60);
	glEnd();
	glBegin(GL_LINE_STRIP);//3-6
	glVertex2f(380, 450);
	glVertex2f(540, 270);
	glEnd();
	glBegin(GL_LINE_STRIP);//5-6
	glVertex2f(380, 60);
	glVertex2f(540, 270);
	glEnd();
	if (linkbreakmode == 0) {
		for (int y = 0; y < 9; y++)
		{
			drawtext(costcoord[y][0], costcoord[y][1], buf[y], 2);
		}
	}
	if (flag != 0) {
		switch (S) {
		case 1:
			switch (dest) {
			case 2:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 3:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 4:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 5:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 6:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(540, 220, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				break;
			default:
				glColor3ubv(srcnodecolor);
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
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 3:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 4:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 5:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 6:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(540, 220, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			default:
				glColor3ubv(srcnodecolor);
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
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 2:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 4:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 5:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 6:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Source", 1);
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(540, 220, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			default:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
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
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 2:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 3:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 5:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 6:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(540, 220, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			default:
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			}
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Source", 1);
			break;
		case 5:
			switch (dest) {
			case 1:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 2:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 3:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 4:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			case 6:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(540, 220, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			default:
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				break;
			}
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Source", 1);
			break;
		case 6:
			switch (dest) {
			case 1:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				break;
			case 2:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(60, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				break;
			case 3:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 480, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				break;
			case 4:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(250, 270, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				break;
			case 5:
				glColor3ubv(linehcolor);
				linehighlight();
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ubv(srctextcolor);
				drawtext(380, 20, "Destination", 1);
				glColor3ubv(destnodecolor);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			default:
				glColor3ubv(srcnodecolor);
				circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
				glColor3ub(81, 191, 255);
				circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
				circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
				circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
				circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
				circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
				break;
			}
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Source", 1);
			break;
		}
	}
	else
	{
		glColor3ub(81, 191, 255);
		circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
		circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
		circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
		circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
		circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
		circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
	}
	glColor3ub(0, 0, 0);
	drawtext(node_cord[0][0], node_cord[0][1], "1", 1);
	drawtext(node_cord[1][0], node_cord[1][1], "2", 1);
	drawtext(node_cord[2][0], node_cord[2][1], "3", 1);
	drawtext(node_cord[3][0], node_cord[3][1], "4", 1);
	drawtext(node_cord[4][0], node_cord[4][1], "5", 1);
	drawtext(node_cord[5][0], node_cord[5][1], "6", 1);
}

//to calculate buffer path
void bufcalc()
{
	int q;
	cout << flag << endl;
	if (flag == 0)
	{
		for (q = 0; q < sz[destbuf - 1] - 1; q++)
		{
			
			if (pathbuf[q] == 0)
			{
				continue;
			}
			else
			{
				flag = pathbuf[q] * 10 + pathbuf[q + 1];
				pathbuf[q] = 0;
				ind = 0;
				//dest = path[l][0];
				//ind = l;
				break;
			}
		}
		if (pathbuf[sz[destbuf - 1] - 2] == 0)
			sta = 0;
	}
	
	
}

//buffer and fragments display and animation
void buffer()
{
	int i1,j1;
	disp();
	switch (S)
	{
	case 1:
		switch (destbuf)
		{
		case 2: 
			glColor3ubv(srctextcolor);
			drawtext(60, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 200);
			glVertex2f(10, 100);
			glVertex2f(40, 100);
			glVertex2f(40, 200);
			glEnd();
			break;
		case 3:
			glColor3ubv(srctextcolor);
			drawtext(380, 480, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(410, 590);
			glVertex2f(410, 490);
			glVertex2f(440, 490);
			glVertex2f(440, 590);
			glEnd();
			break;
		case 4:
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(280, 320);
			glVertex2f(280, 220);
			glVertex2f(310, 220);
			glVertex2f(310, 320);
			glEnd();
			break;
		case 5:
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(440, 110);
			glVertex2f(440, 10);
			glVertex2f(470, 10);
			glVertex2f(470, 110);
			glEnd();
			break;
		case 6:
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(550, 210);
			glVertex2f(550, 110);
			glVertex2f(580, 110);
			glVertex2f(580, 210);
			glEnd();
			break;
		}
		glColor3ubv(srctextcolor);
		drawtext(60, 480, "Source", 1);
		glColor3ubv(srcnodecolor);
		circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(10, 590);
		glVertex2f(10, 490);
		glVertex2f(40, 490);
		glVertex2f(40, 590);
		glEnd();
		break;

	case 2:
		switch (destbuf)
		{
		case 1: 
			glColor3ubv(srctextcolor);
			drawtext(60, 480, "Destination", 1);
			glColor3ubv(srcnodecolor);
			circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 590);
			glVertex2f(10, 490);
			glVertex2f(40, 490);
			glVertex2f(40, 590);
			glEnd();
			break;
		case 3:
			glColor3ubv(srctextcolor);
			drawtext(380, 480, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(410, 590);
			glVertex2f(410, 490);
			glVertex2f(440, 490);
			glVertex2f(440, 590);
			glEnd();
			break;
		case 4:
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(280, 320);
			glVertex2f(280, 220);
			glVertex2f(310, 220);
			glVertex2f(310, 320);
			glEnd();
			break;
		case 5:
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(440, 110);
			glVertex2f(440, 10);
			glVertex2f(470, 10);
			glVertex2f(470, 110);
			glEnd();
			break;
		case 6:
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(550, 210);
			glVertex2f(550, 110);
			glVertex2f(580, 110);
			glVertex2f(580, 210);
			glEnd();
			break;
		}
		glColor3ubv(srctextcolor);
		drawtext(60, 20, "Source", 1);
		glColor3ubv(destnodecolor);
		circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(10, 200);
		glVertex2f(10, 100);
		glVertex2f(40, 100);
		glVertex2f(40, 200);
		glEnd();
		break;
	case 3:
		switch (destbuf)
		{
		case 1:
			glColor3ubv(srctextcolor);
			drawtext(60, 480, "Destination", 1);
			glColor3ubv(srcnodecolor);
			circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 590);
			glVertex2f(10, 490);
			glVertex2f(40, 490);
			glVertex2f(40, 590);
			glEnd();
			break;
		case 2:
			glColor3ubv(srctextcolor);
			drawtext(60, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 200);
			glVertex2f(10, 100);
			glVertex2f(40, 100);
			glVertex2f(40, 200);
			glEnd();
			break;
		case 4:
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(280, 320);
			glVertex2f(280, 220);
			glVertex2f(310, 220);
			glVertex2f(310, 320);
			glEnd();
			break;
		case 5:
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(440, 110);
			glVertex2f(440, 10);
			glVertex2f(470, 10);
			glVertex2f(470, 110);
			glEnd();
			break;
		case 6:
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(550, 210);
			glVertex2f(550, 110);
			glVertex2f(580, 110);
			glVertex2f(580, 210);
			glEnd();
			break;
		}

		glColor3ubv(srctextcolor);
		drawtext(380, 480, "Source", 1);
		glColor3ubv(destnodecolor);
		circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(410, 590);
		glVertex2f(410, 490);
		glVertex2f(440, 490);
		glVertex2f(440, 590);
		glEnd();
		break;
	case 4:
		switch (destbuf)
		{
		case 1:
			glColor3ubv(srctextcolor);
			drawtext(60, 480, "Destination", 1);
			glColor3ubv(srcnodecolor);
			circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 590);
			glVertex2f(10, 490);
			glVertex2f(40, 490);
			glVertex2f(40, 590);
			glEnd();
			break;
		case 2:
			glColor3ubv(srctextcolor);
			drawtext(60, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 200);
			glVertex2f(10, 100);
			glVertex2f(40, 100);
			glVertex2f(40, 200);
			glEnd();
			break;
		case 3:
			glColor3ubv(srctextcolor);
			drawtext(380, 480, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(410, 590);
			glVertex2f(410, 490);
			glVertex2f(440, 490);
			glVertex2f(440, 590);
			glEnd();
			break;
		case 5:
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(440, 110);
			glVertex2f(440, 10);
			glVertex2f(470, 10);
			glVertex2f(470, 110);
			glEnd();
			break;
		case 6:
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(550, 210);
			glVertex2f(550, 110);
			glVertex2f(580, 110);
			glVertex2f(580, 210);
			glEnd();
			break;
		}
		glColor3ubv(srctextcolor);
		drawtext(250, 270, "Source", 1);
		glColor3ubv(destnodecolor);
		circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(280, 320);
		glVertex2f(280, 220);
		glVertex2f(310, 220);
		glVertex2f(310, 320);
		glEnd();
		break;
	case 5:
		switch (destbuf)
		{
		case 1:
			glColor3ubv(srctextcolor);
			drawtext(60, 480, "Destination", 1);
			glColor3ubv(srcnodecolor);
			circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 590);
			glVertex2f(10, 490);
			glVertex2f(40, 490);
			glVertex2f(40, 590);
			glEnd();
			break;
		case 2:
			glColor3ubv(srctextcolor);
			drawtext(60, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 200);
			glVertex2f(10, 100);
			glVertex2f(40, 100);
			glVertex2f(40, 200);
			glEnd();
			break;
		case 3:
			glColor3ubv(srctextcolor);
			drawtext(380, 480, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(410, 590);
			glVertex2f(410, 490);
			glVertex2f(440, 490);
			glVertex2f(440, 590);
			glEnd();
			break;
		case 4:
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(280, 320);
			glVertex2f(280, 220);
			glVertex2f(310, 220);
			glVertex2f(310, 320);
			glEnd();
			break;
		case 6:
			glColor3ubv(srctextcolor);
			drawtext(540, 220, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(550, 210);
			glVertex2f(550, 110);
			glVertex2f(580, 110);
			glVertex2f(580, 210);
			glEnd();
			break;
		}
		glColor3ubv(srctextcolor);
		drawtext(380, 20, "Source", 1);
		glColor3ubv(destnodecolor);
		circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(440, 110);
		glVertex2f(440, 10);
		glVertex2f(470, 10);
		glVertex2f(470, 110);
		glEnd();
		break;
	case 6:
		switch (destbuf)
		{
		case 1:
			glColor3ubv(srctextcolor);
			drawtext(60, 480, "Destination", 1);
			glColor3ubv(srcnodecolor);
			circle_draw(node_cord[0][0], node_cord[0][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 590);
			glVertex2f(10, 490);
			glVertex2f(40, 490);
			glVertex2f(40, 590);
			glEnd();
			break;
		case 2:
			glColor3ubv(srctextcolor);
			drawtext(60, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[1][0], node_cord[1][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10, 200);
			glVertex2f(10, 100);
			glVertex2f(40, 100);
			glVertex2f(40, 200);
			glEnd();
			break;
		case 3:
			glColor3ubv(srctextcolor);
			drawtext(380, 480, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[2][0], node_cord[2][1], node_rad);
			glBegin(GL_LINE_LOOP);
			glVertex2f(410, 590);
			glVertex2f(410, 490);
			glVertex2f(440, 490);
			glVertex2f(440, 590);
			glEnd();
			break;
		case 4:
			glColor3ubv(srctextcolor);
			drawtext(250, 270, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[3][0], node_cord[3][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(280, 320);
			glVertex2f(280, 220);
			glVertex2f(310, 220);
			glVertex2f(310, 320);
			glEnd();
			break;
		case 5:
			glColor3ubv(srctextcolor);
			drawtext(380, 20, "Destination", 1);
			glColor3ubv(destnodecolor);
			circle_draw(node_cord[4][0], node_cord[4][1], node_rad);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(440, 110);
			glVertex2f(440, 10);
			glVertex2f(470, 10);
			glVertex2f(470, 110);
			glEnd();
			break;
		}
		glColor3ubv(srctextcolor);
		drawtext(540, 220, "Source", 1);
		glColor3ubv(destnodecolor);
		circle_draw(node_cord[5][0], node_cord[5][1], node_rad);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2f(550, 210);
		glVertex2f(550, 110);
		glVertex2f(580, 110);
		glVertex2f(580, 210);
		glEnd();
		break;
	}
	glColor3ub(0, 0, 0);
	drawtext(node_cord[0][0], node_cord[0][1], "1", 1);
	drawtext(node_cord[1][0], node_cord[1][1], "2", 1);
	drawtext(node_cord[2][0], node_cord[2][1], "3", 1);
	drawtext(node_cord[3][0], node_cord[3][1], "4", 1);
	drawtext(node_cord[4][0], node_cord[4][1], "5", 1);
	drawtext(node_cord[5][0], node_cord[5][1], "6", 1);
	switch (fragcount)
	{
	case 0:	i1 = 5;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
			glColor3ub(222, 229, 239);
			glRecti(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, vert[S - 1][1][0] - 2, vert[S - 1][1][1] + l - 2);
			sprintf_s(seq, "%d", i1);
			glColor3i(0, 0, 1);
			drawtext(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, seq, 1);
			i1--;
		}

			break;
	case 1: i1 = 5;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
			for (int l = 0; l < 80; l += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, vert[S - 1][1][0] - 2, vert[S - 1][1][1] + l - 2);
			sprintf_s(seq, "%d", i1);
			glColor3i(0, 0, 1);
			drawtext(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, seq, 1);
			i1--;
		}
		if(sta==0 && flag == 0)
			for (int q = 0; q < 20; q += 20) {
				glColor3ub(222, 229, 239);
				glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
				sprintf_s(seq, "%d", i1 );
				glColor3i(0, 0, 1);
				drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
				i1++;
		}
			
			break;
	case 2:i1 = 5; j1 = 1;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
		for (int l = 0; l < 60; l += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, vert[S - 1][1][0] - 2, vert[S - 1][1][1] + l - 2);
			sprintf_s(seq, "%d", i1);
			glColor3i(0, 0, 1);
			drawtext(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, seq, 1);
			i1--;
		}
		for (int q = 0; q < 20; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", j1);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			j1--;
		}
		if (sta == 0 && flag == 0)
			for (int q = 0; q < 40; q += 20) {
				glColor3ub(222, 229, 239);
				glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
				sprintf_s(seq, "%d", i1-1);
				glColor3i(0, 0, 1);
				drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
				i1++;
			}

		break;
	case 3:i1 = 5; j1 = 1;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
		for (int l = 0; l < 40; l += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, vert[S - 1][1][0] - 2, vert[S - 1][1][1] + l - 2);
			sprintf_s(seq, "%d", i1);
			glColor3i(0, 0, 1);
			drawtext(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, seq, 1);
			i1--;
		}
		for (int q = 0; q < 40; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", j1);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			j1++;
		}
		if (sta == 0 && flag == 0)
			for (int q = 0; q < 60; q += 20) {
				glColor3ub(222, 229, 239);
				glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
				sprintf_s(seq, "%d", i1 - 2);
				glColor3i(0, 0, 1);
				drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
				i1++;
			}

		break;
	case 4:i1 = 5; j1 = 1;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
		for (int l = 0; l < 20; l += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, vert[S - 1][1][0] - 2, vert[S - 1][1][1] + l - 2);
			sprintf_s(seq, "%d", i1);
			glColor3i(0, 0, 1);
			drawtext(vert[S - 1][0][0] + 2, vert[S - 1][0][1] + l - 17, seq, 1);
			i1--;
		}
		for (int q = 0; q < 60; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", j1);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			j1++;
		}
		if (sta == 0&&flag == 0)
			for (int q = 0; q < 80; q += 20) {
				glColor3ub(222, 229, 239);
				glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
				sprintf_s(seq, "%d", i1 - 3);
				glColor3i(0, 0, 1);
				drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
				i1++;
			}

		break;
	case 5:i1 = 5; j1 = 1;
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
		for (int q = 0; q < 80; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", j1);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			j1++;
		}
		
		if (sta == 0 && flag == 0) {
			for (int q = 0; q < 100; q += 20) {
				glColor3ub(222, 229, 239);
				glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
				sprintf_s(seq, "%d", i1 - 4);
				glColor3i(0, 0, 1);
				drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
				i1++;
			}
			glColor3f(1, 1, 1);
			drawtext(250, 500, "MESSAGE RECEIVED!", 2);
		}

		break;

	default: i1 = 5; j1 = 1;
		drawtext(250, 500, "Buffer Overflow!", 2);
		for (int l = 0; l < 100; l += 20) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2i(vert[destbuf - 1][0][0], vert[destbuf - 1][0][1] + l);
			glVertex2i(vert[destbuf - 1][1][0], vert[destbuf - 1][1][1] + l);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(vert[S - 1][0][0], vert[S - 1][0][1] + l);
			glVertex2i(vert[S - 1][1][0], vert[S - 1][0][1] + l);
			glEnd();
		}
		for (int q = 0; q < 80; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", j1);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			j1++;
		}

		
		for (int q = 0; q < 100; q += 20) {
			glColor3ub(222, 229, 239);
			glRecti(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, vert[destbuf - 1][1][0] - 2, vert[destbuf - 1][1][1] + q - 2);
			sprintf_s(seq, "%d", i1 - 4);
			glColor3i(0, 0, 1);
			drawtext(vert[destbuf - 1][0][0] + 2, vert[destbuf - 1][0][1] + q - 17, seq, 1);
			i1++;
		}

		break;
	}
	
	bufcalc();
	disppk();

}


//start screen
void disppresent()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(116, 0, 165);
	stroke(40, 500, "NETWORK PROTOCOLS", 0.35, 4);
	stroke(135, 430, "VISUALIZATION", 0.35, 4);
	glColor3ub(68, 56, 66);
	stroke(150, 180, "RAGHUVEER BHAT R [1RN14CS078]", 0.12,1);
	stroke(150, 160, "PRAMOD G [1RN14CS067]", 0.12,1);
	glColor3ub(160,0,0);
	stroke(100, 320, "DEPARTMENT OF COMPUTER SCIENCE", 0.15,3);
	stroke(200, 280, "RNSIT BENGALURU", 0.15, 3);
	drawtext(400, 50, "PRESS e TO CONTINUE...", 1);

}

//interactive mode
void dispinteract()
{
	glClearColor(255/255, 201/255, 71/255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glRectf(xm + 140, ym + 400, xmm + 140, ymm + 400);
	glRectf(xm + 140, ym + 300, xmm + 140, ymm + 300);
	glRectf(xm + 140, ym + 200, xmm + 140, ymm + 200);
	glRectf(xm + 140, ym + 100, xmm + 140, ymm + 100);
	glRectf(0, 560, 40, 600); //exit
	//glRectf(490, 490, 540, 540);
	glColor3ub(255, 255, 255);
	stroke(100, 520, "~~INTERACTIVE MODE~~", 0.25, 2);
	glColor3ub(0, 0, 0);
	drawtext(250, 435, "1.Enter Source", 2);
	drawtext(250, 335, "2.Visualization Mode", 2);
	drawtext(240, 235, "3.Link Failure Mode", 2);
	drawtext(245, 135, "4.Buffer Mode", 2);
	drawtext(7,570, "Exit", 2);
}

//source mode
void dispsource() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	drawtext(250, 435, "Enter Source", 2);
}

//help mode
void help()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 1, 1);
	drawtext(100, 550, "i---->GO BACK TO INTERACTIVE MODE", 2);
	drawtext(100, 500, "e---->EXIT", 2);
	drawtext(100, 450, "h---->HELP MODE", 2);

}
//display callback
void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	if (presentationmode == 1)
	{
		disppresent();
	}
	if (interactivemode == 1)
	{

		dispinteract();
	}
	if (sourcemode == 1)
	{

		dispsource();
	}
	if (normalmode == 1)
	{
		glColor3ub(22, 255, 173);
		stroke(100, 520, "~~VISUALIZATION MODE~~", 0.25, 2);
		glPointSize(15);
		glLineWidth(3);
		disp();
		calc();
		disppk();
		drawtext(500, 10, "Press i to go back...", 1);
	}
	if (linkbreakmode == 1)
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3ub(22, 255, 173);
		stroke(100, 520, "~~LINK BREAK MODE~~", 0.25, 2);
		disp();
		if (lnf == 0) {
			glColor3f(1, 1, 1);
			glRectf(205, 465, 235, 435);//1-3
			glRectf(205, 75, 235, 45);//2-5
			glRectf(43, 265, 73, 235);//1-2
			glRectf(133, 195, 163, 165);//2-4
			glRectf(133, 365, 163, 335);//1-4
			glRectf(273, 365, 303, 335);//4-3
			glRectf(273, 195, 303, 165);//4-5
			glRectf(453, 195, 483, 165);//5-6
			glRectf(453, 365, 483, 335);//3-6
			glColor3f(0, 0, 0);
			drawtext(217, 447, "2", 1);//
			drawtext(217, 49, "5", 1);
			drawtext(56, 248, "1", 1);
			drawtext(146, 178, "4", 1);
			drawtext(146, 348, "3", 1);
			drawtext(286, 348, "6", 1);
			drawtext(286, 178, "8", 1);
			drawtext(466, 178, "9", 1);
			drawtext(466, 348, "7", 1);
		}
		else if (lnf == 1)
		{
			glColor3f(1, 0, 0);
			glLineWidth(10);
			switch (link1)
			{
			case 0:
				switch (link2)
				{
				case 1:
					glBegin(GL_LINES);
					glVertex2f(43, 235);
					glVertex2f(73, 265);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(43, 265);
					glVertex2f(73, 235);
					glEnd();
					break;
				case 2:
					glBegin(GL_LINES);
					glVertex2f(205, 435);
					glVertex2f(235, 465);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(205, 465);
					glVertex2f(235, 435);
					glEnd();
					break;
				case 3:
					glBegin(GL_LINES);
					glVertex2f(133, 365);
					glVertex2f(163, 335);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(133, 335);
					glVertex2f(163, 365);
					glEnd();
					break;
				}
				break;
			case 1:
				switch (link2)
				{
				case 3:
					glBegin(GL_LINES);
					glVertex2f(113, 165);
					glVertex2f(143, 135);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(113, 135);
					glVertex2f(143, 165);
					glEnd();
					break;
				case 4:
					glBegin(GL_LINES);
					glVertex2f(235, 45);
					glVertex2f(205, 75);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(205, 45);
					glVertex2f(235, 75);
					glEnd();
					break;
				}
				break;
			case 2:
				switch (link2)
				{
				case 3:
					glBegin(GL_LINES);
					glVertex2f(273, 335);
					glVertex2f(303, 365);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(273, 365);
					glVertex2f(303, 335);
					glEnd();
					break;

				case 5:
					glBegin(GL_LINES);
					glVertex2f(453, 335);
					glVertex2f(483, 365);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(453, 365);
					glVertex2f(483, 335);
					glEnd();
					break;
				}
				break;
			case 3:
				switch (link2)
				{

				case 4:
					glBegin(GL_LINES);
					glVertex2f(273, 195);
					glVertex2f(303, 165);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(273, 165);
					glVertex2f(303, 195);
					glEnd();
					break;

				}
				break;
			case 4:
				switch (link2)
				{
				case 5:glBegin(GL_LINES);
					glVertex2f(453, 165);
					glVertex2f(483, 195);
					glEnd();
					glBegin(GL_LINES);
					glVertex2f(453, 195);
					glVertex2f(483, 165);
					glEnd();
					break;

				}
				break;
			default:break;

			}
		}

		glColor3f(1, 1, 1);
		drawtext(50, 500, "Enter the link no", 1);
		drawtext(500, 10, "Press i to go back...", 1);
	}
	if (buffermode == 1)
	{
		if (fbuf == 0) {
			glColor3f(1, 1, 1);
			drawtext(200, 500, "Enter destination node:", 2);
		}
		else {
			glColor3ub(22, 255, 173);
			stroke(50, 520, "~~BUFFER MODE~~", 0.25, 2);
			drawtext(500, 10, "Press i to go back...", 1);
			buffer();
		}
	}
	if (helpmode == 1)
	{
		help();
	}
	glutSwapBuffers();

}

//reshape
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,600,0,600);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

//main
int main(int argc, char** argv)
{
	//cout << "Enter n:";
	//cin >> n;
	//cout << "Enter cost mat: ";
	/*for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
	cin >> cost[i][j];*/

	cout << "BELLMAN FORD\n";
	V = 6;
	cout << "Enter graph in matrix form:\n";
	for (i = 0; i<V; i++)
		for (j = 0; j<V; j++)
		{
			cin >> G[i][j];
			if (G[i][j] != 0)
			{
				edge[E][0] = i, edge[E][1] = j;
				edgetemp[E][0] = i; edgetemp[E++][1] = j;
			}
			g1[i][j] = G[i][j];
			Gtemp[i][j] = G[i][j];
		}
	costmatrix();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);
	glutInitWindowSize(1024,600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Project");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutFullScreen();
	glutDisplayFunc(display);
	glutTimerFunc(1000 / fps, timer, 100);
	glutReshapeFunc(reshape);
	//glutIdleFunc(Idle);
	glutKeyboardFunc(mykey);
	glutMouseFunc(mouse);
	glutMainLoop();

}

