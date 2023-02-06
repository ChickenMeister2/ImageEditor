#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//strucutra pentru selectia imaginii
struct selectie {
int x1;
int y1;
int x2;
int y2;
int isselected;
};

void deallocmatrix(int **matrix, int row)
{
int i;
for (i = 0; i < row; i++)
	free(matrix[i]);
free(matrix);
}

//functie care decide mesajul sau actiunile pe care le va face
//comanda EXIT
void exitfunction(int **pixelmatrix, int height, int loaded)
{
if (loaded == 1)
	deallocmatrix(pixelmatrix, height);
if (loaded == 0)
	printf("No image loaded\n");
}

void selectarea(int loaded, int *select)
{
	if (loaded == 1)
		*select = 0;
	else
		*select = 2;
}

//functie care constrange valorile pixelilor in intervalul valid [0,255]
int clamp(int value)
{
if (value > 255)
	return 255;
if (value < 0)
	return 0;
return value;
}

//citirea imaginii alb-negru in format ascii
int readp2(int *width, int *height, int ***pixelmatrix, char filename[],
		   int *current_pos, int *loaded)
{
int i, j;

int **a = (int **)calloc(*height, sizeof(int *));
if (!a) {  // daca nu pot aloca, opresc executia si afisez un mesaj
	fprintf(stderr, "malloc() for matrix failed\n");
	*pixelmatrix = NULL;
	return 0;
}

*pixelmatrix = a;

for (int i = 0; i < *height; i++) {
	a[i] = (int *)calloc(*width, sizeof(int));
	if (!a[i]) {
		// daca una din alocari a esuat, trebuie sa dezaloc tot ce am alocat
		fprintf(stderr, "calloc() for line %d failed\n", i);
		for (int j = 0; j < i; j++)
			free(a[j]);
		free(a);
		*pixelmatrix = NULL;
	return 0;
	}
}

FILE * photo;
photo = fopen(filename, "r");

if (!photo)
	fprintf(stderr, "Cannot open file\n");

printf("Loaded %s\n", filename);
*loaded = 1;

fseek(photo, *current_pos, SEEK_SET);
for (i = 0; i < *height; i++)
	for (j = 0; j < *width; j++)
		fscanf(photo, "%d", &a[i][j]);
fclose(photo);
return 0;
}

//functie pentru citirea unei poze in format ascii color
int readp3(int *width, int *height, int ***pixelmatrix, char filename[],
		   int *current_pos, int *loaded)
{
int i, j;
int **a = (int **)calloc(*height, sizeof(int *));

if (!a) {  // daca nu pot aloca, opresc executia si afisez un mesaj
	fprintf(stderr, "malloc() for matrix failed\n");
	*pixelmatrix = NULL;
	return 0;
}

*pixelmatrix = a;

for (int i = 0; i < *height; i++) {
	a[i] = (int *)calloc((*width) * 3, sizeof(int));
	if (!a[i]) {
		// daca una din alocari a esuat, trebuie sa dezaloc tot ce am alocat
		fprintf(stderr, "calloc() for line %d failed\n", i);
		for (int j = 0; j < i; j++)
			free(a[j]);
		free(a);
		*pixelmatrix = NULL;
		return 0;
	}
}

FILE * photo;
photo = fopen(filename, "r");

if (!photo)
	fprintf(stderr, "Cannot open file\n");

printf("Loaded %s\n", filename);
*loaded = 1;
fseek(photo, *current_pos, SEEK_SET);

for (i = 0; i < *height; i++)
	for (j = 0; j < *width * 3; j++)
		fscanf(photo, "%d", &a[i][j]);
fclose(photo);
return 0;
}

//functie pentru citirea unei imagini in format binar alb-negru
int readp5(int *width, int *height, int ***pixelmatrix, char filename[],
		   int *current_pos, int *loaded)
{
int i, j;
int **a = (int **)calloc(*height, sizeof(int *));

if (!a) {  // daca nu pot aloca, opresc executia si afisez un mesaj
	fprintf(stderr, "malloc() for matrix failed\n");
	*pixelmatrix = NULL;
	return 0;
}

*pixelmatrix = a;

for (int i = 0; i < *height; i++) {
	a[i] = (int *)calloc((*width), sizeof(int));
	if (!a[i]) {
		// daca una din alocari a esuat, trebuie sa dezaloc tot ce am alocat
		fprintf(stderr, "calloc() for line %d failed\n", i);
		for (int j = 0; j < i; j++)
			free(a[j]);
		free(a);
		*pixelmatrix = NULL;
		return 0;
	}
}

FILE * photo;
photo = fopen(filename, "rb");

fseek(photo, *current_pos, SEEK_SET);
if (!photo)
	fprintf(stderr, "Cannot open file\n");

printf("Loaded %s\n", filename);
*loaded = 1;

for (i = 0; i < *height; i++)
	for (j = 0; j < *width; j++)
		fread(&a[i][j], sizeof(unsigned char), 1, photo);
fclose(photo);
return 0;
}

//functie pentru citirea unei imagini color in format binar
int readp6(int *width, int *height, int ***pixelmatrix, char filename[],
		   int *current_pos, int *loaded)
{
int i, j;

int **a = (int **)calloc(*height, sizeof(int *));
if (!a) {  // daca nu pot aloca, opresc executia si afisez un mesaj
	fprintf(stderr, "malloc() for matrix failed\n");
	*pixelmatrix = NULL;
	return 0;
}

*pixelmatrix = a;

for (int i = 0; i < *height; i++) {
	a[i] = (int *)calloc((*width) * 3, sizeof(int));
	if (!a[i]) {
		// daca una din alocari a esuat, trebuie sa dezaloc tot ce am alocat
		fprintf(stderr, "calloc() for line %d failed\n", i);
		for (int j = 0; j < i; j++)
			free(a[j]);
		free(a);
		*pixelmatrix = NULL;
		return 0;
	}
}

FILE * photo;
photo = fopen(filename, "rb");

fseek(photo, *current_pos, SEEK_SET);

if (!photo)
	fprintf(stderr, "Cannot open file\n");

printf("Loaded %s\n", filename);
*loaded = 1;

for (i = 0; i < *height; i++)
	for (j = 0; j < *width * 3; j++)
		fread(&a[i][j], sizeof(unsigned char), 1, photo);

fclose(photo);
return 0;
}

