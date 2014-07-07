/*
 ============================================================================
 Name        : cc.c
 Author      : kongming
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lookup.h"
#include <assert.h>
#include <stdarg.h>

#define LEN 1000

static struct item *hashtable[LEN];

/**
 * mini printf
 */
void minprintf(char *fmt, ...) {
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'o':
			ival = va_arg(ap, int);
			printf("%o", ival);
			break;
		case 'x':
		case 'X':
			ival = va_arg(ap, int);
			printf("%x", ival);
			break;
		case 'u':
			ival = va_arg(ap, int);
			printf("%u", ival);
			break;
		case 'c':
			ival = va_arg(ap, int);
			putchar(ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			printf("%s", va_arg(ap, char *));
			break;
		case '%':
			putchar('%');
			break;
		default:
			putchar(*p);
			break;

		}
	}
	va_end(ap);
}

static unsigned hash(char *name) {
	unsigned val;
	for (val = 0; *name != '\0'; name++) {
		val = *name + 31 * val;
	}
	return val % LEN;
}

static char *strdup2(char *s) {
	char *p = (char *) malloc(strlen(s) + 1);
	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

struct item *lookup(char *name) {
	unsigned hashval = hash(name);
	struct item *itemp;
	for (itemp = hashtable[hashval]; itemp != NULL; itemp = itemp->next) {
		if (strcmp(name, itemp->name) == 0) {
			return itemp;
		}
	}
	return NULL;
}

struct item *install(char *name, char *value) {
	struct item *itemp;
	if ((itemp = lookup(name)) == NULL) {
		itemp = (struct item *) malloc(sizeof(struct item));
		if (itemp == NULL) {
			return NULL;
		}
		if ((itemp->name = strdup2(name)) == NULL) {
			free((void *) itemp);
			return NULL;
		}
		unsigned hashval = hash(name);
		itemp->next = hashtable[hashval];
		hashtable[hashval] = itemp;

	} else {
		free((void *) itemp->next);
	}

	if ((itemp->value = strdup2(value)) == NULL) {
		return NULL;
	}

	return itemp;

}

void undef(char *name) {
	unsigned hashval = hash(name);
	struct item *itemp;
	struct item *previtemp;
	for (itemp = hashtable[hashval]; itemp != NULL; previtemp = itemp, itemp =
			itemp->next) {
		if (strcmp(name, itemp->name) == 0) {
			if (previtemp == NULL) {
				hashtable[hashval] = itemp->next;
			} else {
				previtemp->next = itemp->next;
			}
			free(itemp->name);
			free(itemp->value);
			free(itemp);
		}
	}

}

/**
 * copy from ifp to ofp
 */
void filecopy(FILE *ifp,FILE *ofp){
	int c;
	while((c=getc(ifp))!=EOF)
		putc(c,ofp);
}


/**
 * test main
 */
int main(int argc,char *argv[]) {
    /**
     * cat example
     */
	FILE *fp;
	void filecopy(FILE *,FILE *);
	if(argc==1)
		filecopy(stdin,stdout);
	else
		while(--argc > 0)
			if((fp=fopen(*++argv,"r"))==NULL){
				printf("cat:cant open %s\n",*argv);
				return 1;
			}else{
				filecopy(fp,stdout);
				fclose(fp);
			}

	return 0;
}

	//minprintf("%d,%s",63,"abc");

//	assert(lookup("name")==NULL);
//	install("name", "kongming");
//
//	assert(strcmp(lookup("name")->value, "kongming") == 0);
//	undef("name");
//	assert(lookup("name")==NULL);



//#define MAXWORD 100
//
//struct tnode {					/* 树的节点 */
//  char *word;					/* 指向单词的指针 */
//  int count;					/* 单词的出现次数 */
//  struct tnode *left;			/* 左子树 */
//  struct tnode *right;			/* 右子树 */
//};
//
//struct tnode *addtree(struct tnode *, char *);
//void treeprint(struct tnode *);
//int getword(char *, int);
///**
// * wc
// */
//int main(void){
//	struct tnode *root;
//	char word[MAXWORD];
//
//	root = NULL;
//	/* getword: 读入一个单词到 word */
//	while (getword(word, MAXWORD) != EOF)
//		if (isalpha(word[0]))
//		  root = addtree(root, word);
//	  treeprint(root);
//
//	  return 0;
//
//}

//struct tnode *talloc(void);
//char *istrdup(char *);
///* addtree: 在 p 或 p 的下方加一个包含 w 的节点 */
//struct tnode *
//addtree(struct tnode *p, char *w)
//{
//	int cond;
//
//	  if (p == NULL) {				/* 新来一个单词 */
//		p = talloc();				/* 创建一个节点 */
//		p->word = strdup(w);
//		p->count = 1;
//		p->left = p->right = NULL;
//	  } else if ((cond = strcmp(w, p->word)) == 0)
//		p->count++;					/* 重复的单词 */
//	  else if (cond < 0)			/* 小于该节点则进入左子树 */
//		p->left = addtree(p->left, w);
//	  else							/* 大于该节点则进入右子树 */
//		p->right = addtree(p->right, w);
//
//	  return p;
//
//}
//
//
///* treeprint: 按序打印树 p */
//void treeprint(struct tnode *p)
//{
//  if (p != NULL) {
//	treeprint(p->left);			/* 打印左子树 */
//	printf("%4d %s\n", p->count, p->word); /* 打印中间节点 */
//	treeprint(p->right);		/* 打印右子树 */
//  }
//}
//
//#include <stdlib.h>  //malloc()
//
///* talloc: 创建一个 tnode */
//struct tnode *  talloc(void)
//{
//  return (struct tnode *) malloc(sizeof(struct tnode));
//}
//
//char *istrdup(char *s)			/* 拷贝 s */
//{
//  char *p;
//
//  p = (char *) malloc(strlen(s)+1); /* +1 是为了在结尾存入 '\0' */
//  if (p != NULL)
//	strcpy(p, s);
//
//  return p;
//}
//
//
//
///* getword: 从输入中读入下一个字或字符 */
//int getword(char *word, int lim)
//{
//  int c, getch1(void);
//  void ungetch1(int);
//  char *w = word;
//
//  while (isspace(c = getch1()))	/* 跳过空白 */
//	;
//  if (c != EOF)
//	*w++ = c;
//  if (!isalpha(c)) {
//	*w = '\0';
//	return c;
//  }
//  for (; --lim > 0; w++)
//	if (!isalnum(*w = getch1())) {
//	  ungetch1(*w);
//	  break;
//	}
//  *w = '\0';
//
//  return word[0];
//}
//
//
//
//#define BUFSIZE 100
////buffer
//char buf[BUFSIZE];
////pos
//int bufp=0;
///**
// * get a char
// */
//int getch1(void){
//
//	return (bufp>0)?buf[--bufp]:getchar();
//}
//
///**
// * 把字符退回到buffer中
// */
//void ungetch1(int c){
//	if(bufp>=BUFSIZE)
//		printf("ungetch: too many chars\n");
//	else
//		buf[bufp++]=c;
//}
//
//
//
//

//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//
//#define MAXWORD 100
//#define MAXLINE 1000
//
//char *month_name(int n);
//
//
//struct key{
//	char *word;
//	int count;
//} keytab[] = {
//		"auto",0,
//		"break",0,
//		"case",0,
//		"char",0,
//		"default",0,
//		"continue",0
//};
//
//#define NKEYS (sizeof keytab / sizeof keytab[0])
//
//int getword(char *,int);
//int binsearch(char *,struct key *,int);
//
////int main(){
////	int n;
////	char word[MAXWORD];
////	while(getword(word,MAXWORD)!=EOF)
////		if(isalpha(word[0]))
////			if((n=binsearch(word,keytab,NKEYS))>=0)
////				keytab[n].count++;
////	for(n=0;n<NKEYS;n++)
////		if(keytab[n].count>0)
////			printf("%4d %s\n",keytab[n].count,keytab[n].word);
////	return 0;
////
////
////}
//
//#define BUFSIZE 100
//
//static char c;
//
//int getch1() {
//  char rt = c ? c : getchar();
//  c = '\0';
//  return rt;
//}
//
//int ungetch1(char ch) {
//  if (c) {
//    printf("Error: more than one char unget.\n");
//    return 0;
//  } else {
//    c = ch;
//    return 1;
//  }
//}
///**
// * binsearch 在tab[0] - tab[n-1]中查找单词
// */
//int binsearch(char *word,struct key tab[],int n){
//	int cond;
//	int low,high,mid;
//	low = 0;
//	high = n - 1;
//	while(low <= high){
//		mid = (low + high)/2;
//		if((cond = strcmp(word,tab[mid].word))<0)
//			high = mid-1;
//		else if(cond > 0)
//			low = mid + 1;
//		else
//			return mid;
//	}
//	return -1;
//}
//
//
///**
// * getword 函数 从输入中获取下一个单词或字符
// */
//int getword(char *word,int lim){
//	int c, getch1(void);
//	int ungetch1(char);
//
//	char *w = word;
//	while(isspace(c=getch1()))
//		;
//	if(c!=EOF)
//		*w++=c;
//	if(!isalpha(c)){
//		*w='\0';
//		return c;
//	}
//	for(;--lim;w++)
//		if(!isalnum(*w=getch1())){
//			ungetch1(*w);
//			break;
//		}
//	*w='\0';
//	return word[0];
//}
//
//
//
//
//
//
//
////int getline(char *line,int max);
///**
// * grep
// */
////int main(int argc,char *argv[]){
////	char line[MAXLINE];
////	int found = 0;
////	if(argc!=2)
////		printf("Usage:find pattern\n");
////	else
////		while(getline(line,MAXLINE)>0)
////			if(strstr(line,argv[1]!=NULL)){
////				printf("%s",line);
////				found++;
////			}
////
////	return found;
////}
//
//
///**
// * echo version 1
// */
////int main(int argc,char *argv[]){
////	int i;
////	for(i=1;i<argc;i++){
////		printf("%s%s",argv[i],(i<argc-1)?" ":"" );
////	}
////	printf("\n");
////	return 0;
////}
//
///**
// * echo version2
// */
////int main(int argc,char *argv[]){
////	while(--argc > 0)
////		printf("%s%s",*++argv,(argc>1)?" ":"" );
////	printf("\n");
////	return 0;
////}
//
////int main(void) {
////	int n = 10;
////    char name = *month_name(n);
////
////    printf("%s",*name);
////
////	return EXIT_SUCCESS;
////}
//
//char *month_name(int n){
//	static char *name[] = {
//			"Illegal month","January",
//			"February","March","April",
//			"May","June","July","August",
//			"Sepetembr","October","Novermber","December"
//	};
//	return (n<1 || n>12)?name[0]:name[n];
//}
