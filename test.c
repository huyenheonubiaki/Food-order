#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define M 256
typedef struct Node{
  char *code_query;
  int number_of_people;
  int room_number;
  char *hotel_code;
  char *date;
  int number_of_children;
  struct Node *leftChild;
  struct Node *rightChild;
}Node;

Node *root;


Node *makeNode(char *code_query, int number_people, int room, char *hotel_code, char *date, int children)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	
	newNode->code_query = (char*)malloc(sizeof(Node));
	newNode->hotel_code = (char*)malloc(sizeof(Node));
	newNode->date = (char*)malloc(sizeof(Node));
	
	newNode->number_of_people = number_people;	
	strcpy(newNode->code_query, code_query);
 	strcpy(newNode->hotel_code, hotel_code);
 	strcpy(newNode->date, date);
 	newNode->number_of_children = children;
 	newNode->room_number = room;
 	
 	newNode->leftChild = NULL;
 	newNode->rightChild = NULL;
    
	return newNode;    
}
void init()
{
	root = NULL;
}

int h(char *s)
{
	int rs = 0;
	for(int i = 0; i < strlen(s); ++i)  rs = (rs*255 + s[i]) % M;
	return rs;
}
int fre[M];
void printNode(Node *node)
{
	printf("%s %d %d %s %s %d\n", node->code_query, node->number_of_people, node->room_number, node->hotel_code, node->date, node->number_of_children);
}

Node *insert(Node *r, char *code_query, int number_people, int room, char *hotel_code, char *date, int children)
{
  if(r == NULL) return makeNode(code_query, number_people, room, hotel_code, date, children);
  
  int c = strcmp(code_query, r->code_query);

  if(c == 0){
      return r;
    }
  else if(c < 0){
    r->leftChild = insert(r->leftChild, code_query, number_people, room, hotel_code, date, children); 
    return r;
  }
  else{
    r->rightChild = insert(r->rightChild, code_query, number_people, room, hotel_code, date, children); 
    return r;
  }
}
void printNode_intofile(Node *node, FILE *f)
{
	fprintf(f, "%s %d %d %s %s %d\n", node->code_query, node->number_of_people, node->room_number, node->hotel_code, node->date, node->number_of_children);
}
void inorder(Node *r, FILE *f)
{
	if(r == NULL) return;
	inorder(r->leftChild, f);
	printNode_intofile(r, f);
	inorder(r->rightChild, f);
}

Node *find(Node *r, char *name)
{
  if(r == NULL) return NULL;
  
  int c = strcmp(name, r->code_query);
  
  if(c == 0){
      return r;
    }
  else if(c < 0){
      return find(r->leftChild, name); 
  }
  else{
    return find(r->rightChild, name);
  }
}

void copyProfile(Node *n1, Node *n2)
{
	n1->number_of_people = n2->number_of_people;	
	strcpy(n1->code_query, n2->code_query);
 	strcpy(n1->hotel_code, n2->hotel_code);
 	strcpy(n1->date, n2->date);
 	n1->number_of_children = n2->number_of_children;
 	n1->room_number = n2->room_number;
}

Node *minValue(Node *p)
{
  Node *current = p;
  while(current != NULL && current->leftChild != NULL)
    current = current->leftChild;
  return current;
}

void processRemove(char *name)
{
  
  Node *findName = find(root, name);
    
  if(findName == root) root = NULL;
  
  if(findName->leftChild == NULL && findName->rightChild == NULL)
    {
    	free(findName);
    	return;
	}
	
  Node *tmp;
 
  if(findName->leftChild != NULL && findName->rightChild == NULL){
    copyProfile(findName, findName->leftChild);
    free(findName->leftChild);
    findName->leftChild = NULL;
    return;
  }
  
  if(findName->rightChild != NULL && findName->leftChild == NULL){
    copyProfile(findName, findName->rightChild);
    free(findName->rightChild);
   findName->rightChild = NULL;
    return;
  }
  
 
  Node *successor = minValue(findName->rightChild);

 
  copyProfile(findName, successor);
  free(successor);
  successor = NULL;
}

void freeTree(Node *r)
{
  if(r == NULL) return;
  freeTree(r->leftChild);
  freeTree(r->rightChild);
  free(r);
}


