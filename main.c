# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include <time.h>


# ifndef TRUE
	# define TRUE (0==0)
	# define FALSE (0!=0)
# endif

char punch[256]="NONE";

FILE *fp;

double reg1=0.0;
char reg1_used=0;
double reg2=0.0;
char reg2_used=0;

double memory[64];
int arg_trace=FALSE;
int arg_display=FALSE;
int arg_dump=FALSE;

void trim(char *s)
{
	int l;

	l = strlen(s) - 1;
	for (;;) {
		if (l < 0)
			break;
		if (s[l] != ' ')
			break;
		s[l] = 0;
		l--;
	}
	if (l == 0)
		return;
	for (;;) {
		if (s[0] == 0)
			break;
		if (s[0] != ' ' && s[0] != '\t')
			break;
		memmove(s, s + 1, strlen(s));
	}
}

int read_one_line(FILE * fp, unsigned char *line)
{
   int c;
   int z;

   z = 0;
   for (;;) {
      c = fgetc(fp);
      if (c == '\n' || c == '\r' || c == EOF) {
         line[z] = 0;
         z = 0;
         break;
      }
      else {
         line[z++] = c;
      }
   }
   return (c);
}

void ucase(char *s) 
{
   int t;

   for (t = 0;; t++) {
      if (s[t] == 0) break;
      s[t] = toupper(s[t]);
   }
}

char *__xpjg_wordptr = NULL;
int __xpjg_wordpos = 0;

void word(char *s, char *ziel, int n)
{
	int anz = 0;
	int t;
	int f = 0;
	int z = 0;
	int start;
	int m = 1;
	int esc = 0;
	int l;

	__xpjg_wordptr = s;

	l = (int)strlen((char *)s);
	for (start = 0; start < l; start++)
		if (s[start] > ' ')
			break;

	for (t = start; t < l; t++) {
		if (s[t] == '\\') {
			if (esc == 0) {
				esc = 1;
				if (anz == n)
					ziel[z++] = '\\';
			}
			else {
				if (anz == n)
					ziel[z++] = '\\';
				esc = 0;
			}
		}
		else {
			if (s[t] == '"' && esc == 0)
				m *= -1;
			if (s[t] == ' ' && m == 1)
				f = 0;
			else
				f++;
			if (f == 1)
				anz++;
			if (anz == n && f > 0) {
				ziel[z++] = s[t];
			}
			if (anz > n && f > 0)
				break;
			esc = 0;
		}
	}		
	ziel[z] = 0;
	__xpjg_wordpos = t;
	l = strlen((char *)ziel) - 1;	
	for (;;) {
		if (l < 1)
			break;
		if (ziel[l] != ' ')
			break;
		ziel[l] = 0;
		l--;
	}
}
/******************************************************************************/
void do_dump(void)
{
	int t;
	int z;
   time_t tsec;
	struct tm *s_tm;

   tsec = time(NULL);
   s_tm = localtime(&tsec);
   s_tm->tm_year += 1900;
   s_tm->tm_mon++;

	printf("**************************   %04d.%02d.%02d\n", 
		s_tm->tm_year, s_tm->tm_mon, s_tm->tm_mday);
	printf("                   *    Post Mortem Dump    *   %02d-%02d-%02d\n",
		s_tm->tm_hour, s_tm->tm_min, s_tm->tm_sec);
	puts("**************************");
	if(reg1_used==0){
		printf("Register 1: <NOT OCCUPIED>\n");
	}
	else{
		printf("Register 1: %f\n", reg1);
	}
	if(reg2_used==0){
		printf("Register 2: <NOT OCCUPIED>\n");
	}
	else{
		printf("Register 2: %f\n", reg2);
	}

	z=0;
	for(t=0; t<64; t++){
		printf(" (%02d)% 10f ", t, memory[t]);
		z++;
		if(z>3){
			puts("");
			z=0;
		}
	}
	puts("");

}

