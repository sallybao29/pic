#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>


int randint(){
  int i;
  int f = open("/dev/urandom", O_RDONLY);
  if (f < 0)
    printf("error %d: %s\n", errno, strerror(errno));
  else
		read(f, &i, sizeof(int));
  close(f);
  return i;  
}


int main(){
	char buff[256];
	int fd, i, j, r, g, b, rand;
  
	fd = open("pic.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		printf("Error %d: %s\n", errno, strerror(errno));

	sprintf(buff, "%s %d %d %d\n", "P3", 500, 500, 255);
	write(fd, buff, strlen(buff));

	rand = (abs(randint())) % 256;
	for (i = 0; i < 500; i++){
		for (j = 0; j < 500; j++){
			r = (rand * (int)(sin((double)(i)))) % 256;
			g = (rand * (int)(cos((double)(j)))) % 256;
			b = (((int)(pow((double)i, 2) + pow((double)j, 2)))) % 256;
			
			sprintf(buff, "%d %d %d ", r, g, b);
			write(fd, buff, strlen(buff));
		}
	}

	close(fd);
	return 0;
}