//fucntia care citeste headerul si se ocupa de apelarea celorlalte functii
//specifice tipului de poza
int openphoto(int *type, int *width, int *height, int *maxpixelvalue,
			  char *filename, int *current_pos, int ***pixelmatrix,
			  int *loaded)
{
FILE *photo;
photo = fopen(filename, "r");

if (!photo) {
	if (*loaded == 1) {
		deallocmatrix(*pixelmatrix, *height);
		*loaded = 0;
	}
	printf("Failed to load %s\n", filename);
	return 0;
} else {
	if (*loaded == 1)
		deallocmatrix(*pixelmatrix, *height);
	fseek(photo, 1, SEEK_SET);
	fscanf(photo, "%d", type);
	fscanf(photo, "%d", width);
	fscanf(photo, "%d", height);
	fscanf(photo, "%d ", maxpixelvalue);
	*current_pos = ftell(photo);
	fclose(photo);
	if (*type == 2)
		readp2(width, height, pixelmatrix, filename, current_pos, loaded);
	else if (*type == 3)
		readp3(width, height, pixelmatrix, filename, current_pos, loaded);
	else if (*type == 5)
		readp5(width, height, pixelmatrix, filename, current_pos, loaded);
	else if (*type == 6)
		readp6(width, height, pixelmatrix, filename, current_pos, loaded);
	}
return 0;
}

//functia verifica daca unghiul de la comanda ROTATE este valid
int isvalidangle(int c)
{
if (c % 90 == 0 && (c >= -360 && c <= 360))
	return 1;
return 0;
}

//functia verifica daca numarul de binuri pentru comanda EQUALIZE este valid
int checksquare(int c)
{
if (c == 2 || c == 4 || c == 8 || c == 16 || c == 32 || c == 64)
	return 1;
if (c == 128 || c == 256)
	return 1;
return 0;
}

//functia compara si interschimba doua valori
void switch_compare(int *a, int *b)
{
if (*a > *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	}
}

//functia de salvare a imaginilor
int save(char *name, int **pixelmatrix, int ascii, int height, int width,
		 int maxpixelvalue, int type)
{
FILE *out;
int writtentype = type;
out = fopen(name, "w");
if (ascii == 0 && (type == 2 || type == 3))
	writtentype = writtentype + 3;
if (ascii == 1 && (type == 6 || type == 5))
	writtentype = writtentype - 3;

fprintf(out, "P%d\n", writtentype);
fprintf(out, "%d %d\n", width, height);
fprintf(out, "%d\n", maxpixelvalue);
if (writtentype == 2) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			fprintf(out, "%d ", pixelmatrix[i][j]);
		fprintf(out, "\n");
	}
}

if (writtentype == 3) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * 3; j++)
			fprintf(out, "%d ", pixelmatrix[i][j]);
		fprintf(out, "\n");
	}
}

if (ascii == 1) {
	fclose(out);
	printf("Saved %s\n", name);
	return 0;
}

if (ascii == 0 && (type == 5 || type == 6)) {
	fclose(out);
	out = fopen(name, "ab");
}

if (writtentype == 5) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			fwrite(&pixelmatrix[i][j], sizeof(unsigned char), 1, out);
	}
}

if (writtentype == 6) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * 3; j++)
			fwrite(&pixelmatrix[i][j], sizeof(unsigned char), 1, out);
	}
}

if (ascii == 0)
	fclose(out);
printf("Saved %s\n", name);
return 0;
}

int issascii(char *str1, char *str2, int loaded, int **pixelmatrix, int height,
			 int width, int maxpixelvalue, int type)
{
	if (loaded == 0) {
		printf("No image loaded\n");
		return 0;
	}
	int ascii;
	if (loaded == 1) {
		if (strcmp(str2, "ascii") == 0 && str2[0] != '\0')
			ascii = 1;
		else
			ascii = 0;
	}
	save(str1, pixelmatrix, ascii, height, width, maxpixelvalue, type);
	return 0;
}

int isnumber(char *str)
{
int corect = 1;
for (int r = 0; r < (int)strlen(str); r++)
	if (isdigit(str[r]) == 0) {
		corect = 0;
		break;
	}
return corect;
}

int issletter(char *str)
{
int corect = 1;
for (int r = 1; r < (int)strlen(str); r++)
	if (isalpha(str[r]) == 0) {
		corect = 0;
		break;
	}

return corect;
}

int correctselect(char *xx1, char *yy1, char *xx2, char *yy2, int height,
				  int width)
{
if (xx1[0] == '\0' || xx2[0] == '\0' || yy1[0] == '\0' || yy2[0] == '\0') {
	printf("Invalid command\n");
	return 2;
}

if (!isnumber(xx1) || !isnumber(yy2) || !isnumber(xx2) || !isnumber(yy1)) {
	printf("Invalid set of coordinates\n");
	return 0; }

int x1, y1, x2, y2;

if (strstr(xx1, "-"))
	x1 = -atoi(xx1);
else
	x1 = atoi(xx1);

if (strstr(xx2, "-"))
	x2 = -atoi(xx2);
else
	x2 = atoi(xx2);

if (strstr(yy1, "-"))
	y1 = -atoi(yy1);
else
	y1 = atoi(yy1);

if (strstr(yy2, "-"))
	y2 = -atoi(yy2);
else
	y2 = atoi(yy2);
if (x1 == x2 || y1 == y2) {
	printf("Invalid set of coordinates\n");
	return 0; }
if (x1 < 0 || y1 < 0 || y2 < 0 || x2 < 0) {
	printf("Invalid set of coordinates\n");
	return 0; }
if (x1 > width || y1 > height || y2 > height || x2 > width) {
	printf("Invalid set of coordinates\n");
	return 0; }
return 1;
}