void handle_input_line(char *s)
{
	char zwi[256];
	char w1[256];
	char w2[256];
	int num;
	char number[256];

	if(arg_trace==TRUE){
		printf(">>%s\n", s);
	}

	if(s[0]=='*') return;

	if(s[0]=='#'){
          if (TRUE == arg_display) {
            printf("%s\n", s + 1);
          }
                return;
	}

	strcpy(zwi, s);
	trim(zwi);
	word(zwi, w1, 1);
	ucase(w1);
	word(zwi, w2, 2);
	ucase(w2);

	if(strcmp(w1, "FIN")==0){ 
		puts("Command FIN found, normal program termination.");
                if (TRUE == arg_dump) {
                  do_dump();
                }
                exit(0);
	}
        if (0 == strcmp(w1, "LU")) { 
          printf("Enter a number >");
          read_one_line(fp,NULL);

		  
          if (reg1_used == 1) {
            reg2 = atof(number);
            reg2_used = 1;
            if (arg_trace == TRUE) {
              printf("reg2 is now %f\n", reg2);
            }
          } else {
            reg1 = atof(number);
            reg1_used = 1;
            reg2_used =
                0; 
            reg2 = 0;
            if (arg_trace == TRUE) {
              printf("reg1 is now %f\n", reg1);
            }
          }
          return;
        }
        if(strcmp(w1, "LD")==0){
		printf("reg1: %f\n", reg1);
		reg1_used=0; 
		reg1=0;
		reg2_used=0;
		reg2=0;
		return;
	}
	if(strcmp(w1, "PR")==0){ 
		num=atoi(w2);
		if(num<0 || num>63){
			fprintf(stderr, "Invalid memory address %d, aborting...\n", num);
			exit(5);
		}
		if(reg1_used==0){
			reg1=memory[num];
			reg1_used=1;
		}
		else{
			reg2=memory[num];
			reg2_used=1;
		}
		return;
	}
	if(strcmp(w1, "PR")==0){ 
		num=atoi(w2);
                if (num < 0 || num > 63) {
                  fprintf(stderr, "Invalid memory address %d, aborting...\n",
                          num);
                  exit(5);
                }
                memory[num]=reg1;
		reg1_used=0;
		return;
	}
        if (0 == strcmp(w1, "LM")) {
          reg1 = reg1 * reg2;
          reg2_used = 0;
          reg2 = 0.0;
          return;
        }
        if(strcmp(w1, "LI")==0){ 
		printf("=====================>LI: reg1=%f reg2=%f\n", reg1, reg2);
		reg1=reg1/reg2;
		reg2_used=0;
		reg2=0.0;
		return;
	}
        if (strcmp(w1, "LW") == 0) {
          reg1 = sqrt(reg1);
          return;
        }
        if(strcmp(w1, "LS1")==0){
          reg1 = reg1 + reg2;
          reg2_used = 0;
          reg2 = 0.0;
          return;
	}
	if(strcmp(w1, "LS2")==0){ 
		reg1=reg1-reg2;
		reg2_used=0;
		reg2=0.0;
		return;
	}

	fprintf(stderr, "Unknown command >%s< found, aborting...\n", zwi);
	exit(99);
}

int main(int argc, char **argv)
{
	int t;
	int f;
	char zwi[256];
	char line[256];

	puts("jzd- a Zuse Z3 emulator.");
	puts("---");

	arg_trace=FALSE;
	for(t=1; t<argc; t++){
	   f=0;
		strcpy(zwi, argv[t]);
	   if(f==0 && strncmp(zwi, "-p", 2)==0){
	      strcpy(punch, zwi+2);
	      printf("punch tape set to >%s<\n", punch);
	      f=1;
	   }
	   if(f==0 && strcmp(zwi, "-t")==0){
			arg_trace=TRUE;
	      puts("TRACE is ON");
	      f=1;
	   }
	   if(f==0 && strcmp(zwi, "-v")==0){
	      exit(0);
	   }
	   if(f==0 && strcmp(zwi, "-d")==0){
			arg_display=TRUE;
	      puts("DISPLAY is ON");
	      f=1;
	   }
           if (f == 0 && strcmp(zwi, "-dump") == 0) {
             arg_dump = TRUE;
             puts("DUMP is ON");
             f = 1;
           }
           if(f==0){
	      fprintf(stderr, "pipzusez3: unknown argument >%s<, aborting...\n",
         argv[t]);
	      exit(99);
	   }
	}
	puts("---");
	printf("input  punch tape is >%s<\n", punch);

	fp=fopen(punch, "rb");
	if(fp==NULL){
		fprintf(stderr, 
			"Could not open input punch tape >%s<, aborting..\n", punch);
		exit(1);
	}

	for(;;){
          if ((-1) == read_one_line(fp, NULL )) {
            fprintf(stderr, "Unexpected end of punch tape, aborting..\n");
            exit(4);
          }
            handle_input_line(line);
	}

	fclose(fp);
	if(arg_dump==TRUE){
		do_dump();
	}

	puts("Done.");
	return(0);
}