//1
int invalid_queries;
int number_queries;
void readfile(FILE *f, char *filename)
{
  f = fopen(filename, "r");
  
  init();
  
  while(!feof(f)){
  	
  	char code1[20], code2[20], date[20];
  	int number_people, room_number, number_children;
  	
  	
  	
  	fscanf(f, "%d", &number_queries);
  	
  	for(int i = 0; i < number_queries; ++i)
  	{
  		fscanf(f, "%s %d %d %s %s %d", code1, &number_people, &room_number, code2, date, &number_children);
  		if(number_people <= number_children) ++invalid_queries;
  		else
  		{
  				root = insert(root, code1, number_people, room_number, code2, date, number_children);
  				fre[h(code1)]++;
		}
  		
	}
  	
  	printf("So luong yeu cau doc duoc : %d\n", number_queries);
  	
    }
  fclose(f);
}

//2


void solve_func2() 
{
	printf("Co %d yeu cau khong hop le.\n", invalid_queries);
}


//3

void solve_func3()
{
	char tmp[10];
	printf("Nhap ma yeu cau : ");
	scanf("%s", tmp);
	Node *findNode = find(root, tmp);
	if(findNode) printNode(findNode);
	else printf("Not found\n");
}

//4

void update(Node *r, int num1, char *s1, int num2)
{
	r->number_of_people = num1;
	strcpy(r->date, s1);
	r->number_of_children = num2;
}
void solve_func4()
{
	char tmp[10];
	printf("Nhap ma yeu cau : ");
	scanf("%s", tmp);
	Node *findNode = find(root, tmp);
	if(findNode) 
	{
		printNode(findNode);
		printf("Nhap so luong nguoi : ");
		int number1;
		scanf("%d", &number1);
		
		printf("Nhap ngay thang nam (dd-mm-yyyy): ");
		char tmp1[20];
		scanf("%s", tmp1);
		
		printf("Nhap so luong tre em : ");
		int number2;
		scanf("%d", &number2);
		
		if(number1 <= number2) printf("Invalid\n");
		else 
		{
				update(findNode, number1, tmp1, number2);
				printf("Update\n");
		}
	}
	
	
	else printf("Not found\n");
	
	
}

//5

void solve_func5()
{
	char tmp[10];
	printf("Nhap ma yeu cau : ");
	scanf("%s", tmp);
	Node *findNode = find(root, tmp);
	if(findNode) 
	{
		processRemove(tmp);
		printf("Delete\n");
		--number_queries;
	}
	
	
	else printf("Not found\n");
}

//6

void solve_func6(FILE *f)
{
	f = fopen("booking_output.txt", "w");
	fprintf(f, "%d\n", number_queries);
	inorder(root, f);
	fclose(f);
}
int max_array(int *fre)
{
	int max = -1;
	for(int i = 0; i < M; ++i)
		if(max < fre[i]) max = fre[i];
	return max;
}
Node *maxx  = NULL;
void Inorder(Node *r, int i)
{
	if(r == NULL) return;
	Inorder(r->leftChild, i);
	if(fre[h(r->code_query)] == i) maxx = r;
	Inorder(r->rightChild, i);
}
void solve_func7()
{
	int max = max_array(fre);
	Inorder(root, max);
	printf("%s\n", maxx->code_query);
}
void printCurrDate()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Hien tai la : %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void MENU()
{
	printf("Chuong trinh quan ly dat phong khach san\n");
	printf("Vui long chon mot trong cac chuc nang sau\n");
	printf("[1] Doc du lieu tu file log\n");
	printf("[2] Kiem tra so luong yeu cau khong hop le\n");
	printf("[3] Tra cuu theo ma yeu cau\n");
	printf("[4] Thay doi yeu cau\n");
	printf("[5] Huy yeu cau\n");
	printf("[6] Luu danh sach yeu cau ra file\n");
	printf("[7] (OP1) Thong ke khach san duoc ua thich nhat\n");
	printf("[8] (OP2) Ngay khong hop le\n");
	printf("[9] (OP3) Ngay khong hop le\n");
	printf("[10] Thoat chuong trinh\n");
}

int main()
{

	int option;
	while(1)
	{
		MENU();
		printf("Lua chon cua ban la : ");
		scanf("%d", &option);
		if(option == 1)
		{
			 FILE *f;
			 readfile(f, "booking_orders.txt");
		}
		if(option == 2)
		{
			solve_func2();
		}
		if(option == 3)
		{
			solve_func3();
		}
		if(option == 4)
		{
			solve_func4();
		}
		if(option == 5)
		{
			solve_func5();
		}
		if(option == 6)
		{
			FILE *f;
			solve_func6(f);
		}
		if(option == 7)
		{
			solve_func7();
		}
		if(option == 10)
		{
			break;
		}
		printf("\n");
	}
  freeTree(root);
  return 0;
}