int histogram(char *x, char *y, char *z, int width, int height,
			  int **pixelmatrix, int type, int maxpixelvalue, int loaded)
{
if (loaded == 0) {
	printf("No image loaded\n");
	return 0;
}

int i, j;
double starsnumber = 0.0;

if (z[0] != '\0' || x[0] == '\0' || y[0] == '\0') {
	printf("Invalid command\n");
	return 0;
}

if (type != 2 && type != 5) {
	printf("Black and white image needed\n");
	return 0;
}

if (!isnumber(x) || !isnumber(y)) {
	printf("Invalid set of parameters\n");
	return 0;
}

int stars = atoi(x);
int bins = atoi(y);

if (!checksquare(bins)) {
	printf("Invalid set of parameters\n");
	return 0;
}

int *frec = (int *)calloc(maxpixelvalue + 1, sizeof(int));
if (!frec) {
	printf("no more mem");
	exit(EXIT_FAILURE);
}

int interval = 256 / bins;
double max = 0.0;

int *frec_interval_sum = (int *)calloc(bins + 1, sizeof(int));
if (!frec_interval_sum) {
	printf("no more mem");
	exit(EXIT_FAILURE);
}

int counter = 0, counter_vect = 0;
int suminterval;
suminterval = 0;
for (i = 0; i < height; i++)
	for (j = 0; j < width; j++)
		frec[pixelmatrix[i][j]]++;

for (i = 0; i < 256; i++) {
	suminterval += frec[i];
	counter++;
	if (counter == interval) {
		counter = 0;
		frec_interval_sum[counter_vect] = suminterval;
		if (frec_interval_sum[counter_vect] > max)
			max = frec_interval_sum[counter_vect];
		suminterval = 0;
		counter_vect++;
	}
}

for (i = 0; i < bins; i++) {
	starsnumber = (frec_interval_sum[i] / max) * stars;
	printf("%d\t|\t", (int)floor(starsnumber));
	for (j = 0; j < floor(starsnumber); j++)
		printf("*");
	printf("\n");
}

if (frec)
	free(frec);
if (frec_interval_sum)
	free(frec_interval_sum);
return 0;
}

int crop(int ***pixelmatrix, int *height, int *width, struct selectie coords,
		 int *loaded, int *type)
{
if (*loaded == 0) {
	printf("No image loaded\n");
	return 0;
}

int i, j, storedwidth;
int newheight = coords.y2 - coords.y1;
int newwidth = coords.x2 - coords.x1;
int **copy;
storedwidth = newwidth;

if (*type == 3 || *type == 6) {
	storedwidth = storedwidth * 3;
	coords.x1 *= 3;
	coords.x2 *= 3;
}

copy = (int **)calloc(newheight, sizeof(int *));
if (!copy) {  // daca nu pot aloca, opresc executia si afisez un mesaj
	fprintf(stderr, "calloc() for matrix failed\n");
	return 0;
}

for (int i = 0; i < newheight; i++) {
	copy[i] = (int *)calloc(storedwidth, sizeof(int));
	if (!copy[i]) {
		fprintf(stderr, "calloc() for line %d failed\n", i);
		for (j = 0; j < i; j++)
			free(copy[j]);
		free(copy);
		return 0;
	}
}

for (i = coords.y1; i < coords.y2; i++)
	for (j = coords.x1; j < coords.x2; j++)
		copy[i - coords.y1][j - coords.x1] = (*pixelmatrix)[i][j];

deallocmatrix(*pixelmatrix, *height);

*height = newheight;
*width = newwidth;

*pixelmatrix = (int **)calloc(newheight, sizeof(int *));
if (!copy) {
	fprintf(stderr, "calloc() for matrix failed\n");
	return 0;
}

for (int i = 0; i < newheight; i++)
	(*pixelmatrix)[i] = (int *)calloc(storedwidth, sizeof(int));

for (int i = 0; i < *height; i++)
	for (int j = 0; j < storedwidth; j++)
		(*pixelmatrix)[i][j] = copy[i][j];

deallocmatrix(copy, newheight);
printf("Image cropped\n");

return 0;
}

void edge(int ***pixelmatrix, int height, int width, struct selectie coords)
{
int **R = (int **)calloc(height, sizeof(int *));
int **aux_R = (int **)calloc(height, sizeof(int *));
int **G = (int **)calloc(height, sizeof(int *));
int **aux_G = (int **)calloc(height, sizeof(int *));
int **B = (int **)calloc(height, sizeof(int *));
int **aux_B = (int **)calloc(height, sizeof(int *));

for (int i = 0; i < height; i++) {
	R[i] = (int *)calloc(width, sizeof(int));
	aux_R[i] = (int *)calloc(width, sizeof(int));
	G[i] = (int *)calloc(width, sizeof(int));
	aux_G[i] = (int *)calloc(width, sizeof(int));
	B[i] = (int *)calloc(width, sizeof(int));
	aux_B[i] = (int *)calloc(width, sizeof(int));
}

int r, s;

if (coords.isselected == 0) {
	coords.x1 = 0;
	coords.x2 = width;
	coords.y1 = 0;
	coords.y2 = height;
}

for (int i = 0; i < height; i++) {
	memset(aux_R[i], -1, width * sizeof(int));
	memset(aux_G[i], -1, width * sizeof(int));
	memset(aux_B[i], -1, width * sizeof(int));
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		R[i][c] = (*pixelmatrix)[i][j];
		G[i][c] = (*pixelmatrix)[i][j + 1];
		B[i][c] = (*pixelmatrix)[i][j + 2];
	}
}

int sumpixels[3][3] = {0}, finalpixel = 0;
int tempx1, tempx2, tempy1, tempy2;

tempx1 = coords.x1;
tempx2 = coords.x2;
tempy1 = coords.y1;
tempy2 = coords.y2;

if (coords.x1 == 0)
	tempx1 = 1;
if (coords.x2 == width)
	tempx2 = width - 1;
if (coords.y1 == 0)
	tempy1 = 1;
if (coords.y2 == height)
	tempy2 = height - 1;

for (int i = tempy1; i < tempy2; i++) {
	for (int j = tempx1; j < tempx2; j++) {
		sumpixels[0][0] = -1 * R[i - 1][j - 1];
		sumpixels[0][1] = -1 * R[i - 1][j];
		sumpixels[0][2] = -1 * R[i - 1][j + 1];
		sumpixels[1][0] = -1 * R[i][j - 1];
		sumpixels[1][1] = 8 * R[i][j];
		sumpixels[1][2] = -1 * R[i][j + 1];
		sumpixels[2][0] = -1 * R[i + 1][j - 1];
		sumpixels[2][1] = -1 * R[i + 1][j];
		sumpixels[2][2] = -1 * R[i + 1][j + 1];
		finalpixel = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];

		aux_R[i][j] = clamp(finalpixel);
		finalpixel = 0;

		sumpixels[0][0] = -1 * G[i - 1][j - 1];
		sumpixels[0][1] = -1 * G[i - 1][j];
		sumpixels[0][2] = -1 * G[i - 1][j + 1];
		sumpixels[1][0] = -1 * G[i][j - 1];
		sumpixels[1][1] = 8 * G[i][j];
		sumpixels[1][2] = -1 * G[i][j + 1];
		sumpixels[2][0] = -1 * G[i + 1][j - 1];
		sumpixels[2][1] = -1 * G[i + 1][j];
		sumpixels[2][2] = -1 * G[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];

		aux_G[i][j] = clamp(finalpixel);
		finalpixel = 0;

		sumpixels[0][0] = -1 * B[i - 1][j - 1];
		sumpixels[0][1] = -1 * B[i - 1][j];
		sumpixels[0][2] = -1 * B[i - 1][j + 1];
		sumpixels[1][0] = -1 * B[i][j - 1];
		sumpixels[1][1] = 8 * B[i][j];
		sumpixels[1][2] = -1 * B[i][j + 1];
		sumpixels[2][0] = -1 * B[i + 1][j - 1];
		sumpixels[2][1] = -1 * B[i + 1][j];
		sumpixels[2][2] = -1 * B[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_B[i][j] = clamp(finalpixel);
		finalpixel = 0;
	}
}

for (int i = 0; i < height; i++)
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		if (aux_R[i][c] != -1)
			(*pixelmatrix)[i][j] = aux_R[i][c];
		if (aux_G[i][c] != -1)
			(*pixelmatrix)[i][j + 1] = aux_G[i][c];
		if (aux_B[i][c] != -1)
			(*pixelmatrix)[i][j + 2] = aux_B[i][c];
	}

deallocmatrix(R, height);
deallocmatrix(aux_R, height);
deallocmatrix(G, height);
deallocmatrix(aux_G, height);
deallocmatrix(B, height);
deallocmatrix(aux_B, height);

printf("APPLY EDGE done\n");
}

void sharpen(int ***pixelmatrix, int height, int width, struct selectie coords)
{
int **R = (int **)calloc(height, sizeof(int *));
int **aux_R = (int **)calloc(height, sizeof(int *));
int **G = (int **)calloc(height, sizeof(int *));
int **aux_G = (int **)calloc(height, sizeof(int *));
int **B = (int **)calloc(height, sizeof(int *));
int **aux_B = (int **)calloc(height, sizeof(int *));

for (int i = 0; i < height; i++) {
	R[i] = (int *)calloc(width, sizeof(int));
	aux_R[i] = (int *)calloc(width, sizeof(int));
	G[i] = (int *)calloc(width, sizeof(int));
	aux_G[i] = (int *)calloc(width, sizeof(int));
	B[i] = (int *)calloc(width, sizeof(int));
	aux_B[i] = (int *)calloc(width, sizeof(int));
}

int r, s;
if (coords.isselected == 0) {
	coords.x1 = 0;
	coords.x2 = width;
	coords.y1 = 0;
	coords.y2 = height;
}

for (int i = 0; i < height; i++) {
	memset(aux_R[i], -1, width * sizeof(int));
	memset(aux_G[i], -1, width * sizeof(int));
	memset(aux_B[i], -1, width * sizeof(int));
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		R[i][c] = (*pixelmatrix)[i][j];
		G[i][c] = (*pixelmatrix)[i][j + 1];
		B[i][c] = (*pixelmatrix)[i][j + 2];
	}
}

int sumpixels[3][3] = {0}, finalpixel = 0;
int tempx1, tempx2, tempy1, tempy2;

tempx1 = coords.x1;
tempx2 = coords.x2;
tempy1 = coords.y1;
tempy2 = coords.y2;

if (coords.x1 == 0)
	tempx1 = 1;
if (coords.x2 == width)
	tempx2 = width - 1;
if (coords.y1 == 0)
	tempy1 = 1;
if (coords.y2 == height)
	tempy2 = height - 1;

for (int i = tempy1; i < tempy2; i++) {
	for (int j = tempx1; j < tempx2; j++) {
		sumpixels[0][0] = 0;
		sumpixels[0][1] = -1 * R[i - 1][j];
		sumpixels[0][2] = 0;
		sumpixels[1][0] = -1 * R[i][j - 1];
		sumpixels[1][1] = 5 * R[i][j];
		sumpixels[1][2] = -1 * R[i][j + 1];
		sumpixels[2][0] = 0;
		sumpixels[2][1] = -1 * R[i + 1][j];
		sumpixels[2][2] = 0;
		finalpixel = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		finalpixel = clamp(finalpixel);
		aux_R[i][j] = finalpixel;
		finalpixel = 0;

		sumpixels[0][0] = 0;
		sumpixels[0][1] = -1 * G[i - 1][j];
		sumpixels[0][2] = 0;
		sumpixels[1][0] = -1 * G[i][j - 1];
		sumpixels[1][1] = 5 * G[i][j];
		sumpixels[1][2] = -1 * G[i][j + 1];
		sumpixels[2][0] = 0;
		sumpixels[2][1] = -1 * G[i + 1][j];
		sumpixels[2][2] = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		finalpixel = clamp(finalpixel);
		aux_G[i][j] = finalpixel;
		finalpixel = 0;

		sumpixels[0][0] = 0;
		sumpixels[0][1] = -1 * B[i - 1][j];
		sumpixels[0][2] = 0;
		sumpixels[1][0] = -1 * B[i][j - 1];
		sumpixels[1][1] = 5 * B[i][j];
		sumpixels[1][2] = -1 * B[i][j + 1];
		sumpixels[2][0] = 0;
		sumpixels[2][1] = -1 * B[i + 1][j];
		sumpixels[2][2] = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];

		finalpixel = clamp(finalpixel);
		aux_B[i][j] = finalpixel;
		finalpixel = 0;
	}
}

for (int i = 0; i < height; i++)
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		if (aux_R[i][c] != -1)
			(*pixelmatrix)[i][j] = aux_R[i][c];
		if (aux_G[i][c] != -1)
			(*pixelmatrix)[i][j + 1] = aux_G[i][c];
		if (aux_B[i][c] != -1)
			(*pixelmatrix)[i][j + 2] = aux_B[i][c];
	}

deallocmatrix(R, height);
deallocmatrix(aux_R, height);
deallocmatrix(G, height);
deallocmatrix(aux_G, height);
deallocmatrix(B, height);
deallocmatrix(aux_B, height);

printf("APPLY SHARPEN done\n");
}

void blur(int ***pixelmatrix, int height, int width, struct selectie coords)
{
int **R = (int **)calloc(height, sizeof(int *));
int **aux_R = (int **)calloc(height, sizeof(int *));
int **G = (int **)calloc(height, sizeof(int *));
int **aux_G = (int **)calloc(height, sizeof(int *));
int **B = (int **)calloc(height, sizeof(int *));
int **aux_B = (int **)calloc(height, sizeof(int *));

for (int i = 0; i < height; i++) {
	R[i] = (int *)calloc(width, sizeof(int));
	aux_R[i] = (int *)calloc(width, sizeof(int));
	G[i] = (int *)calloc(width, sizeof(int));
	aux_G[i] = (int *)calloc(width, sizeof(int));
	B[i] = (int *)calloc(width, sizeof(int));
	aux_B[i] = (int *)calloc(width, sizeof(int));
}

int r, s;

if (coords.isselected == 0) {
	coords.x1 = 0;
	coords.x2 = width;
	coords.y1 = 0;
	coords.y2 = height;
}

for (int i = 0; i < height; i++) {
	memset(aux_R[i], -1, width * sizeof(int));
	memset(aux_G[i], -1, width * sizeof(int));
	memset(aux_B[i], -1, width * sizeof(int));
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		R[i][c] = (*pixelmatrix)[i][j];
		G[i][c] = (*pixelmatrix)[i][j + 1];
		B[i][c] = (*pixelmatrix)[i][j + 2];
	}
}

int sumpixels[3][3] = {0};
double finalpixel;

int tempx1, tempx2, tempy1, tempy2;
tempx1 = coords.x1;
tempx2 = coords.x2;
tempy1 = coords.y1;
tempy2 = coords.y2;

if (coords.x1 == 0)
	tempx1 = 1;
if (coords.x2 == width)
	tempx2 = width - 1;
if (coords.y1 == 0)
	tempy1 = 1;
if (coords.y2 == height)
	tempy2 = height - 1;

for (int i = tempy1; i < tempy2; i++) {
	for (int j = tempx1; j < tempx2; j++) {
		sumpixels[0][0] = R[i - 1][j - 1];
		sumpixels[0][1] = R[i - 1][j];
		sumpixels[0][2] = R[i - 1][j + 1];
		sumpixels[1][0] = R[i][j - 1];
		sumpixels[1][1] = R[i][j];
		sumpixels[1][2] = R[i][j + 1];
		sumpixels[2][0] = R[i + 1][j - 1];
		sumpixels[2][1] = R[i + 1][j];
		sumpixels[2][2] = R[i + 1][j + 1];
		finalpixel = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_R[i][j] = clamp(round(finalpixel / 9.0));
		finalpixel = 0.0;

		sumpixels[0][0] = G[i - 1][j - 1];
		sumpixels[0][1] = G[i - 1][j];
		sumpixels[0][2] = G[i - 1][j + 1];
		sumpixels[1][0] = G[i][j - 1];
		sumpixels[1][1] = G[i][j];
		sumpixels[1][2] = G[i][j + 1];
		sumpixels[2][0] = G[i + 1][j - 1];
		sumpixels[2][1] = G[i + 1][j];
		sumpixels[2][2] = G[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_G[i][j] = clamp(round(finalpixel / 9.0));
		finalpixel = 0.0;

		sumpixels[0][0] = B[i - 1][j - 1];
		sumpixels[0][1] = B[i - 1][j];
		sumpixels[0][2] = B[i - 1][j + 1];
		sumpixels[1][0] = B[i][j - 1];
		sumpixels[1][1] = B[i][j];
		sumpixels[1][2] = B[i][j + 1];
		sumpixels[2][0] = B[i + 1][j - 1];
		sumpixels[2][1] = B[i + 1][j];
		sumpixels[2][2] = B[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_B[i][j] = (int)clamp(round(finalpixel / 9.0));
		finalpixel = 0.0;
	}
}

for (int i = 0; i < height; i++)
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		if (aux_R[i][c] != -1)
			(*pixelmatrix)[i][j] = aux_R[i][c];
		if (aux_G[i][c] != -1)
			(*pixelmatrix)[i][j + 1] = aux_G[i][c];
		if (aux_B[i][c] != -1)
			(*pixelmatrix)[i][j + 2] = aux_B[i][c];
	}

deallocmatrix(R, height);
deallocmatrix(aux_R, height);
deallocmatrix(G, height);
deallocmatrix(aux_G, height);
deallocmatrix(B, height);
deallocmatrix(aux_B, height);

printf("APPLY BLUR done\n");
}

void gaussian_blur(int ***pixelmatrix, int height, int width,
				   struct selectie coords)
{
int **R = (int **)calloc(height, sizeof(int *));
int **aux_R = (int **)calloc(height, sizeof(int *));
int **G = (int **)calloc(height, sizeof(int *));
int **aux_G = (int **)calloc(height, sizeof(int *));
int **B = (int **)calloc(height, sizeof(int *));
int **aux_B = (int **)calloc(height, sizeof(int *));

for (int i = 0; i < height; i++) {
	R[i] = (int *)calloc(width, sizeof(int));
	aux_R[i] = (int *)calloc(width, sizeof(int));
	G[i] = (int *)calloc(width, sizeof(int));
	aux_G[i] = (int *)calloc(width, sizeof(int));
	B[i] = (int *)calloc(width, sizeof(int));
	aux_B[i] = (int *)calloc(width, sizeof(int));
}

int r, s;

if (coords.isselected == 0) {
	coords.x1 = 0;
	coords.x2 = width;
	coords.y1 = 0;
	coords.y2 = height;
}

for (int i = 0; i < height; i++) {
	memset(aux_R[i], -1, width * sizeof(int));
	memset(aux_G[i], -1, width * sizeof(int));
	memset(aux_B[i], -1, width * sizeof(int));
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		R[i][c] = (*pixelmatrix)[i][j];
		G[i][c] = (*pixelmatrix)[i][j + 1];
		B[i][c] = (*pixelmatrix)[i][j + 2];
	}
}

int sumpixels[3][3] = {0};
double finalpixel = 0.0;

int tempx1, tempx2, tempy1, tempy2;
tempx1 = coords.x1;
tempx2 = coords.x2;
tempy1 = coords.y1;
tempy2 = coords.y2;

if (coords.x1 == 0)
	tempx1 = 1;
if (coords.x2 == width)
	tempx2 = width - 1;
if (coords.y1 == 0)
	tempy1 = 1;
if (coords.y2 == height)
	tempy2 = height - 1;

for (int i = tempy1; i < tempy2; i++) {
	for (int j = tempx1; j < tempx2; j++) {
		sumpixels[0][0] = R[i - 1][j - 1];
		sumpixels[0][1] = 2 * R[i - 1][j];
		sumpixels[0][2] = R[i - 1][j + 1];
		sumpixels[1][0] = 2 * R[i][j - 1];
		sumpixels[1][1] = 4 * R[i][j];
		sumpixels[1][2] = 2 * R[i][j + 1];
		sumpixels[2][0] = R[i + 1][j - 1];
		sumpixels[2][1] = 2 * R[i + 1][j];
		sumpixels[2][2] = R[i + 1][j + 1];
		finalpixel = 0;
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_R[i][j] = (int)clamp(round(finalpixel / 16.0));
		finalpixel = 0.0;

		sumpixels[0][0] = G[i - 1][j - 1];
		sumpixels[0][1] = 2 * G[i - 1][j];
		sumpixels[0][2] = G[i - 1][j + 1];
		sumpixels[1][0] = 2 * G[i][j - 1];
		sumpixels[1][1] = 4 * G[i][j];
		sumpixels[1][2] = 2 * G[i][j + 1];
		sumpixels[2][0] = G[i + 1][j - 1];
		sumpixels[2][1] = 2 * G[i + 1][j];
		sumpixels[2][2] = G[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_G[i][j] = (int)clamp(round(finalpixel / 16.0));
		finalpixel = 0.0;

		sumpixels[0][0] = B[i - 1][j - 1];
		sumpixels[0][1] = 2 * B[i - 1][j];
		sumpixels[0][2] = B[i - 1][j + 1];
		sumpixels[1][0] = 2 * B[i][j - 1];
		sumpixels[1][1] = 4 * B[i][j];
		sumpixels[1][2] = 2 * B[i][j + 1];
		sumpixels[2][0] = B[i + 1][j - 1];
		sumpixels[2][1] = 2 * B[i + 1][j];
		sumpixels[2][2] = B[i + 1][j + 1];
		for (r = 0; r < 3; r++)
			for (s = 0; s < 3; s++)
				finalpixel = finalpixel + sumpixels[r][s];
		aux_B[i][j] = (int)clamp(round(finalpixel / 16.0));
		finalpixel = 0.0;
	}
}

for (int i = 0; i < height; i++)
	for (int j = 0, c = 0; j < width * 3; j = j + 3, c++) {
		if (aux_R[i][c] != -1)
			(*pixelmatrix)[i][j] = aux_R[i][c];
		if (aux_G[i][c] != -1)
			(*pixelmatrix)[i][j + 1] = aux_G[i][c];
		if (aux_B[i][c] != -1)
			(*pixelmatrix)[i][j + 2] = aux_B[i][c];
	}

deallocmatrix(R, height);
deallocmatrix(aux_R, height);
deallocmatrix(G, height);
deallocmatrix(aux_G, height);
deallocmatrix(B, height);
deallocmatrix(aux_B, height);

printf("APPLY GAUSSIAN_BLUR done\n");
}

int apply(char *comm, int ***pixelmatrix, int height, int width, int type,
		  int loaded, struct selectie coords)
{
if (loaded == 0) {
	printf("No image loaded\n");
	return 0;
}

if (comm[0] == '\0') {
	printf("Invalid command\n");
	return 0;
}

if (type != 6 && type != 3) {
	printf("Easy, Charlie Chaplin\n");
	return 0;
}

if (strcmp(comm, "EDGE") == 0) {
	edge(pixelmatrix, height, width, coords);
	return 0;
} else if (strcmp(comm, "SHARPEN") == 0) {
	sharpen(pixelmatrix, height, width, coords);
	return 0;
} else if (strcmp(comm, "BLUR") == 0) {
	blur(pixelmatrix, height, width, coords);
	return 0;
} else if (strcmp(comm, "GAUSSIAN_BLUR") == 0) {
	gaussian_blur(pixelmatrix, height, width, coords);
	return 0;
} else {
	printf("APPLY parameter invalid\n"); }

return 0;
}

double eqsum(double max, double frec[])
{
int r;
double sum = 0.0;

for (r = 0; r < max; r++)
	sum = sum + frec[r];
return sum;
}

int equalize(int ***pixelmatrix, int height, int width, int type, int loaded,
			 int maxvalue)
{
if (loaded == 0) {
	printf("No image loaded\n");
	return 0;
}

if (type != 2 && type != 5) {
	printf("Black and white image needed\n");
	return 0;
}

int i, j;
double eq = 255.0 / (height * width);
double *frec = (double *)calloc(maxvalue + 1, sizeof(double));
double **auxpixelmatrix = (double **)calloc(height, sizeof(double *));

if (!frec) {
	printf("no more memory");
	exit(EXIT_FAILURE);
}

for (i = 0; i < height; i++) {
	auxpixelmatrix[i] = (double *)calloc(width, sizeof(double));
	for (j = 0; j < width; j++)
		frec[(*pixelmatrix)[i][j]]++;
}

for (i = 0; i < height; i++)
	for (j = 0; j < width; j++)
		auxpixelmatrix[i][j] = (*pixelmatrix)[i][j];

for (i = 0; i < height; i++)
	for (j = 0; j < width; j++) {
		(*pixelmatrix)[i][j] =
			clamp(round(eq * eqsum(auxpixelmatrix[i][j], frec)) + 5);
	}

free(frec);

deallocmatrix((int **)auxpixelmatrix, height);

printf("Equalize done\n");

return 0;
}

void rotatecolor(int ***pixelmatrix, int intangle, int beginh, int endh,
				 int beginw, int endw, int times, int negative)
{
int sizeh = endh - beginh;
int sizew = endw - beginw;
int **R = (int **)calloc(sizeh, sizeof(int *));
int **G = (int **)calloc(sizeh, sizeof(int *));
int **B = (int **)calloc(sizeh, sizeof(int *));
for (int i = 0; i < sizeh; i++) {
	R[i] = (int *)calloc(sizew, sizeof(int));
	G[i] = (int *)calloc(sizew, sizeof(int));
	B[i] = (int *)calloc(sizew, sizeof(int));
}

for (int i = beginh, r = 0; i < endh; i++, r++) {
	for (int j = beginw * 3, c = 0; j < endw * 3; j = j + 3, c++) {
		R[r][c] = (*pixelmatrix)[i][j];
		G[r][c] = (*pixelmatrix)[i][j + 1];
		B[r][c] = (*pixelmatrix)[i][j + 2];
	}
}

for (int g = 0; g < times; g++)
	// Consider all squares one by one
	for (int i = 0; i < sizeh / 2; i++) {
		// Consider elements in group
		// of 4 in current square
		for (int j = i; j < sizeh - i - 1; j++) {
			// Store current cell in
			// temp variablef
			int tempr = R[i][j];
			int tempg = G[i][j];
			int tempb = B[i][j];
			// Move values from right to top
			R[i][j] = R[j][sizeh - 1 - i];
			G[i][j] = G[j][sizeh - 1 - i];
			B[i][j] = B[j][sizeh - 1 - i];
			// Move values from bottom to right
			R[j][sizeh - 1 - i] = R[sizeh - 1 - i][sizeh - 1 - j];
			G[j][sizeh - 1 - i] = G[sizeh - 1 - i][sizeh - 1 - j];
			B[j][sizeh - 1 - i] = B[sizeh - 1 - i][sizeh - 1 - j];
			// Move values from left to bottom
			R[sizeh - 1 - i][sizeh - 1 - j] = R[sizeh - 1 - j][i];
			G[sizeh - 1 - i][sizeh - 1 - j] = G[sizeh - 1 - j][i];
			B[sizeh - 1 - i][sizeh - 1 - j] = B[sizeh - 1 - j][i];
			// Assign temp to left
			R[sizeh - 1 - j][i] = tempr;
			G[sizeh - 1 - j][i] = tempg;
			B[sizeh - 1 - j][i] = tempb;
			}
	}
	// i = 0 pt selectie cu margine j la fel
for (int i = beginh, r = 0; i < endh; i++, r++)
	for (int j = beginw * 3, c = 0; j < endw * 3; j = j + 3, c++) {
		(*pixelmatrix)[i][j] = R[r][c];
		(*pixelmatrix)[i][j + 1] = G[r][c];
		(*pixelmatrix)[i][j + 2] = B[r][c];
	}

deallocmatrix(R, sizeh);
deallocmatrix(G, sizeh);
deallocmatrix(B, sizeh);
if (negative == 1)
	printf("Rotated -%d\n", intangle);
else
	printf("Rotated %d\n", intangle);
}

void rotatebw(int ***pixelmatrix, int times, int beginh, int sizeh,
			  int negative, int intangle)
{
for (int g = 0; g < times; g++)
// Consider all squares one by one
	for (int i = beginh; i < sizeh / 2; i++) {
		// Consider elements in group
		// of 4 in current square
		for (int j = i; j < sizeh - i - 1; j++) {
			// Store current cell in
			// temp variablef
			int temp = (*pixelmatrix)[i][j];
			// Move values from right to top
			(*pixelmatrix)[i][j] = (*pixelmatrix)[j][sizeh - 1 - i];
			// Move values from bottom to right
			(*pixelmatrix)[j][sizeh - 1 - i] =
				(*pixelmatrix)[sizeh - 1 - i][sizeh - 1 - j];
			// Move values from left to bottom
			(*pixelmatrix)[sizeh - 1 - i][sizeh - 1 - j] =
				(*pixelmatrix)[sizeh - 1 - j][i];
			// Assign temp to left
			(*pixelmatrix)[sizeh - 1 - j][i] = temp;
		}
}

if (negative == 1)
	printf("Rotated -%d\n", intangle);
else
	printf("Rotated %d\n", intangle);
}

int rotate(int ***pixelmatrix, int height, int width, struct selectie coords,
		   int loaded, char *angle, int type)
{
if (loaded == 0) {
	printf("No image loaded\n");
	return 0;
}

int beginh, endh, beginw, endw;
int intangle = 0, negative = 0, times;
if (!isvalidangle(atoi(angle))) {
	printf("Unsupported rotation angle\n");
	return 0;
}

if (strstr(angle, "-")) {
	negative = 1;
	intangle = -atoi(angle);
} else {
	intangle = atoi(angle); }

if (intangle == 360) {
	if (negative == 1)
		printf("Rotated -360\n");
	else
		printf("Rotated 360\n");
	return 1;
}

if (intangle == 270 && negative == 0)
	times = 1;
if (intangle == 270 && negative == 1)
	times = 3;
if (intangle == 180)
	times = 2;
if (intangle == 90 && negative == 1)
	times = 1;
if (intangle == 90 && negative == 0)
	times = 3;

beginh = coords.y1;
endh = coords.y2;
beginw = coords.x1;
endw = coords.x2;

if (coords.isselected == 0) {
	beginh = 0;
	endh = height;
	beginw = 0;
	endw = width;
}

if ((endh - beginh) != (endw - beginw) &&coords.isselected == 0) {
	if (negative == 1)
		printf("Rotated -%d\n", intangle);
	if (negative == 0)
		printf("Rotated %d\n", intangle);
	return 0;
}

if ((endh - beginh) != (endw - beginw) &&coords.isselected == 1) {
	printf("The selection must be square\n");
	return 0;
}

int sizeh = endh - beginh;

if (type == 3 || type == 6) {
	rotatecolor(pixelmatrix, intangle, beginh, endh, beginw, endw, times,
				negative);
		return 1;
} else if (type == 2 || type == 5) {
	rotatebw(pixelmatrix, times, beginh, sizeh, negative, intangle);
	return 1;
}

return 1;
}

int main(void)
{
struct selectie coords;
char task[61], sep[] = " ", *p, cuvinte[5][40]; coords.isselected = 2;
int type, width, height, maxpixelvalue, current_pos, **pixelmatrix, i,
	loaded = 0, totwords = 0;
while (1) {
	for (i = 0; i <= 4; i++)
		cuvinte[i][0] = '\0';
	totwords = 0;
	fgets(task, 60, stdin);
	task[strcspn(task, "\n")] = 0;
	p = strtok(task, sep);
	while (p != 0) {
		strcpy(cuvinte[totwords], p);
		totwords++;
		p = strtok(NULL, sep);
	}
	if (!strcmp(cuvinte[0], "LOAD")) {
		openphoto(&type, &width, &height, &maxpixelvalue, cuvinte[1],
				  &current_pos, &pixelmatrix, &loaded);
		selectarea(loaded, &coords.isselected);
		continue;
	} else if (!strcmp(cuvinte[0], "SELECT")) {
		if (loaded == 0) {
			printf("No image loaded\n");
			continue;
		} else {
			if (!strcmp(cuvinte[1], "ALL")) {
				printf("Selected ALL\n");
				coords.isselected = 0;
				continue;
			} else if (isalpha(cuvinte[4][0]) != 0) {
				continue;
			} else if (correctselect(cuvinte[1], cuvinte[2], cuvinte[3],
										cuvinte[4], height, width) == 0) {
				continue;
			} else if (correctselect(cuvinte[1], cuvinte[2], cuvinte[3],
										cuvinte[4], height, width) == 2) {
				continue; }
			coords.x1 = atoi(cuvinte[1]); coords.y1 = atoi(cuvinte[2]);
			coords.x2 = atoi(cuvinte[3]); coords.y2 = atoi(cuvinte[4]);
			coords.isselected = 1;
			switch_compare(&coords.x1, &coords.x2);
			switch_compare(&coords.y1, &coords.y2);
			printf("Selected %d %d %d %d\n", coords.x1, coords.y1, coords.x2,
				   coords.y2);
			continue;
		}
	} else if (!strcmp(cuvinte[0], "HISTOGRAM")) {
		histogram(cuvinte[1], cuvinte[2], cuvinte[3], width, height,
				  pixelmatrix, type, maxpixelvalue, loaded);
		continue;
	} else if (!strcmp(cuvinte[0], "ROTATE")) {
		rotate(&pixelmatrix, height, width, coords, loaded, cuvinte[1], type);
		continue;
	} else if (!strcmp(cuvinte[0], "EQUALIZE")) {
		equalize(&pixelmatrix, height, width, type, loaded, maxpixelvalue);
		continue;
	} else if (!strcmp(cuvinte[0], "CROP")) {
		if (coords.isselected == 1) {
			crop(&pixelmatrix, &height, &width, coords, &loaded, &type);
			coords.isselected = 0;
		} else if (coords.isselected == 0) {
			printf("Image cropped\n");
		} else {
			printf("No image loaded\n"); }
		continue;
	} else if (!strcmp(cuvinte[0], "APPLY")) {
		apply(cuvinte[1], &pixelmatrix, height, width, type, loaded, coords);
		continue;
	} else if (!strcmp(cuvinte[0], "EXIT")) {
		exitfunction(pixelmatrix, height, loaded);
		break;
	} else if (!strcmp(cuvinte[0], "SAVE")) {
		issascii(cuvinte[1], cuvinte[2], loaded, pixelmatrix, height,
				 width, maxpixelvalue, type);
	} else {
		printf("Invalid command\n"); }
	}
}
